#include <iostream>
#include <stdlib.h>
#include <cstring> // memset,strcpy,strcat
#include <math.h>  // definitions.h
#include <Eigen/Dense>
#include <Eigen/Core>
#include <chrono>

#define DEBUG_MODE 1
#define DEBUG_MODE_DEEP 1
#define DEBUG_MODE_ERROR_UHAT 1
//#define DEBUG_MODE_CLIMATE_THETA 1
using namespace std;
typedef double real_t;
typedef unsigned short small_idx_t;
#define TRMULTPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/trmult_reduced.bin"
const size_t size_of_trmult_reduced = sizeof(real_t);
const real_t TRMULT_REDUCED_THRESHOLD = 1e-14;
#define BLOCK_SIZE 8 // 8*17048
#define BLOCK_SIZE_READ 136384 // 8*17048
#define INPUTPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/"
#define PRINTPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/output/"
#ifdef DEBUG_MODE
    #define DEBUGPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/debug/"
#endif
#define N_MODEL 1
#define IND_DAM 9        // Level of the damage function, 9 is the benchmark
#define NPOSLAND 17048    // Number of cells with positive land
#define N2600 600        // Years period: 2000-2600
#define N2600_2 601        // Years period: 2000-2600 (forc_noCO2)
#define NDATA 8568        // country_data, year_data, natal_data, pop_data
#define NCOSTEMIPARAM 7 // size of cost_emi_param
#define NSCEN 36        // size of theta_amen_scen and theta_prod_scen
#define NCLEANENERGY 35 // clean_energy_data
#define T_BACK_AUX 51    // Used in temp_past
#define T_M2_MIGRATION_COSTS 4 // Year 5 in Matlab for Computing price_energy: [m2_f] = migration_costs(m2_i,amen(:,5),prod(:,5),pop5_dens,price_energy(:,5),tol_m2_inner);
// estim_model
#define TEMPLINSCALER 0.7 // Scaler impact of temperature in 20 periods (constructed)
#define LENGTH_ISO 168      // NDATA/(2000-1950+1)=168 ---> also length_C_vect
#define LENGTH_COEFF_POP 8 // length of coeff_pop_i

/** Simulation settings */
#define T_BACK 50                             // Number of periods to run backward the model
#define T_FORWARD 20                         // Number of periods to run forward the model
#define T_FORWARD_MINUS1 19                  // Number of periods to run forward the model minus 1
#define IPOSLAND(i, j) ((i)*NPOSLAND + (j))     // location i-location j cost: col_idx*NROWS+ row_idx
#define ISCEN(i, j) ((i)*9 + (j))             // amen_scen, prod_scen (4x9)
#define IPOSLANDT(t, i) ((t)*NPOSLAND + (i)) // time t-location i: col_idx*NROWS+ row_idx
#define IDERIV(c,j)  ((c)*LENGTH_ISO * T_BACK_AUX + (j))    // LENGTH_ISO * T_BACK_AUX * LENGTH_COEFF_POP ----> DEVELOP: CHECK THIS
#define ELEMENT(row,column,row_cnt) (column)*(row_cnt) + (row)
#define REV_ELEMENT(row,column,row_cnt,column_cnt) ((column_cnt)-(column)-1)*(row_cnt) + (row)
// *************************************************************
//                        BEGIN: definition.s
// *************************************************************
// 1. ****************************** main.m ******************************
// Initialize model with Benchmark Estimation: initialize(ind_RCP,maxCO2,eps)
const real_t env__ind_RCP = 8.5;    // RCP scenario for the CO2 emissions from non-fossil fuel combustion and the forcing from non-CO2sources; can take the value of 8.5, 6.0, 4.5 or 2.6;    8.5 is the baseline.
const real_t env__maxCO2 = 19500; // Total stock of CO2 available in the ground; 19500 is the baseline.
const real_t env__eps = 1.6;        // Elasticity of substitution between fossil fuels and clean energy;
// ----------------------------------------------
//    INITILIZE THE GUESSES
// Estimates natality function, migration costs and energy productivities
//  Guess on natality function, migration costs, upsilon_fossil and upsilon_clean
const real_t GUESS_coeff_pop_i[LENGTH_COEFF_POP] = {-0.69, 0, -5, -0.51, -0.25, -5, 2.88, -0.67}; // [ b0y, b1y, b1y', b2y, bsy, b1T, b2T, bsT ]
const real_t GUESS_upsilon_fossil_i = 1.15;
const real_t GUESS_upsilon_clean_i = 1.15;
const real_t GUESS_real_tgdp_growth_i = 1.017; // guess for global real_tgdp growth (backward_climate and forward_climate)
// ----------------------------------------------
// update_vect = [1 0.95 0.95]: Set speed of update for migration costs, upsilon_fossil and upsilon_clean
const real_t UPDATE_M2 = 1;
const real_t UPDATE_UPSILON_FOSSIL = 0.95;
const real_t UPDATE_UPSILON_CLEAN = 0.95;
// ------------------------ backward_climate.m
const real_t UPDATE_BW_L = 1.;    // speed of update when iterating over l
const real_t UPDATE_BW_EE = 1.;   // speed of update when iterating over CO2 emissions
const real_t UPDATE_BW_R = 1.;    // speed of update when iterating over GDP
// ------------------------ end backward_climate.m
// ------------------------ forward_climate.m
const real_t UPDATE_FW_EE = 1.;   // speed of update when iterating over CO2 emissions
const real_t UPDATE_FW_R = 1.;    // speed of update when iterating over GDP
// ------------------------ end forward_climate.m
// Tolerance of errors in the iteration: tol_vect = [ tol_clean tol_fossil tol_m2 tol_l tol_nlls tol_final_SSR tol_m2_inner tol_step ]';
#define TOLL_CLEAN ((real_t)(1.2))
#define TOLL_FOSSIL ((real_t)(2.5))
#define TOLL_M2 ((real_t)(1e9))
#define TOLL_L ((real_t)(1e9))
#define TOLL_NLLS ((real_t)(0))
#define TOLL_FINAL_SSR ((real_t)(1e-5))
#define TOLL_M2_INNER ((real_t)(1e-8))
#define TOLL_STEP ((real_t)(40))
#define TOLL_MODEL_INITIAL_PERIOD ((real_t)(1e-2)) // model_initial_period.m
// 2. ****************************** backward_climate.m ******************************
// ----------------------------------------------
#define BW_tol ((real_t)(1e-2))       // tolerance for error when iterating over uhat
#define BW_tol_l ((real_t)(1e+1))     // tolerance for error when iterating over l
#define BW_tol_e ((real_t)(1e-3))     // tolerance for error when iterating over CO2 emissions
#define BW_tol_real_tgdp ((real_t)(1e-2))// tolerance for error when iterating over real_t GDP
// 3. ****************************** forward_climate.m ******************************
#define FW_tol ((real_t)(1e-2))       // tolerance for error when iterating over uhat
#define FW_tol_e ((real_t)(1e-2))     // tolerance for error when iterating over CO2 emissions
#define FW_tol_real_tgdp ((real_t)(1e-2))// tolerance for error when iterating over real_t GDP
// 2. ****************************** initialize.m ******************************
// 1. Initialize the Parameters
const real_t env__lbar = 5.9174e+09; // total population
const real_t env__lambda = 0.32;       // congestion externalities
const real_t env__gamma1 = 0.319;       // elasticity of tomorrow's productivity relative to today's innovation
const real_t env__gamma2 = 0.99246;  // elasticity of tomorrow's productivity relative to today's productivity
const real_t env__eta = 1.;           // parameter driving scale of technology diffusion
const real_t env__mu = 0.8;           // labor share in production
const real_t env__nu = 0.15;           // intercept parameter in innovation cost function
const real_t env__ksi = 125;           // elasticity of innovation costs relative to innovation
const real_t env__sigma = 4.;           // elasticity of substitution
const real_t env__psi_util = 0.045;  // wellbeing parameter
const real_t env__beta = 0.965;       // discount factor for present discounted values
const real_t env__alpha = 0.06;       // agglomeration externalities
const real_t env__theta = 6.5;       // variance productivity shocks
const real_t env__Omega = 0.5;       // variance taste shocks
// NOT USED const real_t env__max_cumCO2 = maxCO2;                            // total stock of CO2 in the ground
//  USE env__eps const real_t env__epsilon = eps;                                // elasticity of substitution between fossil fuels and clean energy
const real_t env__tCO2_toe = 2.8466;                                                  // conversion factor: GtCO2 per Gtoe
const real_t env__price_fossil0_world = 72.99 * pow(10., 9.);                          // price of fossil fuels in usd/GtCO2
const real_t env__price_clean0_world = 1.997515248601176e+11; // ****** DEVELOP ****** read from outside: missing from initialize.m: price_clean0_world = price_clean0_world/GDPpc0; % usdP/GtCO2
//1.15 * 76.34 * pow(10., 9.) / env__tCO2_toe; // price of clean energy in usd/GtCO2 --> fundamentals.m is in usd/Gtoe
// 10. Set carbon circulation parameters (initialize.m)
// Set parameters regarding depreciation of CO2 in the atmosphere
const real_t env__a0 = 0.2173; // share of CO2 emissions remaining in the atmosphere forever
const real_t env__a1 = 0.2240; // share of CO2 emissions associated with the timescale b1
const real_t env__a2 = 0.2824;
const real_t env__a3 = 0.2763;
const real_t env__b1 = 394.4;
const real_t env__b2 = 36.54;
const real_t env__b3 = 4.304;
const real_t env__S_preind = 2200; // CO2 stock in pre-industrial era
// 11. Set forcing parameters
const real_t env__forc_sens = 5.35; // forcing sensitivity
//// 12. Set global temperature parameters
// Set global temperature parameters
const real_t env__c1 = 0.631; // temperature evolution parameters
const real_t env__c2 = 0.429;
const real_t env__d1 = 8.4;
const real_t env__d2 = 409.5;
// USED ONLY IN PLOTS: const real_t env__temp_preind = 8.1; // temperature in pre-industrial era
//// 21. Set numerical restrictions on natality functions
const real_t env__b0y_max = 0.045;
const real_t env__b1y_min = 0.01;
const real_t env__b1y_max = 0.03;
const real_t env__b2y_min = -0.00090;
const real_t env__b2y_max = -0.00050;
const real_t env__b2T_max = 0.015;
const real_t env__bsy_min = 0;
const real_t env__bsy_max = 8;
const real_t env__bsT_min = 14;
const real_t env__bsT_max = 22;
//const real_t natal_param[10] = {b0y_max, b1y_min, b1y_max, b2y_min, b2y_max, b2T_max, bsy_min, bsy_max, bsT_min, bsT_max};
//// 22. Define colors and variable names for plots
// 3. ****************************** fundamentals.m ******************************
// Set energy parameters: REPEATED DECLARATION: env__tCO2_toe, env__fossil0, env__clean0
/** Simulation settings: Set numerical parameters for the estimation of the natality function */
const real_t size_deriv = 1e-5;
const real_t scal_nlls = 1e-5;
const real_t lev_nlls = 1e-3;
const int count_max = 50;
// *************************************************************
//                        END: definition.h
// *************************************************************
// Environmental Struct
typedef struct{
    int *rowStart;     // Index of the first nonzero value of each row
    int *colIndex;     // Column Index of non-zero value
    real_t *value;               // Value
} trmult_t;
typedef struct env_t
{
    real_t *trmult_reduced;                  // Bilateral trade cost on Earth cells at t=0 only
    real_t *H;                              // NPOSLAND
    real_t *prod0;                          // productivities in 2000
    real_t *pop5_dens;                      //
    real_t *u0;                              // utility in 2000
    real_t *a_norm;                          // amenities in 2000
    real_t *weight_pop_matrix;              // Weighting matrix
    small_idx_t *C_vect;                  // national demarcations with H0>0
    real_t *emi_no_ff;                      // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC, N2600x1 (600x1)
    real_t *price_energy0;                  //, (17048x1)
    real_t *zeta_clean0;                      // Construct initial energy productivities, (17048x1)
    real_t *zeta_fossil0;                      //, (17048x1)
    real_t *forc_noCO2;                      // Read non CO2 radiative forcing, 601x1
    real_t *temp0_local;                      // Local temperatures, 17048x1
    real_t *temp_past;                      // , 17048x51 (NPOSLAND,T_BACK_AUX)
    real_t *Delta_temp;                      // , 17048x50 (NPOSLAND,T_BACK)
    real_t *scaler_temp;                      // , 17048x1
    real_t *theta_amen_scen;                  // 4x9
    real_t *theta_prod_scen;                  // 4x9
    real_t *natal_data;                      // data for years < 2001, 8568x1
    real_t *pop_data;                          // data for years < 2001, 8568x1
    real_t *m2_i;                              // Load guess for migration costs (estim_model.m)
    // Auxiliary Variables
    real_t *l0_model;          // NPOSLANDx1, 17048x1
    real_t *real_tgdp0_model; // NPOSLANDx1, 17048x1
    // ------------- end: model_initial_period
    real_t *l20_model;       // NPOSLANDx1, 17048x1   ---> natal_fct (consider printing)
    real_t *real_tgdp20_model; // NPOSLANDx1, 17048x1     ---> natal_fct (consider printing)
    real_t *temp20_local;       // NPOSLANDx1, 17048x1     ---> natal_fct (consider printing)
    // ------------- begin: backward_climate
    real_t cost_emi_param[NCOSTEMIPARAM];      // Redefine extraction cost function 1x7: [cost_emi_param_f maxCO2 3];
    real_t clean_energy_data[NCLEANENERGY]; // 35x1
    real_t emi_ff_data[T_BACK];              // Historical fossil fuel CO2 emission and its trend, 50x1, TBACKx1
    real_t emi_ff_data_tend[T_BACK];          // , 50x1, TBACKx1
    real_t coeff_pop_i[LENGTH_COEFF_POP];                  // Guess for coefficients on the natality rate function.
    trmult_t trmult_sparse_;               // Bilateral trade cost on Earth cells at t=0 only
    int ELEMENTS;
    real_t emi0_ff;                          // Global CO2 emissions from fossil fuels for 2000 (interpreted *****) - scalar
    real_t emi0;                              // total CO2 emissions for 2000, scalar
    real_t fossil_share;                      // Construct share of fossil fuels in energy composite, scalar
    real_t chi;                              // Construct share of energy in production, equations (7) and (44), scalar
    real_t cost_CO2_data;                      // Cost extraction data, 202x2
    real_t price_clean0_world;              // Define normalization relative to Princeton wage: usdP/GtCO2
    real_t S0;                              // Initialize CO2 stock layers, equations (38) and (39), scalar
    real_t S1;                              // , scalar
    real_t S2;                              // , scalar
    real_t S3;                              // , scalar
    real_t temp1;                              // Initialize temperature layers, equation (41), scalar
    real_t temp2;                              // , scalar
    real_t temp0_global;                      // , scalar
    real_t natal0;                          // Natality rates of 2000, scalar
    real_t natal20;                          // Natality rates of 2020, scalar
    real_t upsilon_fossil_i;                  // Guess for the elasticity of fossil fuel productivity growth to global real_t GDP growth    ****** DEVELOP ****** --> MAY NOT BE NEEDED
    real_t upsilon_clean_i;                  // Guess for the elasticity of clean energy productivity growth to global real_t GDP growth   ****** DEVELOP ****** --> MAY NOT BE NEEDED
    // -------------- model_initial_period
    int dummy_m; // 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    real_t flat;
    real_t exp_uhatL;
    real_t exp_uhatR;
    real_t uhat_f_exp;
    /*
    real_t *FL_H_m2_left; // model_initial_period
    real_t *FR_H_m2_left; // model_initial_period
    real_t FL_H_m2_right_exp;
    real_t FR_H_m2_right_exp;
    real_t FL_a_norm_exp;
    real_t FR_a_norm_exp;
    real_t FL_prod0_exp;
    real_t FR_prod0_exp;
    real_t FL_price_energy0_exp;
    real_t FR_price_energy0_exp;
    real_t flatL;
    real_t flatR;
    real_t aux_denom;
     */
    real_t const_phi;
    real_t const_energy;    // notice this may differ in forward and backward looking --> check
    /*
    real_t natural;        // naturalL,naturalR not needed if we have BL_H_m2_left,BL_H_m2_right
    real_t *BL_H_m2_left; // backward_climate
    real_t *BR_H_m2_left; // backward_climate
    real_t BL_H_m2_right_exp;
    real_t BR_H_m2_right_exp;
    real_t BL_a_norm_exp;
    real_t BR_a_norm_exp;
    real_t BL_prod0_exp;
    real_t BR_prod0_exp;
    real_t BL_price_energy0_exp;
    real_t BR_price_energy0_exp;
    real_t BW_exp_uhatR;
    real_t BW_uhat_f_exp;
     */
    // ------------- begin: natal_fct
    real_t real_tgdp0_w;
    real_t b0T;               // b0T, equation (31)
    real_t bw;                // bw, equation (33)
    real_t logi_bsT_fct_7;    // logi_bsT_fct(coeff_pop[7]);
    // Auxiliary to natal_fct_logreal_tgdp
    real_t logi_bsy_fct_4;    //logi_bsy_fct(coeff_pop[4]);
    real_t logi_b0y_fct_0;    //logi_b0y_fct(coeff_pop[0]);
    real_t logi_b2y_fct_3;    //logi_b2y_fct(coeff_pop[3]);
    real_t logi_b1y_fct_1;    //logi_b1y_fct(coeff_pop[1]);
    real_t minus_exp_2;       //-exp(coeff_pop[2]);
    // Construct numerator of temperature component of natality rate function, equation (24)
    real_t natal_coeff_6;     //logi_b2T_fct(coeff_pop[6]);
    real_t natal_coeff_5;     // -exp(coeff_pop[5]);

} env_t;
// *************************************************************
//                    backward/forward_climate
// *************************************************************
typedef struct sym_t
{
    // Backward
    real_t *l_b;
    real_t *real_tgdp_b;
    real_t *emiCO2_b;
    real_t *clean_b;
    // Forward
    real_t *l;
    real_t *prod;
    real_t *real_tgdp;
    real_t *amen;
    real_t *temp_local;
    real_t *price_emi;
    real_t *price_clean;
    /*
    real_t * u;

    real_t *amen;
    real_t *emiCO2_ff;
    real_t *emiCO2_total;
    real_t *stockCO2;
    real_t *temp_global;
    real_t *temp_local;
    real_t *price_fossil;
    real_t *clean;
    real_t *price_clean;
    real_t *net_births;
    */

} sym_t;
class stopwatch
{
  public:
    double total_time, calls;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
    stopwatch() : total_time(0), calls(0) {};

    inline void reset() {
      total_time = 0;
      calls = 0;
    }

    inline void start() {
      start_time = std::chrono::high_resolution_clock::now();
      calls++;
    };

    inline void stop() {
      end_time = std::chrono::high_resolution_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();
      total_time += static_cast<double>(elapsed);
    };

    // return latency in ns
    inline double latency() {
      return total_time;
    };

    // return latency in ns
    inline double avg_latency() {
      return (total_time / calls);
    };
};


size_t read_block(real_t *X_var, size_t offset)
{
    // Open the file
    FILE *fp = fopen(TRMULTPATH, "rb"); // // rb: read binary
    size_t new_offset=fread(&X_var[0],size_of_trmult_reduced,BLOCK_SIZE_READ,fp);
    new_offset=new_offset + offset;
    fclose(fp);
    return new_offset;
}
void write_binary(real_t *X_var, char *variablename, int dim_n)
{
    FILE *fp;
    char filename[250] = {'\0'};
    memset(filename, '\0', sizeof(filename));
    strcpy(filename, PRINTPATH);
    strcat(filename, variablename);
    strcat(filename, ".bin");
    fprintf(stderr, "Opening the file: %s\n", filename);

    // Open the file
    fp = fopen(filename, "wb"); // // wb: write binary
    if (fp == NULL)
    {
        fprintf(stderr, "\n1.1. FAIL: Cannot write the variable %s\n", variablename);
        exit(EXIT_FAILURE);
    }
    // Write binary
    fwrite(X_var, sizeof(X_var[0]), dim_n, fp);

    fclose(fp);
    fp = NULL;
    return;
}
void read_binary(real_t *X_var, char *variablename, int dim_n)
{
    FILE *fp;
    char filename[250] = {'\0'};
    memset(filename, '\0', sizeof(filename));
    strcpy(filename, INPUTPATH);
    strcat(filename, variablename);
    strcat(filename, ".bin");
    fprintf(stderr, "Opening the file: %s\n", filename);

    // Open the file
    fp = fopen(filename, "rb"); // // rb: read binary
    if (fp == NULL)
    {
        fprintf(stderr, "\n1.1. FAIL: Cannot read the variable %s\n", variablename);
        exit(EXIT_FAILURE);
    }
    // Variable size
    size_t SIZE_var = dim_n * sizeof(X_var[0]); // Number of bytes
    fprintf(stderr, "\nVariable %s is of size: %lu bytes\n", variablename, SIZE_var);

    // Read binary
    for (int i = 0; i < dim_n; i++)
    {
        fread(&X_var[i], sizeof(X_var[0]), 1, fp);
    }

    fclose(fp);
    fp = NULL;
    return;
}
#ifdef DEBUG_MODE
void read_binary_debug(real_t *X_var, char *variablename, int dim_n)
{
    FILE *fp;
    char filename[250] = {'\0'};
    memset(filename, '\0', sizeof(filename));
    strcpy(filename, DEBUGPATH);
    strcat(filename, variablename);
    strcat(filename, ".bin");
    fprintf(stderr, "Opening the file: %s\n", filename);

    // Open the file
    fp = fopen(filename, "rb"); // // rb: read binary
    if (fp == NULL)
    {
        fprintf(stderr, "\n1.1. FAIL: Cannot read the variable %s\n", variablename);
        exit(EXIT_FAILURE);
    }
    // Variable size
    size_t SIZE_var = dim_n * sizeof(X_var[0]); // Number of bytes
    fprintf(stderr, "\nVariable %s is of size: %lu bytes\n", variablename, SIZE_var);

    // Read binary
    for (int i = 0; i < dim_n; i++)
    {
        fread(&X_var[i], sizeof(X_var[0]), 1, fp);
    }

    fclose(fp);
    fp = NULL;
    return;
}
void debug_NLLS_temporary_read(env_t *env)
{
    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "coeff_pop_i");read_binary_debug(env->coeff_pop_i, variablename,LENGTH_COEFF_POP);
}
void debug_backward_climate_part_1(env_t *env)
{
    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_l0_model");write_binary(env->l0_model, variablename, NPOSLAND);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_real_tgdp0_model");write_binary(env->real_tgdp0_model, variablename, NPOSLAND);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_weight_pop_matrix");write_binary(env->weight_pop_matrix, variablename, NPOSLAND);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_b0T");write_binary(&env->b0T, variablename, 1);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_bw");write_binary(&env->bw, variablename, 1);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_l20_model");write_binary(env->l20_model, variablename, NPOSLAND);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_real_tgdp20_model");write_binary(env->real_tgdp20_model, variablename, NPOSLAND);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_temp20_local");write_binary(env->temp20_local, variablename, NPOSLAND);
}
void debug_backward_climate_init(env_t *env, real_t *theta_amen_temp)
{

    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_m2_i");
    write_binary(env->m2_i, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    printf("\ncoef pop: %.16lf %.16lf %.16lf %.16lf %.16lf %.16lf %.16lf %.16lf", env->coeff_pop_i[0],
           env->coeff_pop_i[1],
           env->coeff_pop_i[2],
           env->coeff_pop_i[3],
           env->coeff_pop_i[4],
           env->coeff_pop_i[5],
           env->coeff_pop_i[6],
           env->coeff_pop_i[7]);
    // ---------------------------------------------------------------------------
    printf("\nupsilon_fossil: %.16lf", env->upsilon_fossil_i);
    printf("\nupsilon_clean: %.16lf", env->upsilon_clean_i);
    printf("\n real_tgdp0_w: %.16lf", env->real_tgdp0_w);
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_temp_past");
    write_binary(env->temp_past, variablename, (int)(NPOSLAND * T_BACK_AUX)); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_theta_amen_temp");
    write_binary(theta_amen_temp, variablename, (int)(NPOSLAND * T_BACK)); // SET VARIABLE
}
void debug_backward_climate_output(sym_t *sym_)
{
    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_sym_l_b");write_binary(sym_->l_b, variablename, NPOSLAND * T_BACK);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_sym_real_tgdp_b");write_binary(sym_->real_tgdp_b, variablename, NPOSLAND * T_BACK);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_sym_emiCO2_b");write_binary(sym_->emiCO2_b, variablename, NPOSLAND * T_BACK);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_sym_clean_b");write_binary(sym_->clean_b, variablename, NPOSLAND * T_BACK);
}
void debug_backward_climate_temporary_read(sym_t *sym_)
{
    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    int alloc_size = NPOSLAND * T_BACK;
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "l_b");read_binary_debug(sym_->l_b, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "real_tgdp_b");read_binary_debug(sym_->real_tgdp_b, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emiCO2_b");read_binary_debug(sym_->emiCO2_b, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "clean_b");read_binary_debug(sym_->clean_b, variablename,alloc_size);
}
void debug_forward_climate_temporary_read(sym_t *sym_)
{
    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    int alloc_size = NPOSLAND * T_FORWARD;
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "l");read_binary_debug(sym_->l, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "prod");read_binary_debug(sym_->prod, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "real_tgdp");read_binary_debug(sym_->real_tgdp, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "amen");read_binary_debug(sym_->amen, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp_local");read_binary_debug(sym_->temp_local, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "price_emi");read_binary_debug(sym_->price_emi, variablename,alloc_size);
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "price_clean");read_binary_debug(sym_->price_clean, variablename,alloc_size);
    
}
void write_all(env_t *env) //, input_t *in, vars_t *vars)
{
    // ********************************** WRITE THE VARIABLES TO OUTPUT
    char variablename[250] = {'\0'};
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "H");
    write_binary(env->H, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "prod0");
    write_binary(env->prod0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "pop5_dens");
    write_binary(env->pop5_dens, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "u0");
    write_binary(env->u0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "a_norm");
    write_binary(env->a_norm, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "trmult_reduced");
    write_binary(env->trmult_reduced, variablename, NPOSLAND * NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    real_t *C_vect_real_t = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    for (int i = 0; i < NPOSLAND; i++)
        C_vect_real_t[i] = (real_t)env->C_vect[i];
    strcpy(variablename, "C_vect");
    write_binary(C_vect_real_t, variablename, NPOSLAND); // ************* VARIABLE
    free(C_vect_real_t);
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi_no_ff");
    write_binary(env->emi_no_ff, variablename, N2600); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "price_energy0");
    write_binary(env->price_energy0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "zeta_clean0");
    write_binary(env->zeta_clean0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "zeta_fossil0");
    write_binary(env->zeta_fossil0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "forc_noCO2");
    write_binary(env->forc_noCO2, variablename, N2600_2); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp0_local");
    write_binary(env->temp0_local, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp_past");
    write_binary(env->temp_past, variablename, (int)(NPOSLAND * T_BACK_AUX)); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "Delta_temp");
    write_binary(env->Delta_temp, variablename, NPOSLAND * T_BACK); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "scaler_temp");
    write_binary(env->scaler_temp, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "theta_amen_scen");
    write_binary(env->theta_amen_scen, variablename, NSCEN); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "theta_prod_scen");
    write_binary(env->theta_prod_scen, variablename, NSCEN); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "natal_data");
    write_binary(env->natal_data, variablename, NDATA); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "pop_data");
    write_binary(env->pop_data, variablename, NDATA); // SET VARIABLE

    // Print Guesses
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "m2_i");
    write_binary(env->m2_i, variablename, NPOSLAND); // SET VARIABLE

    // Print Scalars
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi0_ff");
    write_binary(&env->emi0_ff, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi0");
    write_binary(&env->emi0, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "fossil_share");
    write_binary(&env->fossil_share, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "chi");
    write_binary(&env->chi, variablename, 1); // SET VARIABLE
    // price_clean0_world is set as global
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S0");
    write_binary(&env->S0, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S1");
    write_binary(&env->S1, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S2");
    write_binary(&env->S2, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S3");
    write_binary(&env->S3, variablename, 1); // SET VARIABLE
    // S_preind set as global
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp1");
    write_binary(&env->temp1, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp2");
    write_binary(&env->temp2, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp0_global");
    write_binary(&env->temp0_global, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "natal0");
    write_binary(&env->natal0, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "natal20");
    write_binary(&env->natal20, variablename, 1); // SET VARIABLE

    // Print arrays in stack
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "cost_emi_param");
    write_binary(env->cost_emi_param, variablename, NCOSTEMIPARAM); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "clean_energy_data");
    write_binary(env->clean_energy_data, variablename, NCLEANENERGY); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi_ff_data");
    write_binary(env->emi_ff_data, variablename, T_BACK); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi_ff_data_tend");
    write_binary(env->emi_ff_data_tend, variablename, T_BACK); // SET VARIABLE
    // ********************************** END WRITE THE VARIABLES TO OUTPUT
    return;
}
#endif
// *************************************************************
//                        BEGIN: KERNEL (estim_model)
// *************************************************************
// ==================================== NATALITY FUNCTION
void loop_uhat_sparse(env_t *env, real_t tol,real_t *L, real_t L_exp,
               real_t *uhat_i, real_t *R, real_t R_exp)
{
    real_t integral[NPOSLAND];
    real_t error = tol + 1.;
    int iter = 0;
    loop_uhat_while:
    while (error >= tol)
    {
        // Compute accuracy and update the guess
        loop_uhat_integral:
        for (int i = 0; i < NPOSLAND; i++)
            integral[i] = R[i] * pow(uhat_i[i], R_exp);
        error = 0;
        loop_uhat_mult:
        for (int i = 0; i < NPOSLAND; i++)
        {
            int e_max;
            if(i<NPOSLAND-1)
                e_max=env->trmult_sparse_.rowStart[i+1];
            else
                e_max=env->ELEMENTS;
            real_t rhs = 0.;
            for (int e = env->trmult_sparse_.rowStart[i]; e < e_max; e++){
                rhs += env->trmult_sparse_.value[e] * integral[env->trmult_sparse_.colIndex[e]];
            }
            real_t uhat_f = L[i] * pow(rhs, L_exp);
            real_t deviation = (uhat_i[i] - uhat_f);
            error += deviation * deviation;
            // Update the Guess
            uhat_i[i] = uhat_f;
        }
        iter = iter + 1;
#ifdef DEBUG_MODE
        printf("Number of iterations: %d\n", iter);
#endif
    } // end while
    
    // ****************************************** ORIGINAL APPROACH: COMPUTE
    // Check differences
    real_t uhat_i_3[NPOSLAND];
    for (int i = 0; i < NPOSLAND; i++)
        uhat_i_3[i] = 1.;
    error = tol + 1.;
    iter = 0;
    while (error >= tol)
    {
        // Compute accuracy and update the guess
        for (int i = 0; i < NPOSLAND; i++)
            integral[i] = R[i] * pow(uhat_i_3[i], R_exp);
        error = 0;
        for (int i = 0; i < NPOSLAND; i++)
        {
            real_t rhs = 0;
            for (int j = 0; j < NPOSLAND; j++)
                rhs += env->trmult_reduced[IPOSLAND(i, j)] * integral[j];
            real_t uhat_f = L[i] * pow(rhs, L_exp);
            real_t deviation = (uhat_i_3[i] - uhat_f);
            error += deviation * deviation;
            // Update the Guess
            uhat_i_3[i] = uhat_f;
        }
        iter = iter + 1;
#ifdef DEBUG_MODE
        printf("%d\n", iter);
#endif
    } // end while
    
#ifdef DEBUG_MODE
    real_t diff;
    diff = 0.;
    for (int i = 0; i < NPOSLAND; i++)
        diff+= uhat_i[i]-uhat_i_3[i];
    printf("DIFFERENCE METHOD 1 AND ORIGINAL METHOD: %.19lf\n",diff);
    diff = 0.;
    for (int i = 0; i < NPOSLAND; i++)
        diff+= fabs(uhat_i[i]-uhat_i_3[i]);
    diff=diff/((real_t) NPOSLAND);
    printf("ABSOLUTE MEAN ERROR METHOD 1 AND ORIGINAL METHOD: %.19lf\n",diff);
    diff = 0.;
    for (int i = 0; i < NPOSLAND; i++)
        diff+= fabs(uhat_i[i]-uhat_i_3[i])/uhat_i_3[i]*100;
    diff=diff/((real_t) NPOSLAND);
    printf("ABSOLUTE MEAN ERROR METHOD 1 AND ORIGINAL METHOD: %.19lf\n",diff);
    
    printf("Error: %.16lf\n", error);
#endif  // DEBUG_MODE
    
}
void loop_uhat_eigen(const real_t tol,double *trmult_reduced,double *L,const real_t L_exp,
                     double *uhat_i,double *R,const real_t R_exp)
/*
    input:
    - tol: level of tolerance, scalar, real_t
    - trmult_reduced: 17048x17048, real_t
    - L,R: 17048x1, real_t
    - L_exp,R_exp: scalar
    output:
    - uhat_i: 17048x1, real_t
 */
{
    // Create Eigen Mapping
    Eigen::MatrixXd tr_e = Eigen::Map<Eigen::Matrix<double,NPOSLAND,NPOSLAND,Eigen::RowMajor>> (trmult_reduced);        // ************* DEVELOP: I am explicitely assuming that real_t is double. May trigger error.
    printf("%.22lf == %.22lf\n",tr_e(13,17047),trmult_reduced[IPOSLAND(13,17047)]);
    printf("%.22lf == %.22lf\n",tr_e(0,17047),trmult_reduced[IPOSLAND(0, 17047)]);
    
    Eigen::MatrixXd integral_e(NPOSLAND,1);
    Eigen::MatrixXd rhs_e(NPOSLAND,1);
    Eigen::MatrixXd uhat_f_e(NPOSLAND,1);
    /*
    Eigen::Matrix<double,NPOSLAND,1> integral_e;
    Eigen::Matrix<double,NPOSLAND,1> rhs_e;
    Eigen::Matrix<double,NPOSLAND,1> uhat_f_e;
    */
    Eigen::MatrixXd L_e = Eigen::Map<Eigen::Matrix<double,NPOSLAND,1>> (L);
    Eigen::MatrixXd R_e = Eigen::Map<Eigen::Matrix<double,NPOSLAND,1>> (R);
    Eigen::MatrixXd uhat_i_e = Eigen::Map<Eigen::Matrix<double,NPOSLAND,1>> (uhat_i);
    
    real_t error = tol + 1.;
    int iter = 0;
    while ((error >= tol) & (iter<=3))
    {
        integral_e = R_e.array() * (uhat_i_e.array()).pow(R_exp);
        rhs_e = tr_e*integral_e;
        uhat_f_e = L_e.array() * (rhs_e.array()).pow(L_exp);
        error = ((uhat_i_e - uhat_f_e).array().pow(2)).sum();
        uhat_i_e = uhat_f_e;
        iter = iter + 1;
//#ifdef DEBUG_MODE_ERROR_UHAT
        printf("iter %d error_uhat: %.16lf\n", iter,error);
//#endif
    } // end while
#ifdef DEBUG_MODE_ERROR_UHAT
    printf("error_uhat: %.16lf\n", error);
#endif
}
// **********************************************************************
//                                  KERNEL TO FPGA
// **********************************************************************
inline void loop_uhat(const real_t tol,const real_t *trmult_reduced,const real_t *L,const real_t L_exp,
               real_t *uhat_i,const real_t *R,const real_t R_exp)
/*
    input:
    - tol: level of tolerance, scalar, real_t
    - trmult_reduced: 17048x17048, real_t
    - L,R: 17048x1, real_t
    - L_exp,R_exp: scalar
    output:
    - uhat_i: 17048x1, real_t
 */
{
    real_t integral[NPOSLAND];
    real_t error = tol + 1.;
    int iter = 0;
    while ((error >= tol) & (iter<=3))
    {
        // Compute accuracy and update the guess
        for (int i = 0; i < NPOSLAND; i++)
            integral[i] = R[i] * pow(uhat_i[i], R_exp);
        error = 0;
        // ATTEMPT 1
        /*
        real_t rhs[NPOSLAND];
        //#pragma clang loop unroll(full)
        //#pragma unroll_completely
        // #pragma UNROLL(4)
        //#pragma clang loop vectorize(enable)
        for (int i = 0; i < NPOSLAND; i++)
        {
            real_t sum = 0;
            int offset = IPOSLAND(i, 0);
            const real_t* __restrict tr_row = &trmult_reduced[offset];//const real_t* __restrict__ integral_row = integral;
            #pragma clang loop vectorize(enable)
            for (int j = 0; j < NPOSLAND; j++)
                sum += tr_row[j] * integral[j];
            rhs[i]=sum;
        }
        for (int i = 0; i < NPOSLAND; i++){
            real_t uhat_f = L[i] * pow(rhs[i], L_exp);
            real_t deviation = (uhat_i[i] - uhat_f);
            error += deviation * deviation;
            // Update the Guess
            uhat_i[i] = uhat_f;
        }
        */
        // ATTEMPT 2
        for (int i = 0; i < NPOSLAND; i++)
        {
            real_t rhs = 0;
            for (int j = 0; j < NPOSLAND; j++)// loop
                rhs= std::fma(trmult_reduced[IPOSLAND(i, j)],integral[j],rhs); // instruction
            //    rhs += trmult_reduced[IPOSLAND(i, j)] * integral[j];
            real_t uhat_f = L[i] * pow(rhs, L_exp);
            real_t deviation = (uhat_i[i] - uhat_f);
            error += deviation * deviation;
            // Update the Guess
            uhat_i[i] = uhat_f;
        }
        // GOOD AND WORKING
        /*
         for (int i = 0; i < NPOSLAND; i++)
         {
             real_t rhs = 0;
             for (int j = 0; j < NPOSLAND; j++)
                 rhs += trmult_reduced[IPOSLAND(i, j)] * integral[j];
             real_t uhat_f = L[i] * pow(rhs, L_exp);
             real_t deviation = (uhat_i[i] - uhat_f);
             error += deviation * deviation;
             // Update the Guess
             uhat_i[i] = uhat_f;
         }
         //*/
        iter = iter + 1;
#ifdef DEBUG_MODE_ERROR_UHAT
        printf("iter %d error_uhat: %.16lf\n", iter,error);
#endif
    } // end while
#ifdef DEBUG_MODE_ERROR_UHAT
    printf("error_uhat: %.16lf\n", error);
#endif
}
// **********************************************************************
//                                  KERNEL TO FPGA
// **********************************************************************
void init_L_R_eq_75_88_part_1(env_t *env,real_t *amen,real_t *prod,real_t *L_H_m2,real_t *R_H_m2,real_t *L,real_t *R)
/*
 Inputs:
    amen: amenities
    prod: productivities
    FL_H_m2: aux
    FR_H_m2: aux
 Returns:
    L_aux: pow(env->a_norm[i], env->FL_a_norm_exp) * pow(env->prod0[i], (env->FL_prod0_exp)) * FL_H_m2[i]
    R_aux: pow(env->a_norm[i], env->FR_a_norm_exp) * pow(env->prod0[i], (env->FR_prod0_exp)) * FR_H_m2[i]
 */
{
    real_t denom = 1. + 2. * env__theta;
    real_t L_amen_exp = (1. + env__theta) / (denom * env->exp_uhatL);
    real_t R_amen_exp = env__theta * env__theta / denom;
    real_t L_prod_exp = 1. / (denom * env->exp_uhatL);
    real_t R_prod_exp = (1. + env__theta) / denom;
    // Backward Climate different exponents                                  ****** DEVELOP ******
    if(env->dummy_m==1){
        L_prod_exp = L_prod_exp*1./env__gamma2;
        R_prod_exp = R_prod_exp*1./env__gamma2;
    }
    // Pre-compute auxiliary variables to equation (75)/(88)
    for (int i = 0; i < NPOSLAND; i++)
    {
        L[i] = pow(amen[i], L_amen_exp) * pow(prod[i], L_prod_exp) * L_H_m2[i]; // outside the integral
        R[i] = pow(amen[i], R_amen_exp) * pow(prod[i], R_prod_exp) * R_H_m2[i]; // inside the integral
        // printf("%lf %lf %lf\n",FL[i],FR[i],uhat_i[i]);
    }
}
void init_L_R_eq_75_88_part_2(env_t *env,real_t *price_energy,real_t *L_aux,real_t *R_aux,real_t *L,real_t *R)
/*
 Inputs:
    amen: amenities
    prod: productivities
    FL_H_m2: aux
    FR_H_m2: aux
 Returns:
    FL: pow(env->a_norm[i], env->FL_a_norm_exp) * pow(env->prod0[i], (env->FL_prod0_exp)) * FL_H_m2[i]
        * pow(price_energy[i],L_price_energy0_exp)
    FR: pow(env->a_norm[i], env->FR_a_norm_exp) * pow(env->prod0[i], (env->FR_prod0_exp)) * FR_H_m2[i]
        * pow(price_energy[i],R_price_energy0_exp)
 */
{
    real_t denom = 1. + 2. * env__theta;
    real_t L_price_energy_exp = -env__theta * env__mu * (1. - env->chi) / (denom * env->exp_uhatL);
    real_t R_price_energy_exp = L_price_energy_exp * (1. + env__theta)  * env->exp_uhatL;
    for (int i = 0; i < NPOSLAND; i++)
    {
        L[i] = L_aux[i] * pow(price_energy[i],L_price_energy_exp); // outside the integral
        R[i] = R_aux[i] * pow(price_energy[i],R_price_energy_exp); // inside the integral
        // printf("%lf %lf\n",FL[i],FR[i]);
    }
}
void init_model(env_t *env,const real_t *m2,real_t *L_H_m2,real_t *R_H_m2,real_t * uhat_i,real_t gamma1)
/*
  Precompute Auxiliary Variables
 Input:
    gamma_1:
 Returns:
    env->flat = flatR - env__theta * flatL;                                         // natural in case of backward_climate
    env->exp_uhatL = flatL / env__Omega + (1. + env__theta) / denom;                // naturalL in case of backward_climate
    env->exp_uhatR = flatR / env__Omega - env__theta * env__theta / denom;          // naturalR in case of backward_climate
    env->uhat_f_exp
    L_H_m2
    R_H_m2
    uhat_i: guess on utility function
 */
{
    // Precompute auxiliary variables
    real_t denom = 1. + 2. * env__theta;
    
    // env->dummy_m: 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    real_t squ;
    if((env->dummy_m==0)||(env->dummy_m==2))
        // ******************** model_initial_period.m + forward_climate.m
        squ= env__alpha - 1. +
        (env__lambda + gamma1 / env__ksi - (1. - env__mu)) * env__theta;
        // term in square brackets of flat_R and flat_L
        // Notice: gamma_1 may differ between model_initial_period.m + forward_climate.m
    else{
        // ******************** backward_climate.m
        squ = env__alpha - 1. +
        (env__lambda + gamma1 / env__ksi - (1. - env__mu) - gamma1 / (env__ksi * env__gamma2)) * env__theta;
        // term in square brackets of natural_R and natural_L
    }
    // ======================== flat vs natural
    real_t flatL = env__lambda - squ / denom;                                         // naturalL in case of backward_climate
    real_t flatR = 1. - env__lambda * env__theta + (1. + env__theta) * squ / denom;   // naturalR in case of backward_climate
    // ========================
    // Output
    env->flat = flatR - env__theta * flatL;                                         // natural in case of backward_climate
    env->exp_uhatL = flatL / env__Omega + (1. + env__theta) / denom;
    env->exp_uhatR = flatR / env__Omega - env__theta * env__theta / denom;
    env->uhat_f_exp = 1. / (env__theta * env->exp_uhatL);
    
    // env->dummy_m: 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    env->const_phi = pow((gamma1 / env__ksi) / (env__nu * (env__mu + gamma1 / env__ksi)), (1. / env__ksi));
    env->const_energy = (1. - env->chi) * env__mu / (env__mu + gamma1 / env__ksi);
    
    /* Precompute auxiliary variables to:
     1. equation (75) for forward_climate + model_initial_period
     2. equation (88) for backward_climate
    */
    real_t aux_exp_left = (flatL - 1. / denom) / env->exp_uhatL;
    real_t L_H_m2_right_exp = flatL / (env__Omega * env->exp_uhatL);
    real_t aux_exp_right = -flatR + env__theta / denom;
    real_t R_H_m2_right_exp = -flatR / env__Omega;
    for (int i = 0; i < NPOSLAND; i++)
    {
        L_H_m2[i] = pow(env->H[i],aux_exp_left) *pow(m2[i],L_H_m2_right_exp);
        R_H_m2[i] = pow(env->H[i],aux_exp_right)*pow(m2[i],R_H_m2_right_exp);
        uhat_i[i] = 1.; // guess on utility function
    }
    /*
    env->FL_a_norm_exp = (1. + env__theta) / (denom * exp_uhatL);
    env->FR_a_norm_exp = env__theta * env__theta / denom;
    env->FL_prod0_exp = 1. / (denom * exp_uhatL);
    env->FR_prod0_exp = (1. + env__theta) / denom;
    env->FL_price_energy0_exp = -env__theta * env__mu * (1. - env->chi) / (denom * exp_uhatL);
    env->FR_price_energy0_exp = -env__theta * (1. + env__theta) * env__mu * (1. - env->chi) / denom;
    env->uhat_f_exp = 1. / (env__theta * exp_uhatL);

    env->flatL = flatL;
    env->flatR = flatR;
    env->flat = flat;
    env->exp_uhatL = exp_uhatL;
    env->exp_uhatR = exp_uhatR;
    env->aux_denom = denom;

    // ****************************** backward_climate.m ******************************
    // Backward Climate Preal_tlocation: Precompute auxiliary variables
    env->const_phi = pow((env__gamma1 / env__ksi) / (env__nu * (env__mu + env__gamma1 / env__ksi)), (1. / env__ksi));
    env->const_energy = (1 - env->chi) * env__mu / (env__mu + env__gamma1 / env__ksi);
    real_t squ_b = (env__alpha - 1 + (env__lambda + env__gamma1 / env__ksi - (1 - env__mu) - env__gamma1 / (env__ksi * env__gamma2)) * env__theta); // term in square brackets of natural_R and natural_L
    real_t naturalL = env__lambda - squ_b / denom;
    real_t naturalR = 1 - env__lambda * env__theta + (1 + env__theta) * squ_b / denom;
    real_t natural = naturalR - env__theta * naturalL;
    exp_uhatL = naturalL / env__Omega + (1. + env__theta) / denom;
    exp_uhatR = naturalR / env__Omega - env__theta * env__theta / denom;
    env->natural = natural;
    // Precompute auxiliary variables to equation (88)
    for (int i = 0; i < NPOSLAND; i++)
    {
        env->BL_H_m2_left[i] = pow(env->H[i], (naturalL - 1 / denom) / exp_uhatL); // naturalL only difference
        env->BR_H_m2_left[i] = pow(env->H[i], (-naturalR + env__theta / denom));   // naturalR only difference
    }
    env->BL_H_m2_right_exp = naturalL / (env__Omega * exp_uhatL);                                     // naturalL only difference: m2.^(naturalL/(Omega*exp_uhatL))
    env->BR_H_m2_right_exp = -naturalR / env__Omega;                                                 // naturalR only difference: m2.^(-naturalR/Omega)
    env->BL_a_norm_exp = (1. + env__theta) / (denom * exp_uhatL);                                     // naturalL only difference: amen(:,t).^((1+theta)/(denom*exp_uhatL))
    env->BR_a_norm_exp = env__theta * env__theta / denom;                                             // identical (could simplify, keep for readability): amen(:,t).^(theta^2/denom)            ****** DEVELOP ******
    env->BL_prod0_exp = 1. / (env__gamma2 * denom * exp_uhatL);                                         // naturalL and gamma2 difference: prod_next.^(1/(gamma2*denom*exp_uhatL))
    env->BR_prod0_exp = (1. + env__theta) / (env__gamma2 * denom);                                     // gamma2 difference: prod_next.^((1+theta)/(gamma2*denom))
    env->BL_price_energy0_exp = -env__theta * env__mu * (1. - env->chi) / (denom * exp_uhatL);         // price_energy(:,t).^(-theta*mu*(1-chi)/(denom*exp_uhatL))
    env->BR_price_energy0_exp = -env__theta * (1. + env__theta) * env__mu * (1. - env->chi) / denom; // identical: price_energy(:,t).^(-theta*(1+theta)*mu*(1-chi)/denom)    ****** DEVELOP ******
    env->BW_exp_uhatR=exp_uhatR;
    env->BW_uhat_f_exp = 1. / (env__theta * exp_uhatL);
     */
}
void init_worldgdp(env_t *env)
/*
 // Read parameters
     - from env: m2_i,coeff_pop_i,upsilon_fossil_i,upsilon_clean_i
     - from env: l0_model and real_tgdp0_model.
            // ****** DEVELOP ****** : (CHECK IF IT is l20_model and not l0_model.
            // ****** DEVELOP ****** Consider not storing l0_model and real_tgdp0_model
    Returns: real_tgdp0_w
 */
{
    real_t sum = 0;
    for (int i = 0; i < NPOSLAND; i++)
    {
        sum += env->l0_model[i] * env->real_tgdp0_model[i] * env->H[i];
    }
    sum = sum / env__lbar;
    env->real_tgdp0_w = sum;
}
void model_initial_period(env_t *env)
/*  % Update variables of period 0: [ l0_model,~,~,real_tgdp0_model ] = model_initial_period(m2_i);
    Input: m2_i
    Returns: l0_model,real_tgdp0_model
 */
{
    real_t *FL_H_m2 = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    real_t *FR_H_m2 = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    real_t *FL = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    real_t *FR = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    real_t *uhat_i = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    // ******************* INITIALIZATIONS: model_initial_period; backward_climate; forward_climate
    env->dummy_m=0; // env->dummy_m: 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    // Initialize: env->flat, env->exp_uhatL env->exp_uhatR L_H_m2 R_H_m2, uhat_i, FL, FR
    // Initialize: env->flat, env->exp_uhatL env->exp_uhatR L_H_m2 R_H_m2, uhat_i
    init_model(env,env->m2_i,FL_H_m2,FR_H_m2,uhat_i,env__gamma1);
    // Precompute auxiliary variables to equation (75): FL FR
    init_L_R_eq_75_88_part_1(env,env->a_norm,env->prod0,FL_H_m2,FR_H_m2,FL,FR);
    init_L_R_eq_75_88_part_2(env,env->price_energy0,FL,FR,FL,FR);
    // ********************************************** END INITIALIZATIONS
    // Iterate uhat, equation (75)
    printf("First loop.\n");
    stopwatch total_time;
    total_time.start();
    loop_uhat_eigen(TOLL_MODEL_INITIAL_PERIOD,env->trmult_reduced,FL,env->uhat_f_exp,uhat_i,FR,env->exp_uhatR);
    total_time.stop();
    printf("First loop total latency is: %lf\n",total_time.latency()* double(1e-9));
    stopwatch total_time2;
    printf("Second loop.\n");
    total_time2.start();
    real_t uhat_i_2[NPOSLAND];
    for (int i = 0; i < NPOSLAND; i++){
        uhat_i_2[i] = 1.;
    }
    loop_uhat(TOLL_MODEL_INITIAL_PERIOD,env->trmult_reduced,FL,env->uhat_f_exp,uhat_i_2,FR,env->exp_uhatR);
    total_time2.stop();
    printf("First loop total latency is: %lf\n",total_time2.latency()* double(1e-9));
    //loop_uhat_sparse(env,TOLL_MODEL_INITIAL_PERIOD,FL,env->uhat_f_exp,uhat_i,FR,env->exp_uhatR);
    //loop_uhat_fast(TOLL_MODEL_INITIAL_PERIOD,FL,env->uhat_f_exp,uhat_i,FR,env->exp_uhatR);
    // Accumulators
    real_t one_over_omega = 1. / env__Omega;
    real_t sum_u0m2 = 0.;
    for (int i = 0; i < NPOSLAND; i++)
    {
        real_t aux_u0m2 = pow(uhat_i[i], one_over_omega) * pow(env->m2_i[i], (-one_over_omega));
        sum_u0m2 += aux_u0m2;
        env->l0_model[i] = 1. / env->H[i] * aux_u0m2;
    }
    real_t lbar_u0m2 = env__lbar / sum_u0m2;
    real_t lbar_u0m2_pow = pow(lbar_u0m2, env->flat / env__theta);
    for (int i = 0; i < NPOSLAND; i++)
    {
        env->l0_model[i] = env->l0_model[i] * lbar_u0m2;
        real_t u0 = uhat_i[i] * lbar_u0m2_pow;
        env->real_tgdp0_model[i] = (u0 / env->a_norm[i]) * pow(env->l0_model[i], env__lambda);
    }
    // Initializes real_tgdp0_w
    init_worldgdp(env);
#ifdef DEBUG_MODE
    printf("\n\nreal_tgdp0_w = %.16lf", env->real_tgdp0_w);
#endif

    // Deallocate memory allocation
    free(FL_H_m2);
    free(FR_H_m2);
    free(FL);
    free(FR);
    free(uhat_i);
}
// *************************************************************
//                        END: KERNEL (estim_model)
// *************************************************************
void init_all(env_t *env) //, input_t *in, vars_t *vars)
{
    // Prellocate
    env->H = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->prod0 = (real_t *)calloc(NPOSLAND, sizeof(real_t)); // productivities in 2000
    env->pop5_dens = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->u0 = (real_t *)calloc(NPOSLAND, sizeof(real_t));                         // utility in 2000
    env->a_norm = (real_t *)calloc(NPOSLAND, sizeof(real_t));                     // amenities in 2000
    env->trmult_reduced = (real_t *)calloc(NPOSLAND * NPOSLAND, sizeof(real_t)); // Bilateral trade cost on Earth cells at t=0 only
    env->weight_pop_matrix = (real_t *)calloc(NDATA, sizeof(real_t)); // Population Shares, NDATAx1
    env->C_vect = (small_idx_t *)calloc(NPOSLAND, sizeof(small_idx_t));         // national demarcations with H0>0
    env->emi_no_ff = (real_t *)calloc(N2600, sizeof(real_t));                     // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC                    // utility in 2000
    env->price_energy0 = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->zeta_clean0 = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->zeta_fossil0 = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->forc_noCO2 = (real_t *)calloc(N2600_2, sizeof(real_t)); // Read non CO2 radiative forcing, 601x1
    env->temp0_local = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->temp_past = (real_t *)calloc(NPOSLAND * T_BACK_AUX, sizeof(real_t));
    env->Delta_temp = (real_t *)calloc(NPOSLAND * T_BACK, sizeof(real_t));
    env->scaler_temp = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->theta_amen_scen = (real_t *)calloc(NSCEN, sizeof(real_t)); // 4x9
    env->theta_prod_scen = (real_t *)calloc(NSCEN, sizeof(real_t)); // 4x9
    env->natal_data = (real_t *)calloc(NDATA, sizeof(real_t));
    env->pop_data = (real_t *)calloc(NDATA, sizeof(real_t));
    env->m2_i = (real_t *)calloc(NPOSLAND, sizeof(real_t)); // Guesses

    // Auxiliary Variables
    env->l0_model = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->real_tgdp0_model = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->l20_model = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->real_tgdp20_model = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    env->temp20_local = (real_t *)calloc(NPOSLAND, sizeof(real_t));
    
    // ********************************** READ THE VARIABLES FROM INPUT
    char variablename[250] = {'\0'};
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "H");
    read_binary(env->H, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "prod0");
    read_binary(env->prod0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "pop5_dens");
    read_binary(env->pop5_dens, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "u0");
    read_binary(env->u0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "a_norm");
    read_binary(env->a_norm, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "trmult_reduced");
    read_binary(env->trmult_reduced, variablename, NPOSLAND * NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    real_t *C_vect_real_t = (real_t *)malloc(NPOSLAND * sizeof(real_t));
    strcpy(variablename, "C_vect");
    read_binary(C_vect_real_t, variablename, NPOSLAND); // ************* VARIABLE
    for (int i = 0; i < NPOSLAND; i++)
        env->C_vect[i] = (small_idx_t)(C_vect_real_t[i]-1);
    free(C_vect_real_t);
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi_no_ff");
    read_binary(env->emi_no_ff, variablename, N2600); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "price_energy0");
    read_binary(env->price_energy0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "zeta_clean0");
    read_binary(env->zeta_clean0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "zeta_fossil0");
    read_binary(env->zeta_fossil0, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "forc_noCO2");
    read_binary(env->forc_noCO2, variablename, N2600_2); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp0_local");
    read_binary(env->temp0_local, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp_past");
    read_binary(env->temp_past, variablename, (int)(NPOSLAND * T_BACK_AUX)); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "Delta_temp");
    read_binary(env->Delta_temp, variablename, NPOSLAND * T_BACK); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "scaler_temp");
    read_binary(env->scaler_temp, variablename, NPOSLAND); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "theta_amen_scen");
    read_binary(env->theta_amen_scen, variablename, NSCEN); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "theta_prod_scen");
    read_binary(env->theta_prod_scen, variablename, NSCEN); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "natal_data");
    read_binary(env->natal_data, variablename, NDATA); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "pop_data");
    read_binary(env->pop_data, variablename, NDATA); // SET VARIABLE
    // ********************************** END READ THE VARIABLES FROM INPUT

    // Read Scalars
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi0_ff");
    read_binary(&env->emi0_ff, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi0");
    read_binary(&env->emi0, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "fossil_share");
    read_binary(&env->fossil_share, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "chi");
    read_binary(&env->chi, variablename, 1); // SET VARIABLE
    // price_clean0_world is set as global
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S0");
    read_binary(&env->S0, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S1");
    read_binary(&env->S1, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S2");
    read_binary(&env->S2, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "S3");
    read_binary(&env->S3, variablename, 1); // SET VARIABLE
    // S_preind set as global
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp1");
    read_binary(&env->temp1, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp2");
    read_binary(&env->temp2, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "temp0_global");
    read_binary(&env->temp0_global, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "natal0");
    read_binary(&env->natal0, variablename, 1); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "natal20");
    read_binary(&env->natal20, variablename, 1); // SET VARIABLE

    // Read arrays in stack
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "cost_emi_param");
    read_binary(env->cost_emi_param, variablename, NCOSTEMIPARAM); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "clean_energy_data");
    read_binary(env->clean_energy_data, variablename, NCLEANENERGY); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi_ff_data");
    read_binary(env->emi_ff_data, variablename, T_BACK); // SET VARIABLE
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "emi_ff_data_tend");
    read_binary(env->emi_ff_data_tend, variablename, T_BACK); // SET VARIABLE

    // Guesses
    // Guess for coefficients on the natality rate function.
    int i = 0;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    i++;
    env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
    // Guess for the elasticity of fossil fuel productivity growth to global real_t GDP growth
    env->upsilon_fossil_i = GUESS_upsilon_fossil_i;
    // Guess for the elasticity of clean energy productivity growth to global real_t GDP growth
    env->upsilon_clean_i = GUESS_upsilon_clean_i;
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "m2_i");
    read_binary(env->m2_i, variablename, NPOSLAND); // SET VARIABLE

    // Initialize Auxiliary to model_init_period, backward_climate, forward_climate
    //init_model_TBD(env);

    // **************************  STORE TRMULT_REDUCE AS SPARSE
    // There are two standard sparse-matrix storage schemes for the SpMxV operation: Compressed Storage by Rows (CSR)
    // Sparse Matrix Representation: Compressed Storage by Rows (CSR) https://www.geeksforgeeks.org/operations-sparse-matrices/
    env->ELEMENTS = 0;
    for (int i = 0; i < NPOSLAND; i++)
        for (int j = 0; j < NPOSLAND; j++)
            if(env->trmult_reduced[IPOSLAND(i, j)]>TRMULT_REDUCED_THRESHOLD)
                env->ELEMENTS++;
    printf("Total number of elements in trmult_reduced larger than %lf is: %d\n",TRMULT_REDUCED_THRESHOLD,env->ELEMENTS);
    
    // The CSR scheme contains three 1D arrays: nonzero, colIndex and rowStart
    env->trmult_sparse_.rowStart = (int*)malloc(NPOSLAND * sizeof(int));    // index e of first element in row i
    env->trmult_sparse_.colIndex = (int*)malloc(env->ELEMENTS * sizeof(int));    // Column j
    env->trmult_sparse_.value = (real_t *)malloc(env->ELEMENTS * sizeof(real_t));                     // value of element e
    int e = 0;
    for (int i = 0; i < NPOSLAND; i++){
        env->trmult_sparse_.rowStart[i]=-1;
        for (int j = 0; j < NPOSLAND; j++){
            real_t trmult_scalar= env->trmult_reduced[IPOSLAND(i, j)];
            if(trmult_scalar>TRMULT_REDUCED_THRESHOLD){
                env->trmult_sparse_.colIndex[e]=j;
                env->trmult_sparse_.value[e]=trmult_scalar;
                if(env->trmult_sparse_.rowStart[i]<0){
                    env->trmult_sparse_.rowStart[i]=e;
                }
                e=e+1;
            } // end if
        } // end j
    } // end i
    
    return;
}
void free_all(env_t *env)
{
    // Deallocate Memory
    free(env->H);
    free(env->prod0);
    free(env->pop5_dens);
    free(env->u0);
    free(env->a_norm);
    free(env->trmult_reduced);
    free(env->trmult_sparse_.rowStart);
    free(env->trmult_sparse_.colIndex);
    free(env->trmult_sparse_.value);
    free(env->C_vect);
    free(env->weight_pop_matrix);
    free(env->emi_no_ff);
    free(env->price_energy0);
    free(env->zeta_clean0);
    free(env->zeta_fossil0);
    free(env->forc_noCO2);
    free(env->temp0_local);
    free(env->temp_past);
    free(env->Delta_temp);
    free(env->scaler_temp);
    free(env->theta_amen_scen);
    free(env->theta_prod_scen);
    free(env->natal_data);
    free(env->pop_data);
    free(env->m2_i);

    free(env->l0_model);
    free(env->real_tgdp0_model);
    free(env->l20_model);
    free(env->real_tgdp20_model);
    free(env->temp20_local);
    
    return;
}
int main()
{
    env_t env;
    // Initialize all variables
    init_all(&env);
    // ---------------------------------------------------------------------------
    write_all(&env);
    // Update variables of period 0: l0_model,real_tgdp0_model,real_tgdp0_w (Given m2_i)
    model_initial_period(&env);//printf("env->real_tgdp0_model: %lf, %lf, %lf", env->real_tgdp0_model[0], env->real_tgdp0_model[NPOSLAND - 2], env->real_tgdp0_model[NPOSLAND - 1]);
    // Deallocate
    free_all(&env);
}

