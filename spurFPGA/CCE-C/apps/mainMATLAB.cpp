#include <iostream>
#include <stdlib.h>
#include <cstring> // memset,strcpy,strcat
#include <math.h>  // definitions.h
#include <cstdint>
#define DEBUG_MODE 1
using namespace std;
//#define real double
typedef double real;
typedef unsigned short small_idx_t;
#define INPUTPATH "C:/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/"
#define PRINTPATH "C:/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/output/"
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
#define IPOSLAND(i, j) ((i)*NPOSLAND + (j))     // location i-location j cost: col_idx*NROWS+ row_idx
#define ISCEN(i, j) ((i)*9 + (j))             // amen_scen, prod_scen (4x9)
#define IPOSLANDT(t, i) ((t)*NPOSLAND + (i)) // time t-location i: col_idx*NROWS+ row_idx
#define IDERIV(c,j)  ((c)*LENGTH_ISO * T_BACK_AUX + (j))    // LENGTH_ISO * T_BACK_AUX * LENGTH_COEFF_POP ----> DEVELOP: CHECK THIS
// *************************************************************
//                        BEGIN: definition.s
// *************************************************************
// 1. ****************************** main.m ******************************
// Initialize model with Benchmark Estimation: initialize(ind_RCP,maxCO2,eps)
const real env__ind_RCP = 8.5;    // RCP scenario for the CO2 emissions from non-fossil fuel combustion and the forcing from non-CO2sources; can take the value of 8.5, 6.0, 4.5 or 2.6;    8.5 is the baseline.
const real env__maxCO2 = 19500; // Total stock of CO2 available in the ground; 19500 is the baseline.
const real env__eps = 1.6;        // Elasticity of substitution between fossil fuels and clean energy;
// ----------------------------------------------
//    INITILIZE THE GUESSES
// Estimates natality function, migration costs and energy productivities
//  Guess on natality function, migration costs, upsilon_fossil and upsilon_clean
const real GUESS_coeff_pop_i[LENGTH_COEFF_POP] = {-0.69, 0, -5, -0.51, -0.25, -5, 2.88, -0.67}; // [ b0y, b1y, b1y', b2y, bsy, b1T, b2T, bsT ]
const real GUESS_upsilon_fossil_i = 1.15;
const real GUESS_upsilon_clean_i = 1.15;
const real GUESS_realgdp_growth_i = 1.017; // guess for global realgdp growth (backward_climate and forward_climate)
// ----------------------------------------------
// update_vect = [1 0.95 0.95]: Set speed of update for migration costs, upsilon_fossil and upsilon_clean
const real UPDATE_M2 = 1;
const real UPDATE_UPSILON_FOSSIL = 0.95;
const real UPDATE_UPSILON_CLEAN = 0.95;
// ------------------------ backward_climate.m
const real UPDATE_BW_L = 1.;    // speed of update when iterating over l
const real UPDATE_BW_EE = 1.;   // speed of update when iterating over CO2 emissions
const real UPDATE_BW_R = 1.;    // speed of update when iterating over GDP
// ------------------------ end backward_climate.m
// ------------------------ forward_climate.m
const real UPDATE_FW_EE = 1.;   // speed of update when iterating over CO2 emissions
const real UPDATE_FW_R = 1.;    // speed of update when iterating over GDP
// ------------------------ end forward_climate.m
// Tolerance of errors in the iteration: tol_vect = [ tol_clean tol_fossil tol_m2 tol_l tol_nlls tol_final_SSR tol_m2_inner tol_step ]';
#define TOLL_CLEAN ((real)(1.2))
#define TOLL_FOSSIL ((real)(2.5))
#define TOLL_M2 ((real)(1e9))
#define TOLL_L ((real)(1e9))
#define TOLL_NLLS ((real)(0))
#define TOLL_FINAL_SSR ((real)(1e-5))
#define TOLL_M2_INNER ((real)(1e-8))
#define TOLL_STEP ((real)(40))
#define TOLL_MODEL_INITIAL_PERIOD ((real)(1e-2)) // model_initial_period.m
// 2. ****************************** backward_climate.m ******************************
// ----------------------------------------------
#define BW_tol ((real)(1e-2))       // tolerance for error when iterating over uhat
#define BW_tol_l ((real)(1e+1))     // tolerance for error when iterating over l
#define BW_tol_e ((real)(1e-3))     // tolerance for error when iterating over CO2 emissions
#define BW_tol_realgdp ((real)(1e-2))// tolerance for error when iterating over real GDP
// 3. ****************************** forward_climate.m ******************************
#define FW_tol ((real)(1e-2))       // tolerance for error when iterating over uhat
#define FW_tol_e ((real)(1e-2))     // tolerance for error when iterating over CO2 emissions
#define FW_tol_realgdp ((real)(1e-2))// tolerance for error when iterating over real GDP
// 2. ****************************** initialize.m ******************************
// 1. Initialize the Parameters
const real env__lbar = 5.9174e+09; // total population
const real env__lambda = 0.32;       // congestion externalities
const real env__gamma1 = 0.319;       // elasticity of tomorrow's productivity relative to today's innovation
const real env__gamma2 = 0.99246;  // elasticity of tomorrow's productivity relative to today's productivity
const real env__eta = 1.;           // parameter driving scale of technology diffusion
const real env__mu = 0.8;           // labor share in production
const real env__nu = 0.15;           // intercept parameter in innovation cost function
const real env__ksi = 125;           // elasticity of innovation costs relative to innovation
const real env__sigma = 4.;           // elasticity of substitution
const real env__psi_util = 0.045;  // wellbeing parameter
const real env__beta = 0.965;       // discount factor for present discounted values
const real env__alpha = 0.06;       // agglomeration externalities
const real env__theta = 6.5;       // variance productivity shocks
const real env__Omega = 0.5;       // variance taste shocks
// NOT USED const real env__max_cumCO2 = maxCO2;                            // total stock of CO2 in the ground
//  USE env__eps const real env__epsilon = eps;                                // elasticity of substitution between fossil fuels and clean energy
const real env__tCO2_toe = 2.8466;                                                  // conversion factor: GtCO2 per Gtoe
const real env__price_fossil0_world = 72.99 * pow(10., 9.);                          // price of fossil fuels in usd/GtCO2
const real env__price_clean0_world = 1.997515248601176e+11; // ****** DEVELOP ****** read from outside: missing from initialize.m: price_clean0_world = price_clean0_world/GDPpc0; % usdP/GtCO2
//1.15 * 76.34 * pow(10., 9.) / env__tCO2_toe; // price of clean energy in usd/GtCO2 --> fundamentals.m is in usd/Gtoe
// 10. Set carbon circulation parameters (initialize.m)
// Set parameters regarding depreciation of CO2 in the atmosphere
const real env__a0 = 0.2173; // share of CO2 emissions remaining in the atmosphere forever
const real env__a1 = 0.2240; // share of CO2 emissions associated with the timescale b1
const real env__a2 = 0.2824;
const real env__a3 = 0.2763;
const real env__b1 = 394.4;
const real env__b2 = 36.54;
const real env__b3 = 4.304;
const real env__S_preind = 2200; // CO2 stock in pre-industrial era
// 11. Set forcing parameters
const real env__forc_sens = 5.35; // forcing sensitivity
//// 12. Set global temperature parameters
// Set global temperature parameters
const real env__c1 = 0.631; // temperature evolution parameters
const real env__c2 = 0.429;
const real env__d1 = 8.4;
const real env__d2 = 409.5;
// USED ONLY IN PLOTS: const real env__temp_preind = 8.1; // temperature in pre-industrial era
//// 21. Set numerical restrictions on natality functions
const real env__b0y_max = 0.045;
const real env__b1y_min = 0.01;
const real env__b1y_max = 0.03;
const real env__b2y_min = -0.00090;
const real env__b2y_max = -0.00050;
const real env__b2T_max = 0.015;
const real env__bsy_min = 0;
const real env__bsy_max = 8;
const real env__bsT_min = 14;
const real env__bsT_max = 22;
//const real natal_param[10] = {b0y_max, b1y_min, b1y_max, b2y_min, b2y_max, b2T_max, bsy_min, bsy_max, bsT_min, bsT_max};
//// 22. Define colors and variable names for plots
// 3. ****************************** fundamentals.m ******************************
// Set energy parameters: DOUBLE DECLARATION: env__tCO2_toe, env__fossil0, env__clean0
/** Simulation settings: Set numerical parameters for the estimation of the natality function */
const real size_deriv = 1e-5;
const real scal_nlls = 1e-5;
const real lev_nlls = 1e-3;
const int count_max = 50;
// *************************************************************
//                        END: definition.h
// *************************************************************
// Environmental Struct
typedef struct env_t
{
    real *H;                              // NPOSLAND
    real *prod0;                          // productivities in 2000
    real *pop5_dens;                      //
    real *u0;                              // utility in 2000
    real *a_norm;                          // amenities in 2000
    real *trmult_reduced;                  // Bilateral trade cost on Earth cells at t=0 only
    small_idx_t *C_vect;                  // national demarcations with H0>0
    real emi0_ff;                          // Global CO2 emissions from fossil fuels for 2000 (interpreted *****) - scalar
    real *emi_no_ff;                      // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC, N2600x1 (600x1)
    real emi0;                              // total CO2 emissions for 2000, scalar
    real fossil_share;                      // Construct share of fossil fuels in energy composite, scalar
    real chi;                              // Construct share of energy in production, equations (7) and (44), scalar
    real cost_CO2_data;                      // Cost extraction data, 202x2
    real cost_emi_param[NCOSTEMIPARAM];      // Redefine extraction cost function 1x7: [cost_emi_param_f maxCO2 3];
    real price_clean0_world;              // Define normalization relative to Princeton wage: usdP/GtCO2
    real *price_energy0;                  //, (17048x1)
    real *zeta_clean0;                      // Construct initial energy productivities, (17048x1)
    real *zeta_fossil0;                      //, (17048x1)
    real S0;                              // Initialize CO2 stock layers, equations (38) and (39), scalar
    real S1;                              // , scalar
    real S2;                              // , scalar
    real S3;                              // , scalar
    real *forc_noCO2;                      // Read non CO2 radiative forcing, 601x1
    real temp1;                              // Initialize temperature layers, equation (41), scalar
    real temp2;                              // , scalar
    real temp0_global;                      // , scalar
    real *temp0_local;                      // Local temperatures, 17048x1
    real *temp_past;                      // , 17048x51 (NPOSLAND,T_BACK_AUX)
    real *Delta_temp;                      // , 17048x50 (NPOSLAND,T_BACK)
    real *scaler_temp;                      // , 17048x1
    real *theta_amen_scen;                  // 4x9
    real *theta_prod_scen;                  // 4x9
    real *natal_data;                      // data for years < 2001, 8568x1
    real *pop_data;                          // data for years < 2001, 8568x1
    real natal0;                          // Natality rates of 2000, scalar
    real natal20;                          // Natality rates of 2020, scalar
    real clean_energy_data[NCLEANENERGY]; // 35x1
    real emi_ff_data[T_BACK];              // Historical fossil fuel CO2 emission and its trend, 50x1, TBACKx1
    real emi_ff_data_tend[T_BACK];          // , 50x1, TBACKx1
    real coeff_pop_i[LENGTH_COEFF_POP];                  // Guess for coefficients on the natality rate function.
    real upsilon_fossil_i;                  // Guess for the elasticity of fossil fuel productivity growth to global real GDP growth    ****** DEVELOP ****** --> MAY NOT BE NEEDED
    real upsilon_clean_i;                  // Guess for the elasticity of clean energy productivity growth to global real GDP growth   ****** DEVELOP ****** --> MAY NOT BE NEEDED
    real *m2_i;                              // Load guess for migration costs (estim_model.m)

    // Auxiliary Variables
    real *l0_model;          // NPOSLANDx1, 17048x1
    real *realgdp0_model; // NPOSLANDx1, 17048x1
    // -------------- model_initial_period
    int dummy_m; // 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    real flat;
    real exp_uhatL;
    real exp_uhatR;
    real uhat_f_exp;
    /*
    real *FL_H_m2_left; // model_initial_period
    real *FR_H_m2_left; // model_initial_period
    real FL_H_m2_right_exp;
    real FR_H_m2_right_exp;
    real FL_a_norm_exp;
    real FR_a_norm_exp;
    real FL_prod0_exp;
    real FR_prod0_exp;
    real FL_price_energy0_exp;
    real FR_price_energy0_exp;
    real flatL;
    real flatR;
    real aux_denom;
     */
    // ------------- end: model_initial_period
    real *l20_model;       // NPOSLANDx1, 17048x1   ---> natal_fct (consider printing)
    real *realgdp20_model; // NPOSLANDx1, 17048x1     ---> natal_fct (consider printing)
    real *temp20_local;       // NPOSLANDx1, 17048x1     ---> natal_fct (consider printing)
    // ------------- begin: backward_climate
    real const_phi;
    real const_energy;    // notice this may differ in forward and backward looking --> check
    /*
    real natural;        // naturalL,naturalR not needed if we have BL_H_m2_left,BL_H_m2_right
    real *BL_H_m2_left; // backward_climate
    real *BR_H_m2_left; // backward_climate
    real BL_H_m2_right_exp;
    real BR_H_m2_right_exp;
    real BL_a_norm_exp;
    real BR_a_norm_exp;
    real BL_prod0_exp;
    real BR_prod0_exp;
    real BL_price_energy0_exp;
    real BR_price_energy0_exp;
    real BW_exp_uhatR;
    real BW_uhat_f_exp;
     */
    // ------------- begin: natal_fct
    real realgdp0_w;
    real b0T;               // b0T, equation (31)
    real bw;                // bw, equation (33)
    real logi_bsT_fct_7;    // logi_bsT_fct(coeff_pop[7]);
    // Auxiliary to natal_fct_logrealgdp
    real logi_bsy_fct_4;    //logi_bsy_fct(coeff_pop[4]);
    real logi_b0y_fct_0;    //logi_b0y_fct(coeff_pop[0]);
    real logi_b2y_fct_3;    //logi_b2y_fct(coeff_pop[3]);
    real logi_b1y_fct_1;    //logi_b1y_fct(coeff_pop[1]);
    real minus_exp_2;       //-exp(coeff_pop[2]);
    // Construct numerator of temperature component of natality rate function, equation (24)
    real natal_coeff_6;     //logi_b2T_fct(coeff_pop[6]);
    real natal_coeff_5;     // -exp(coeff_pop[5]);

} env_t;
// *************************************************************
//                    backward/forward_climate
// *************************************************************
typedef struct sym_t
{
    // Backward
    real *l_b;
    real *realgdp_b;
    real *emiCO2_b;
    real *clean_b;
    // Forward
    real *l;
    real *prod;
    real *realgdp;
    real *amen;
    real *temp_local;
    real *price_emi;
    real *price_clean;
    /*
    real * u;

    real *amen;
    real *emiCO2_ff;
    real *emiCO2_total;
    real *stockCO2;
    real *temp_global;
    real *temp_local;
    real *price_fossil;
    real *clean;
    real *price_clean;
    real *net_births;
    */

} sym_t;

void write_binary(real *X_var, char *variablename, int dim_n)
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
void read_binary(real *X_var, char *variablename, int dim_n)
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
void debug_init_backward_climate(env_t *env, real *theta_amen_temp)
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
    printf("\n realgdp0_w: %.16lf", env->realgdp0_w);
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_temp_past");
    write_binary(env->temp_past, variablename, (int)(NPOSLAND * T_BACK_AUX)); // SET VARIABLE
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "bwd_theta_amen_temp");
    write_binary(theta_amen_temp, variablename, (int)(NPOSLAND * T_BACK)); // SET VARIABLE
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
    real *C_vect_real = (real *)malloc(NPOSLAND * sizeof(real));
    for (int i = 0; i < NPOSLAND; i++)
        C_vect_real[i] = (real)env->C_vect[i];
    strcpy(variablename, "C_vect");
    write_binary(C_vect_real, variablename, NPOSLAND); // ************* VARIABLE
    free(C_vect_real);
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
void update_period20(env_t *env,sym_t *sym_)
/*
    Input: forward calculated sym_->l, sym_->realgdp, sym_->temp_local
    Update: l20,realgdp20,temp20 guesses
 */
{
    for (int i = 0; i < NPOSLAND; i++){
        int is = IPOSLANDT(19, i);
        // Update Period 20
        env->l20_model[i] = sym_->l[is];
        env->realgdp20_model[i] = sym_->realgdp[is];
        env->temp20_local[i] = sym_->temp_local[is];
    }
}
void error_sqrt_sum_squared_residual(const real *A_new,const real *A_old,real *error){
    *error =0.;
    for (int i = 0; i < NPOSLAND; i++){
        int is = IPOSLANDT(19, i);
        real diff = A_new[i] - A_old[is];
        *error +=diff*diff;
    }
    *error =sqrt(*error);
}
/*
void compute_error_update20(env_t *env,sym_t *sym_,const real *A_new,const real *A_old,real *error){
    
    *error =0.;
    for (int i = 0; i < NPOSLAND; i++){
        int is = IPOSLANDT(19, i);
        real diff = A_new[i] - A_old[is];
        *error +=diff*diff;
        
        // Update Period 20
        env->l20_model[i] = sym_->l[is];
        env->realgdp20_model[i] = sym_->realgdp[is];
        env->temp20_local[i] = sym_->temp_local[is];
    }
}
*/

// *************************************************************
//                        BEGIN: KERNEL (estim_model)
// *************************************************************
// ==================================== NLLS
void NLLS(env_t *env,sym_t *sym_){
    // 3. Perform NLLS on natality function
    real *logrealgdp_c = (real *)malloc(LENGTH_ISO * T_BACK_AUX * sizeof(real)); // LENGTH_ISO == length_C_vect
    real *temp_c = (real *)malloc(LENGTH_ISO * T_BACK_AUX * sizeof(real));       // LENGTH_ISO == length_C_vect
    real logrealgdp_w[T_BACK_AUX];
    
    // TASK 0:
    /*
    1. Run matlab
    2. Store in binary: l_b,~,~,realgdp_b,~,emiCO2_b,temp_b,~,clean_b,
    3. Read into sym_.l_b, sym_.realgdp_b,....
     */
    //
    // TASK 1
    // Preallocate for t=0
    /*
    logrealgdp_c[0]=;
    temp_c[0]=;
    logrealgdp_w[0]=;
    // Preallocate for t>0
    for(uint8_t t=1;t<T_BACK_AUX;t++){
        j = T_BACK_AUX-1-t;
        for(i < NPOSLAND){
        logrealgdp_c[t]= sym_->l_b[j]sym_->realgdp_b[j]
        accumarray: use matlab coder to get insight on how to implement it (Suggestion you can also do otherwise.)
        }
     }
    */
    // Set numerical parameters
    real SSR_f = 1. + TOLL_FINAL_SSR;
    // length_coeff_pop = length(coeff_pop_i); ---> LENGTH_COEFF_POP == length_coeff_pop
    real error_nlls = 1. + TOLL_NLLS;
    int count = 1;
    
    // Update Natality Function
    while ((error_nlls > TOLL_NLLS) & (SSR_f > TOLL_FINAL_SSR) & (count < count_max)){
        
        // Construct derivative
        real *deriv_i = (real *)malloc(LENGTH_ISO * T_BACK_AUX * LENGTH_COEFF_POP * sizeof(real)); // LENGTH_ISO == length_C_vect=168, T_BACK_AUX==51
        real coeff_pop_p[LENGTH_COEFF_POP];
        real coeff_pop_m[LENGTH_COEFF_POP];
        for(uint8_t c = 0;c<LENGTH_COEFF_POP;c++){
            
            // Construct coeff_pop_p and coeff_pop_m
            // Initialize p and m
            for(uint8_t cp = 0;cp<LENGTH_COEFF_POP;cp++){
                coeff_pop_p[cp] = env->coeff_pop_i[cp];
                coeff_pop_m[cp] = env->coeff_pop_i[cp];
            }
            // Create Wedge at c
            coeff_pop_p[c] = coeff_pop_p[c] + size_deriv;
            coeff_pop_m[c] = coeff_pop_m[c] - size_deriv;
            
            // Construct net births at country level
            for(uint8_t t = 0; t<T_BACK_AUX; t++){
                /*
                real natal_model_p=;
                real natal_model_m=;
                deriv_i[IDERIV(c,)]=natal_model_p-natal_model_m/(2.*size_deriv);
                // CHECK IDERIV(c,j)
                // NEED TO REWRITE THE NATALITY FUNCTON:
                    1. The upper bound of the loop in natal_fct is not function of NPOSLAND but is LENGTH ISO HERE. So:
                        - we need a natality function with two fixed-sized loops but same kernel in the loop
                        - we need to pass temp as vector directly at t+i position. I will explain you more when we talk
                 */
            }
        }
        
        // GOAL IS TO CONSTRUCT as fast as possible:  deriv_i'*weight_pop_matrix*deriv_i
        
        // % Construct net births at country level: I DON'T THINK YOU NEED: natal_model_aux_Cvect_i --> use directly natal_model_i
        // Construct error and SSR: natal_data is in env->natal_data
        // Regress errors on natal_model_i: USE ROUTINES THAT YOU HAVE CREATED and TESTED
        
        // Set step line 185-218: create a function for this called coef_pop_update
        
        
        
        //
        free(deriv_i);

    }
        
        
    
    
    free(logrealgdp_c);
    free(temp_c);
    return;
}
// ==================================== NATALITY FUNCTION
real logi_b2T_fct(real x){
    return env__b2T_max/(1.+exp(-(x)));
}
real logi_b0y_fct(real x){
    return env__b0y_max/(1.+exp(-(x)));
}
real logi_b1y_fct(real x){
    return env__b1y_min + (env__b1y_max - env__b1y_min)/(1.+exp(-(x)));
}
real logi_b2y_fct(real x){
    return env__b2y_min + (env__b2y_max - env__b2y_min)/(1.+exp(-(x)));
}
real logi_bsy_fct(real x){
    return env__bsy_min + (env__bsy_max - env__bsy_min)/(1.+exp(-(x)));
}
real logi_bsT_fct(real x){
    return env__bsT_min + (env__bsT_max - env__bsT_min)/(1.+exp(-(x)));
}
//real natal_fct_logrealgdp(env_t *env,const real logrealgdp,const real minus_exp_2,const real logi_b0y_fct_0,const real logi_b1y_fct_1,const real logi_b2y_fct_3,const real logi_bsy_fct_4){
real natal_fct_logrealgdp(env_t *env,const real logrealgdp){
    // Construct income component of natality rate function, equation (23)
    real square = (logrealgdp-env->logi_bsy_fct_4)*(logrealgdp-env->logi_bsy_fct_4);
    real x =(env->logi_b0y_fct_0 +(env->logi_b2y_fct_3-env->logi_b0y_fct_0)*exp(-env->logi_b1y_fct_1*square)
             )*(logrealgdp<env->logi_bsy_fct_4) +
            (env->logi_b2y_fct_3*exp(env->minus_exp_2*square)
            )*(logrealgdp>=env->logi_bsy_fct_4);
    return x;
}
void update_b0T_bw_coeff_pop(env_t *env,const real *coeff_pop)
// // Construct b0T, equation (31) bw, equation (33) and auxiliary variables to natal_fct
/*
    Input: it depends on time 0 and time 20 variables. ---> Update when you change those
    Output: env->b0T and env->bw
 */
{

    real logrealgdp0_w=log(env->realgdp0_w);
    real sum_l20H=0.;
    real sum_coef5pop0=0.;
    real sum_nat_gdp0pop0=0.;
    real sum_bw_1=0.;
    real sum_bw_2=0.;
    real logrealgdp20_w=0.;
    
    // Store auxiliary variables of natal_fct depending on coeff_pop
    env->logi_bsT_fct_7 = logi_bsT_fct(coeff_pop[7]);
    real minus_exp_5 = -exp(coeff_pop[5]);
    real logi_b2T_fct_6 = logi_b2T_fct(coeff_pop[6]);
    // Auxiliary to natal_fct_logrealgdp
    env->logi_bsy_fct_4=logi_bsy_fct(coeff_pop[4]);
    env->logi_b0y_fct_0 = logi_b0y_fct(coeff_pop[0]);
    env->logi_b2y_fct_3 = logi_b2y_fct(coeff_pop[3]);
    env->logi_b1y_fct_1 = logi_b1y_fct(coeff_pop[1]);
    env->minus_exp_2 = -exp(coeff_pop[2]);
    // Construct numerator of temperature component of natality rate function, equation (24)
    env->natal_coeff_6 = logi_b2T_fct(coeff_pop[6]);
    env->natal_coeff_5 = -exp(coeff_pop[5]);
        
    for (int i = 0; i < NPOSLAND; i++){
        
        real pop0_sh = env->l0_model[i]*env->H[i]/env__lbar;
        real square = (env->temp0_local[i]-env->logi_bsT_fct_7)*(env->temp0_local[i]-env->logi_bsT_fct_7);
        sum_coef5pop0    +=exp(minus_exp_5*square)*pop0_sh;
        //natal_fct_logrealgdp(env,log(env->realgdp0_model[i]),minus_exp_2,logi_b0y_fct_0,logi_b1y_fct_1,logi_b2y_fct_3,logi_bsy_fct_4)
        sum_nat_gdp0pop0+=natal_fct_logrealgdp(env,log(env->realgdp0_model[i]))*pop0_sh;
        
        real pop20_sh = env->l20_model[i]*env->H[i];
        sum_l20H        +=pop20_sh;
        real square20=(env->temp20_local[i]-env->logi_bsT_fct_7)*(env->temp20_local[i]-env->logi_bsT_fct_7);
        sum_bw_1        += logi_b2T_fct_6*exp(minus_exp_5*square20)*pop20_sh;
        sum_bw_2        += natal_fct_logrealgdp(env,log(env->realgdp20_model[i]))*pop20_sh;
        logrealgdp20_w+=env->realgdp20_model[i]*pop20_sh;
    }
    sum_bw_1=sum_bw_1/sum_l20H;
    sum_bw_2=sum_bw_2/sum_l20H;
    logrealgdp20_w=log(logrealgdp20_w/sum_l20H);
    // Construct b0T, equation (31)
    env->b0T = 2.0*env->natal0 - logi_b2T_fct(coeff_pop[6])*sum_coef5pop0 - 2.0*sum_nat_gdp0pop0;
    // Construct bw, equation (33)
    env->bw = log(-1.+ (env->b0T + sum_bw_1)/(env->natal20 - sum_bw_2))/(logrealgdp20_w-logrealgdp0_w);
    
    
}
//real natal_fct_kernel(env_t *env,const real temp,const real logi_bsT_fct_7,const real b0T,const real natal_coeff_6,const real natal_coeff_5,const real natal_fct_temp_denom,const real natal_fct_logrealgdp_scalar){
real natal_fct_kernel(env_t *env,const real temp,const real realgdp,const real natal_fct_temp_denom){
    // **************************************************************
    real square = (temp-env->logi_bsT_fct_7)*(temp-env->logi_bsT_fct_7);
    real natal_fct_temp_num = env->b0T + env->natal_coeff_6*exp(env->natal_coeff_5*square);
    real natal_fct_logrealgdp_scalar = natal_fct_logrealgdp(env,log(realgdp));
    // Construct natality functions
    real net_births = natal_fct_temp_num / natal_fct_temp_denom + natal_fct_logrealgdp_scalar;
    return net_births;
    // **************************************************************
}
void update_globalpop(env_t *env,const real *l_vec,const real *realgdp,const real realgdp_w,const real *temp,const real *coeff_pop,real *lbar_time)
/*
 // Update population size
 Input: b0T,bw
 Returns: lbar_time
 */
{
    /*
    real natal_fct_temp_denom, logi_bsT_fct_7,logi_bsy_fct_4,logi_b0y_fct_0,logi_b2y_fct_3,logi_b1y_fct_1,minus_exp_2,natal_coeff_6,natal_coeff_5;
    natal_fct_auxiliary_variables(realgdp_w,env->realgdp0_w,env->bw,coeff_pop,&natal_fct_temp_denom,                            &logi_bsT_fct_7,&logi_bsy_fct_4,&logi_b0y_fct_0,&logi_b2y_fct_3,&logi_b1y_fct_1,&minus_exp_2,&natal_coeff_6,&natal_coeff_5);
    */
    // Update global population
    real logrealgdp_w= log(realgdp_w);
    real logrealgdp0_w=log(env->realgdp0_w);
    real natal_fct_temp_denom = (1.+exp(env->bw*(logrealgdp_w-logrealgdp0_w)));        // current logrealgdp_w
    
    real ltilde1=0.;
    for (int i = 0; i < NPOSLAND; i++){
        
        // Updated Net Births
        real net_births = natal_fct_kernel(env,temp[i],realgdp[i],natal_fct_temp_denom);
        //real net_births = natal_fct_kernel(env,temp[i],logi_bsT_fct_7,env->b0T,natal_coeff_6,natal_coeff_5,natal_fct_temp_denom,natal_fct_logrealgdp_scalar);
        // Global Population
        ltilde1+=net_births*l_vec[i]*env->H[i];
    }
    *lbar_time=ltilde1;
    /*
    // Construct denominator of temperature component of natality rate function, equation (24)
    real logrealgdp_w= log(realgdp_w);
    real logrealgdp0_w=log(env->realgdp0_w);
    real natal_fct_temp_denom = (1.+exp(env->bw*(logrealgdp_w-logrealgdp0_w)));        // current logrealgdp_w
    // Auxiliary
    real logi_bsT_fct_7 = logi_bsT_fct(coeff_pop[7]);
    // Auxiliary to natal_fct_logrealgdp
    real logi_bsy_fct_4=logi_bsy_fct(coeff_pop[4]);
    real logi_b0y_fct_0 = logi_b0y_fct(coeff_pop[0]);
    real logi_b2y_fct_3 = logi_b2y_fct(coeff_pop[3]);
    real logi_b1y_fct_1 = logi_b1y_fct(coeff_pop[1]);
    real minus_exp_2 = -exp(coeff_pop[2]);
    // Construct numerator of temperature component of natality rate function, equation (24)
    real natal_coeff_6 = logi_b2T_fct(coeff_pop[6]);
    real natal_coeff_5 = -exp(coeff_pop[5]);
    
    // Update global population
    real ltilde1=0.;
    for (int i = 0; i < NPOSLAND; i++){
        
        real square = (temp[i]-logi_bsT_fct_7)*(temp[i]-logi_bsT_fct_7);
        real natal_fct_temp_num = env->b0T + natal_coeff_6*exp(natal_coeff_5*square);
        // Construct natality functions
        real logrealgdp= log(realgdp[i]); // Calculate real GDP per capita, equation (4)
        real natal_fct_logrealgdp_scalar = natal_fct_logrealgdp(env,logrealgdp,minus_exp_2,logi_b0y_fct_0,logi_b1y_fct_1,logi_b2y_fct_3,logi_bsy_fct_4);
        real net_births = natal_fct_temp_num / natal_fct_temp_denom + natal_fct_logrealgdp_scalar;
        //complex function???? real(natal_fct_temp_num / natal_fct_temp_denom + natal_fct_logrealgdp(env,logrealgdp)); ****** DEVELOP ******
        ltilde1+=net_births*l_vec[i]*env->H[i];
    }
    *lbar_time=ltilde1;
    */
}
/*
void natal_fct_auxiliary_variables(const real realgdp_w,
                                   const real realgdp0_w,
                                   const real bw,
                                   const real *coeff_pop,
                                   real *natal_fct_temp_denom,
                                   real *logi_bsT_fct_7,
                                   real *logi_bsy_fct_4,
                                   real *logi_b0y_fct_0,
                                   real *logi_b2y_fct_3,
                                   real *logi_b1y_fct_1,
                                   real *minus_exp_2,
                                   real *natal_coeff_6,
                                   real *natal_coeff_5){
    
    // ******************************** Updated Net Births
    // Construct denominator of temperature component of natality rate function, equation (24)
    real logrealgdp_w= log(realgdp_w);
    real logrealgdp0_w=log(realgdp0_w);
    *natal_fct_temp_denom = (1.+exp(bw*(logrealgdp_w-logrealgdp0_w)));        // current logrealgdp_w
    // Auxiliary
    *logi_bsT_fct_7 = logi_bsT_fct(coeff_pop[7]);
    // Auxiliary to natal_fct_logrealgdp
    *logi_bsy_fct_4=logi_bsy_fct(coeff_pop[4]);
    *logi_b0y_fct_0 = logi_b0y_fct(coeff_pop[0]);
    *logi_b2y_fct_3 = logi_b2y_fct(coeff_pop[3]);
    *logi_b1y_fct_1 = logi_b1y_fct(coeff_pop[1]);
    *minus_exp_2 = -exp(coeff_pop[2]);
    // Construct numerator of temperature component of natality rate function, equation (24)
    *natal_coeff_6 = logi_b2T_fct(coeff_pop[6]);
    *natal_coeff_5 = -exp(coeff_pop[5]);
}
 */
/*
void natal_fct(env_t *env,const real *realgdp,const real realgdp_w,const real *temp,const real *coeff_pop,real *natal_fct_val){
    /*
    real sum_l20H=0.;
    real sum_coef5pop0=0.;
    real sum_nat_gdp0pop0=0.;
    real sum_bw_1=0.;
    real sum_bw_2=0.;
    real logrealgdp20_w=0.;
    // Auxiliary
    real logi_bsT_fct_7 = logi_bsT_fct(coeff_pop[7]);
    real minus_exp_5 = -exp(coeff_pop[5]);
    real logi_b2T_fct_6 = logi_b2T_fct(coeff_pop[6]);
        
    for (int i = 0; i < NPOSLAND; i++){
        
        real pop0_sh = env->l0_model[i]*env->H[i]/env__lbar;
        real square = (env->temp0_local[i]-logi_bsT_fct_7)*(env->temp0_local[i]-logi_bsT_fct_7);
        sum_coef5pop0    +=exp(minus_exp_5*square)*pop0_sh;
        sum_nat_gdp0pop0+=natal_fct_logrealgdp(env,log(env->realgdp0_model[i]),minus_exp_2,logi_b0y_fct_0,logi_b1y_fct_1,logi_b2y_fct_3,logi_bsy_fct_4)*pop0_sh;
        
        real pop20_sh = env->l20_model[i]*env->H[i];
        sum_l20H        +=pop20_sh;
        real square20=(env->temp20_local[i]-logi_bsT_fct_7)*(env->temp20_local[i]-logi_bsT_fct_7);
        sum_bw_1        += logi_b2T_fct_6*exp(minus_exp_5*square20)*pop20_sh;
        sum_bw_2        += natal_fct_logrealgdp(env,log(env->realgdp20_model[i]),minus_exp_2,logi_b0y_fct_0,logi_b1y_fct_1,logi_b2y_fct_3,logi_bsy_fct_4)*pop20_sh;
        logrealgdp20_w+=env->realgdp20_model[i]*pop20_sh;
    }
    sum_bw_1=sum_bw_1/sum_l20H;
    sum_bw_2=sum_bw_2/sum_l20H;
    logrealgdp20_w=log(logrealgdp20_w/sum_l20H);
    // Construct b0T, equation (31)
    real b0T = 2.0*env->natal0 - logi_b2T_fct(coeff_pop[6])*sum_coef5pop0 - 2.0*sum_nat_gdp0pop0;
    // Construct bw, equation (33)
    real bw = log(-1.+ (b0T + sum_bw_1)/(env->natal20 - sum_bw_2))/(logrealgdp20_w-logrealgdp0_w);
    // Construct denominator of temperature component of natality rate function, equation (24)
    real logrealgdp_w= log(realgdp_w);
    real logrealgdp0_w=log(env->realgdp0_w);
    real natal_fct_temp_denom = (1.+exp(env->bw*(logrealgdp_w-logrealgdp0_w)));        // current logrealgdp_w
    
    
    // Construct denominator of temperature component of natality rate function, equation (24)
    real logrealgdp_w= log(realgdp_w);
    real logrealgdp0_w=log(env->realgdp0_w);
    real natal_fct_temp_denom = (1.+exp(env->bw*(logrealgdp_w-logrealgdp0_w)));        // current logrealgdp_w
     
    // Auxiliary
    real logi_bsT_fct_7 = logi_bsT_fct(coeff_pop[7]);
    // Auxiliary to natal_fct_logrealgdp
    real logi_bsy_fct_4=logi_bsy_fct(coeff_pop[4]);
    real logi_b0y_fct_0 = logi_b0y_fct(coeff_pop[0]);
    real logi_b2y_fct_3 = logi_b2y_fct(coeff_pop[3]);
    real logi_b1y_fct_1 = logi_b1y_fct(coeff_pop[1]);
    real minus_exp_2 = -exp(coeff_pop[2]);
    
    // Construct numerator of temperature component of natality rate function, equation (24)
    real natal_coeff_6 = logi_b2T_fct(coeff_pop[6]);
    real natal_coeff_5 = -exp(coeff_pop[5]);
    for (int i = 0; i < NPOSLAND; i++){
        real square = (temp[i]-logi_bsT_fct_7)*(temp[i]-logi_bsT_fct_7);
        real natal_fct_temp_num = env->b0T + natal_coeff_6*exp(natal_coeff_5*square);
        real logrealgdp= log(realgdp[i]); // Calculate real GDP per capita, equation (4)
        // Construct natality functions
        natal_fct_val[i] = natal_fct_temp_num / natal_fct_temp_denom + natal_fct_logrealgdp(env,logrealgdp);
        
        //complex function???? real(natal_fct_temp_num / natal_fct_temp_denom + natal_fct_logrealgdp(env,logrealgdp)); ****** DEVELOP ******
    }
}
*/
// ==================================== END NATALITY FUNCTION
void loop_uhat(real tol, real *trmult_reduced, real *L, real L_exp,
               real *uhat_i, real *R, real R_exp)
{
    real integral[NPOSLAND];
    real error = tol + 1.;
    int iter = 0;
    while (error >= tol)
    {
        // Compute accuracy and update the guess
        for (int i = 0; i < NPOSLAND; i++)
            integral[i] = R[i] * pow(uhat_i[i], R_exp);
        error = 0;
        for (int i = 0; i < NPOSLAND; i++)
        {
            real rhs = 0;
            for (int j = 0; j < NPOSLAND; j++)
                rhs += trmult_reduced[IPOSLAND(i, j)] * integral[j];
            real uhat_f = L[i] * pow(rhs, L_exp);
            real deviation = (uhat_i[i] - uhat_f);
            error += deviation * deviation;
            // Update the Guess
            uhat_i[i] = uhat_f;
        }
        iter = iter + 1;
#ifdef DEBUG_MODE
        printf("%d\n", iter);
#endif
    } // end while
#ifdef DEBUG_MODE
    printf("Error: %.16lf\n", error);
#endif
}
void costC02_fun(env_t *env, real *cumCO2, real *costCO2_fct)
{
    *costCO2_fct = env->cost_emi_param[0] / (env->cost_emi_param[1] + exp(-env->cost_emi_param[2] * (*cumCO2 - env->cost_emi_param[3]))) -
                   env->cost_emi_param[4] * pow((env->cost_emi_param[5] / (*cumCO2 - env->cost_emi_param[5])), env->cost_emi_param[6]);
}
real theta_temp_fun(const real min, const real diff, const real steep, const real center, const real temp)
// Set damage function level by confidence interval
{
    real theta_temp = min + diff / (1. + exp(steep * (temp - center)));
    return theta_temp;
}
real climate_theta_fwd(const real min, const real max, const real center, const real steep, const real temp)
{
    real diff = (max - min);
    real theta_temp = theta_temp_fun(min,diff,steep,center,temp);// theta_temp: theta_amen_temp or theta_real_temp
                    //min + diff / (1. + exp(steep * (past[IPOSLANDT(t, i)] - center)));
#ifdef DEBUG_MODE
    printf("\nmin=%.16lf,max=%.16lf,center=%.16lf,steep=%.16lf\n", min, max, center, steep);
    printf("\n\nVerify climate theta: %lf\n",theta_temp);
#endif
    return theta_temp;
}
void climate_theta(size_t T, const real min, const real max, const real center, const real steep, real *past, real *theta_temp)
{

#ifdef DEBUG_MODE
    printf("\n T=%ld,min=%.16lf,max=%.16lf,center=%.16lf,steep=%.16lf\n", T, min, max, center, steep);
#endif

    real diff = (max - min);
    // theta_temp: theta_amen_temp or theta_real_temp
    for (size_t t = 0; t < T; t++)
        for (int i = 0; i < NPOSLAND; i++)
            theta_temp[IPOSLANDT(t, i)] = theta_temp_fun(min,diff,steep,center,past[IPOSLANDT(t, i)]);
            //min + diff / (1. + exp(steep * (past[IPOSLANDT(t, i)] - center)));
            
#ifdef DEBUG_MODE
    printf("\n\nVerify climate theta:\n");
    for (int i = 0; i < 10; i++)
        printf("(%d,%lf,%lf) ", i, theta_temp[IPOSLANDT(1, i)], past[IPOSLANDT(1, i)]);
#endif
}
void init_L_R_eq_75_88_part_1(env_t *env,real *amen,real *prod,real *L_H_m2,real *R_H_m2,real *L,real *R)
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
    real denom = 1. + 2. * env__theta;
    real L_amen_exp = (1. + env__theta) / (denom * env->exp_uhatL);
    real R_amen_exp = env__theta * env__theta / denom;
    real L_prod_exp = 1. / (denom * env->exp_uhatL);
    real R_prod_exp = (1. + env__theta) / denom;
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
void init_L_R_eq_75_88_part_2(env_t *env,real *price_energy,real *L_aux,real *R_aux,real *L,real *R)
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
    real denom = 1. + 2. * env__theta;
    real L_price_energy_exp = -env__theta * env__mu * (1. - env->chi) / (denom * env->exp_uhatL);
    real R_price_energy_exp = L_price_energy_exp * (1. + env__theta)  * env->exp_uhatL;
    for (int i = 0; i < NPOSLAND; i++)
    {
        L[i] = L_aux[i] * pow(price_energy[i],L_price_energy_exp); // outside the integral
        R[i] = R_aux[i] * pow(price_energy[i],R_price_energy_exp); // inside the integral
        // printf("%lf %lf\n",FL[i],FR[i]);
    }
}
void init_model(env_t *env,const real *m2,real *L_H_m2,real *R_H_m2,real * uhat_i,real gamma1)
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
    real denom = 1. + 2. * env__theta;
    
    // env->dummy_m: 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    real squ;
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
    real flatL = env__lambda - squ / denom;                                         // naturalL in case of backward_climate
    real flatR = 1. - env__lambda * env__theta + (1. + env__theta) * squ / denom;   // naturalR in case of backward_climate
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
    real aux_exp_left = (flatL - 1. / denom) / env->exp_uhatL;
    real L_H_m2_right_exp = flatL / (env__Omega * env->exp_uhatL);
    real aux_exp_right = -flatR + env__theta / denom;
    real R_H_m2_right_exp = -flatR / env__Omega;
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
    // Backward Climate Preallocation: Precompute auxiliary variables
    env->const_phi = pow((env__gamma1 / env__ksi) / (env__nu * (env__mu + env__gamma1 / env__ksi)), (1. / env__ksi));
    env->const_energy = (1 - env->chi) * env__mu / (env__mu + env__gamma1 / env__ksi);
    real squ_b = (env__alpha - 1 + (env__lambda + env__gamma1 / env__ksi - (1 - env__mu) - env__gamma1 / (env__ksi * env__gamma2)) * env__theta); // term in square brackets of natural_R and natural_L
    real naturalL = env__lambda - squ_b / denom;
    real naturalR = 1 - env__lambda * env__theta + (1 + env__theta) * squ_b / denom;
    real natural = naturalR - env__theta * naturalL;
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
     - from env: l0_model and realgdp0_model.
            // ****** DEVELOP ****** : (CHECK IF IT is l20_model and not l0_model.
            // ****** DEVELOP ****** Consider not storing l0_model and realgdp0_model
    Returns: realgdp0_w
 */
{
    real sum = 0;
    for (int i = 0; i < NPOSLAND; i++)
    {
        sum += env->l0_model[i] * env->realgdp0_model[i] * env->H[i];
    }
    sum = sum / env__lbar;
    env->realgdp0_w = sum;
}
void update_fossil_clean_CO2_realgdp(// input
                                real *zeta_fossil_prev,
                                real *zeta_clean_prev,
                                real *realgdp_w_prev,
                                real *cumCO2_prev,
                                // output
                                real *zeta_fossil,
                                real *zeta_clean,
                                real *realgdp_w,
                                     real *cumCO2){
    
    for (int i = 0; i < NPOSLAND; i++){
        zeta_fossil[i]=zeta_fossil_prev[i];
        zeta_clean[i]=zeta_clean_prev[i];
    }
    *realgdp_w= *realgdp_w_prev;
    *cumCO2_prev = *cumCO2;
    
}
void update_productivity(env_t *env,const real *l_vec, real gamma1, real *prod){
    
    // Compute Average Productivity
    real avgprod=0.;
    for (int i = 0; i < NPOSLAND; i++){
        avgprod+=prod[i];  // env->prod0 or prod
    }
    avgprod=avgprod/((real) NPOSLAND);
    real prod_scaler = env__eta * pow(avgprod,1.-env__gamma2) * pow(env->const_phi,gamma1*env__theta);
    real l_vec_exponent = gamma1*env__theta/env__ksi;
    for (int i = 0; i < NPOSLAND; i++){
        // Set Productivity
        prod[i] =  prod_scaler * pow(prod[i],env__gamma2) * pow(l_vec[i],l_vec_exponent);
    }
    
}
void update_stockCO2_temp_amen_prod_fun(env_t *env,const real S0,const real S1,const real S2,const real S3,const real emi,const real forc_noCO2,const real temp1,const real temp2,real *stockCO2_layers,real *temp_layers,real *temp_global,real *temp_local,real *amen,real *prod)
// Set/Update CO2 stock, forcing and temperature, equations (15), (17), (37)-(41)
/*
 Input: CO2 stock: S0,S1,S2,S3 + emission emi + forc_noCO2,temp1-temp2
 Output: stockCO2_layers[4],temp_layers[2], real temp_global, temp_local[NPOSLAND], amen[NPOSLAND], prod[NPOSLAND]
 */
{
    
    // Set/Update CO2 stock, forcing and temperature, equations (15), (17), (37)-(41)
    real sum=0.;
    int i=0;
    stockCO2_layers[i] =                  S0 + env__a0*emi;sum+=stockCO2_layers[i];i++;
    stockCO2_layers[i] = exp(-1./env__b1)*S1 + env__a1*emi;sum+=stockCO2_layers[i];i++;
    stockCO2_layers[i] = exp(-1./env__b2)*S2 + env__a2*emi;sum+=stockCO2_layers[i];i++;
    stockCO2_layers[i] = exp(-1./env__b3)*S3 + env__a3*emi;sum+=stockCO2_layers[i];
    real forc;
    forc = env__forc_sens*log(sum/env__S_preind)/log(2.) + forc_noCO2;
    temp_layers[0] = exp(-1./env__d1)*temp1 + (env__c1/env__d1)*forc;
    temp_layers[1] = exp(-1./env__d2)*temp2 + (env__c2/env__d2)*forc;
    *temp_global = temp_layers[0]+temp_layers[1];
    
    for (int i = 0; i < NPOSLAND; i++){
        real temp_local_prev_scalar= temp_local[i];    // when t>0 temp_local_prev coincides with temp_local
        temp_local[i]= env->temp0_local[i] + env->scaler_temp[i] * ((*temp_global)-env->temp0_global);
        real Delta_temp= temp_local[i]-temp_local_prev_scalar;
        
        // ********* DEVELOP : NOT CLEAR NOT CLEAR
        // Set damages on amenities and productivities
        real theta_amen_temp = climate_theta_fwd(env->theta_amen_scen[ISCEN(0, 8)], // min
                                                 env->theta_amen_scen[ISCEN(1, 8)], // max
                                                 env->theta_amen_scen[ISCEN(2, 8)], // center
                                                 env->theta_amen_scen[ISCEN(3, 8)], // steep
                                                 temp_local[i]);
        real theta_prod_temp = climate_theta_fwd(env->theta_prod_scen[ISCEN(0, 8)], // min
                                                 env->theta_prod_scen[ISCEN(1, 8)], // max
                                                 env->theta_prod_scen[ISCEN(2, 8)], // center
                                                 env->theta_prod_scen[ISCEN(3, 8)], // steep
                                                 temp_local[i]);
        
        
        amen[i] = (1.+theta_amen_temp*Delta_temp)*amen[i];
        prod[i] = (1.+theta_prod_temp*Delta_temp)*prod[i];
    }
    
}
void model_initial_period(env_t *env)
/*  % Update variables of period 0: [ l0_model,~,~,realgdp0_model ] = model_initial_period(m2_i);
    Input: m2_i
    Returns: l0_model,realgdp0_model
 */
{
    real *FL_H_m2 = (real *)malloc(NPOSLAND * sizeof(real));
    real *FR_H_m2 = (real *)malloc(NPOSLAND * sizeof(real));
    real *FL = (real *)malloc(NPOSLAND * sizeof(real));
    real *FR = (real *)malloc(NPOSLAND * sizeof(real));
    real *uhat_i = (real *)malloc(NPOSLAND * sizeof(real));
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
    loop_uhat(TOLL_MODEL_INITIAL_PERIOD,env->trmult_reduced,FL,env->uhat_f_exp,uhat_i,FR,env->exp_uhatR);
    // Accumulators
    real one_over_omega = 1. / env__Omega;
    real sum_u0m2 = 0.;
    for (int i = 0; i < NPOSLAND; i++)
    {
        real aux_u0m2 = pow(uhat_i[i], one_over_omega) * pow(env->m2_i[i], (-one_over_omega));
        sum_u0m2 += aux_u0m2;
        env->l0_model[i] = 1. / env->H[i] * aux_u0m2;
    }
    real lbar_u0m2 = env__lbar / sum_u0m2;
    real lbar_u0m2_pow = pow(lbar_u0m2, env->flat / env__theta);
    for (int i = 0; i < NPOSLAND; i++)
    {
        env->l0_model[i] = env->l0_model[i] * lbar_u0m2;
        real u0 = uhat_i[i] * lbar_u0m2_pow;
        env->realgdp0_model[i] = (u0 / env->a_norm[i]) * pow(env->l0_model[i], env__lambda);
    }

    // Deallocate memory allocation
    free(FL_H_m2);
    free(FR_H_m2);
    free(FL);
    free(FR);
    free(uhat_i);
}
void migration_costs(env_t *env,const real *amen,const real *prod,const real *pop,const real *price_energy,real *m2_i)
/*
 % Output: m2_i: solution for the migration cost function
 */
{
    // Precompute auxiliary variables to equation (88): BL_aux, BR_aux
    real ML[NPOSLAND];
    real MR[NPOSLAND];
    
    // Precompute auxiliary variables
    real denom = 1. + 2. * env__theta;
    real squ= env__alpha - 1. + (env__lambda + env__gamma1 / env__ksi - (1. - env__mu)) * env__theta;
    real flatL = env__lambda - squ / denom;                                         // naturalL in case of backward_climate
    real flatR = 1. - env__lambda * env__theta + (1. + env__theta) * squ / denom;   // naturalR in case of backward_climate
    real denom2 = 1. + env__theta;
    
    real aux_exp_left = (flatL - 1. / denom) / env->exp_uhatL;
    
    real pr_L = 1./denom2;
    real H_L = -env__Omega-1./denom2;
    real po_L = -flatL*denom/denom2-env__Omega;
    real en_L =  -env__theta * env__mu * (1. - env->chi) /denom2;
    
    real am_R = env__theta*env__theta/denom;
    real pr_R = (1.+env__theta)/denom;
    real H_R = env__theta*(1.-env__theta*env__Omega)/denom;
    real po_R = flatR - env__theta * env__theta * env__Omega/denom;
    real en_R = -env__theta*(1.+env__theta)*env__mu*(1.-env->chi)/denom;
    
    for (int i = 0; i < NPOSLAND; i++)
    {
        ML[i] =           amen[i]*pow(prod[i],pr_L)*pow(env->H[i],H_L)*pow(pop[i],po_L)*pow(price_energy[i],en_L);
        MR[i] = pow(amen[i],am_R)*pow(prod[i],pr_R)*pow(env->H[i],H_R)*pow(pop[i],po_R)*pow(price_energy[i],en_R);
    }
    
    // Update m2_i
    real L_exp = denom/(env__theta*denom2);
    real R_exp = -env__theta*env__theta/denom;
    loop_uhat(TOLL_M2_INNER,env->trmult_reduced,ML,L_exp,m2_i,MR,R_exp);
    
    // Normalize m2 such that minimum equals one
    real min_m2_i=1.;                                       // ************ DEVELOP                 TO BE FIXED
    
    //   ******************               DEVELOP JOONGSAN
    
    /*
            // ADAPT THIS CODE
     if (!rtIsNaN(m2_i[0])) {
         idx = 1;
     }
     else {
         idx = 0;
         k = 2;
         exitg1 = false;
         while ((!exitg1) && (k < 11)) {
             if (!rtIsNaN(m2_i[k - 1])) {
                 idx = k;
                 exitg1 = true;
             }
             else {
                 k++;
             }
         }
     }
     if (idx == 0) {
         squ = m2_i[0];
     }
     else {
         squ = m2_i[idx - 1];
         idx++;
         for (k = idx; k < 11; k++) {
             d = m2_i[k - 1];
             if (squ > d) {
                 squ = d;
             }
         }
     }
     */
    
    for (int i = 0; i < NPOSLAND; i++)
    {
        m2_i[i] = m2_i[i] / min_m2_i;
    }
    
    
    
}
void forward_climate(env_t *env, sym_t *sym_)
/*
 Returns:
 sym_.l NPOSLAND * T_FORWARD
 sym_.prod NPOSLAND * T_FORWARD
 sym_.realgdp NPOSLAND * T_FORWARD
 sym_.amen NPOSLAND * T_FORWARD
 sym_.temp_local NPOSLAND * T_FORWARD
 sym_.price_emi NPOSLAND * T_FORWARD
 sym_.price_clean NPOSLAND * T_FORWARD
 */
{
    // 1. Initialize output variables
    // endogenous CO2 emissions (emiCO2_ff), temperature (temp_global) and population (lbar_time)
    // ****** DEVELOP ******
    // Update adaptation parameters: val_adap == 1. so for now leave it
    real *m2_aux = env->m2_i;
    // 2. Initialize parameters and variables of initital period:
    init_worldgdp(env); // Initializes realgdp0_w
#ifdef DEBUG_MODE
    printf("\n\nrealgdp0_w = %.16lf", env->realgdp0_w);
#endif
    // ******************* INITIALIZATIONS: model_initial_period; backward_climate; forward_climate
    // Precompute auxiliary variables
    real FL_H_m2[NPOSLAND];
    real FR_H_m2[NPOSLAND];
    real uhat_i[NPOSLAND];
    env->dummy_m=2; // env->dummy_m: 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    // Initialize: env->flat, env->exp_uhatL env->exp_uhatR L_H_m2 R_H_m2, uhat_i
    // *** NOTE: flat = natural
    real gamma1 = env__gamma1; // *********** DEVELOP CHECK
    init_model(env,env->m2_i,FL_H_m2,FR_H_m2,uhat_i,gamma1);
    // ********************************************** END INITIALIZATIONS
    // Set Guesses
    // *********** DEVELOP CHECK
    real emi_ff_i = env->emi0_ff;                     // guess for global CO2 emissions
    real realgdp_growth_i = GUESS_realgdp_growth_i;     // guess for global realgdp growth
    
    // Update productivity and amenities
    real amen[NPOSLAND];
    real prod[NPOSLAND];
    real zeta_fossil[NPOSLAND];             // DEVELOP TO BE FIXED
    real zeta_clean[NPOSLAND];              // DEVELOP TO BE FIXED
    real temp_local[NPOSLAND];
    
    // Initialize
    for (int i = 0; i < NPOSLAND; i++){
        prod[i] = env->prod0[i];
        amen[i] = env->a_norm[i];
        zeta_fossil[i]=env->zeta_fossil0[i];
        zeta_clean[i]=env->zeta_clean0[i];
        temp_local[i]=env->temp0_local[i];
    }
    update_productivity(env,env->l0_model,gamma1,prod);
    real realgdp_w = env->realgdp0_w;real realgdp_w_next;
    real cumCO2_ff=env->emi0_ff;
    
    
    // Set/Update CO2 stock, forcing and temperature, equations (15), (17), (37)-(41)
    real stockCO2_layers[4];
    real temp_layers[2];
    real temp_global;
    update_stockCO2_temp_amen_prod_fun(env,env->S0,env->S1,env->S2,env->S3,env->emi0,env->forc_noCO2[0],env->temp1,env->temp2,stockCO2_layers,temp_layers,&temp_global,temp_local,amen,prod);
    
    
    // Initialization period 0
    /*
    real *zeta_fossil_fp = env->zeta_fossil0;
    real *zeta_fossil_fp_next = zeta_fossil;
    real *zeta_clean_fp = env->zeta_clean0;
    real *zeta_clean_fp_next = zeta_clean;
     */
    /*
     update_fossil_clean_CO2_realgdp(// input
                                     env->zeta_fossil0,
                                     env->zeta_clean0,
                                     env->realgdp0_w,
                                     env->emi0_ff,
                                     // output
                                     zeta_fossil,
                                     zeta_clean,
                                     realgdp_w_next,
                                     cumCO2);
     */
    // Update global population
    real lbar_time; // Global Population
    update_globalpop(env,
                     env->l0_model,
                     env->realgdp0_model,   // Check
                     env->realgdp0_w,
                     env->temp0_local,                     // temperature
                     env->coeff_pop_i,
                     &lbar_time);
    lbar_time = round(lbar_time);
    
    // ***********************************************************
    //                    3. Simulate the model backwards
    // ***********************************************************
    // Auxiliary variables
    // Retrieve utility, equation (90)
    real one_over_omega = 1. / env__Omega;
    real one_minus_epsilon=(1.-env__eps);
    real one_over_one_minus_epsilon=1./one_minus_epsilon;
    
    for (size_t t = 0; t < T_FORWARD; t++)
    {
        // Output: prod_fp,amen_fp,zeta_fossil_next,zeta_clean_next,realgdp_w_next,cumCO2_ff
        // Compute extraction cost
        real costCO2_avg_i;
        costC02_fun(env, &cumCO2_ff, &costCO2_avg_i);
        
        // Precompute auxiliary variables to equation (88): BL_aux, BR_aux
        real FL_aux[NPOSLAND];
        real FR_aux[NPOSLAND];
        init_L_R_eq_75_88_part_1(env,amen,prod,FL_H_m2,FR_H_m2,FL_aux,FR_aux);
        
        // ***********************************************************
        //                        FIXED POINT
        // ***********************************************************
        real error_realgdp = FW_tol_realgdp + 1.;
        int iter_realgdp = 0;
        real realgdp_growth_f;
        real emiCO2_total;
        real RHS_zeta_fossil,RHS_zeta_clean;
        real realgdp[NPOSLAND];
        real l_vec[NPOSLAND];
        
        while (error_realgdp >= FW_tol_realgdp)
        {
            RHS_zeta_fossil = pow(realgdp_growth_i,-GUESS_upsilon_fossil_i);
            RHS_zeta_clean = pow(realgdp_growth_i,-GUESS_upsilon_clean_i);
            
            real error_e = FW_tol_e + 1.;
            int iter_e = 0;
            while (error_e >= FW_tol_e)
            {
                // Pre-compute auxiliary variables to equation (88)
                real FL[NPOSLAND];
                real FR[NPOSLAND];
                real price_energy[NPOSLAND];
                real varphi[NPOSLAND];// may not be needed
                
                real denom = 1. + 2. * env__theta;
                real L_price_energy_exp = -env__theta * env__mu * (1. - env->chi) / (denom * env->exp_uhatL);
                real R_price_energy_exp = L_price_energy_exp * (1. + env__theta)  * env->exp_uhatL;
                real fossilshare_to_epsilon = pow(env->fossil_share,env__eps);
                real one_minus_fossilshare_to_epsilon = pow(1.-env->fossil_share,env__eps);
                real aux_mu_gamma_ksi = env__mu+gamma1/env__ksi;
                real L_varphi_exp = env__theta*aux_mu_gamma_ksi/(denom * env->exp_uhatL);
                real R_varphi_exp = L_varphi_exp * (1. + env__theta)  * env->exp_uhatL;
                
                for (int i = 0; i < NPOSLAND; i++)
                {
                    real zeta_fossil_real = zeta_fossil[i]*RHS_zeta_fossil;
                    real zeta_clean_real = zeta_clean[i]*RHS_zeta_clean;
                    
                    // Construct energy price, equations (44) and (46)
                    real price_fossil= costCO2_avg_i/zeta_fossil_real;
                    real price_clean = env__price_clean0_world/zeta_clean_real;
                    
                    // Forward climate specific terms
                    real taxCO2_real = 1.;  // Tax              // ******** DEVELOP *********
                    real subclean_real = 1.;    // Subsidy      // ******** DEVELOP *********
                    real fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon = fossilshare_to_epsilon*pow(price_fossil,one_minus_epsilon)*pow(taxCO2_real,-env__eps);
                    real one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon = one_minus_fossilshare_to_epsilon*pow(subclean_real*price_clean,one_minus_epsilon)*pow(subclean_real,-env__eps);
                    
                    
                    price_energy[i]= pow(fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon*taxCO2_real
                                           +
                                         one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon*subclean_real
                                         ,one_over_one_minus_epsilon);
                    real price_energy_tilde = pow(fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon+one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon,one_over_one_minus_epsilon);
                    varphi[i] = (env__mu*env->chi + gamma1 / env__ksi + env__mu*(1-env->chi)*pow(price_energy_tilde/price_energy[i],one_minus_epsilon))/(aux_mu_gamma_ksi);
                    // Precompute auxiliary variables to equation (75)
                    FL[i] = FL_aux[i]* pow(price_energy[i], L_price_energy_exp)*pow(varphi[i],L_varphi_exp); // outside the integral
                    FR[i] = FR_aux[i]* pow(price_energy[i], R_price_energy_exp)*pow(varphi[i],R_varphi_exp); // inside the integral
                    
                }
                // Iterate uhat, equation (75)
                loop_uhat(BW_tol,env->trmult_reduced,FL,env->uhat_f_exp,uhat_i,FR, env->exp_uhatR);
                
                // Preallocate loop that does not depend on the next while but for ltilde
                real sum_u0m2 = 0.;
                for (int i = 0; i < NPOSLAND; i++){
                    // Solve for population, equation (3), and scale it to add up to lbar_time
                    real aux_u0m2 = pow(uhat_i[i]/m2_aux[i],one_over_omega); // ****** DEVELOP ****** m2_aux difference with backward_climate
                    sum_u0m2 += aux_u0m2;
                    l_vec[i] = 1./env->H[i]*aux_u0m2;
                }
                //
                real scaler_u0m2_over_ltilde = lbar_time /sum_u0m2;
                real u_i_scaler = pow(scaler_u0m2_over_ltilde,env->flat/env__theta);        // this third part could be preallocated // ****** DEVELOP ******
                
                // Compute world real GDP
                realgdp_w_next =0.;
                real sum_HL=0.;
                for (int i = 0; i < NPOSLAND; i++){
                    // Solve for population, equation (3), and scale it to add up to ltilde
                    l_vec[i] = l_vec[i] * scaler_u0m2_over_ltilde;
                    // Utility, equation (76): // ****** DEVELOP ****** different w/ bwd_climate
                    real u_i = uhat_i[i]*u_i_scaler;
                    // Calculate real income and real GDP per capita, equation (4)
                    real realincome_i = u_i /amen[i] * pow(l_vec[i],env__lambda);
                    realgdp[i] = (1 + aux_mu_gamma_ksi*(varphi[i]-1))* realincome_i;
                    real Hl = env->H[i]*l_vec[i];
                    realgdp_w_next += realgdp[i]*Hl;
                    sum_HL += Hl;
                }
                realgdp_w_next=realgdp_w_next/sum_HL;
                
                // Update productivity, equation (6)
                update_productivity(env,l_vec,gamma1,prod);
                real l_vec_exponent = gamma1*env__theta/env__ksi;
                
                
                real emi_ff_f =0.;
                real emi_ff_f_abat =0.;
                for (int i = 0; i < NPOSLAND; i++){
                    
                    // Set Productivity: // ****** DEVELOP ****** varphi different w/ bwd_climate
                    prod[i] =  prod[i] * pow(1./varphi[i],l_vec_exponent);
                    
                    real price_energy_real= price_energy[i];
                    //real price_clean_real = env__price_clean0_world/zeta_clean[i];
                    real price_fossil_real= costCO2_avg_i/zeta_fossil[i];
                    real const_energy_l_over_price_energy =env->const_energy*l_vec[i]/(varphi[i]*price_energy_real);
                    real taxCO2_real = 1.;  // Tax              // ******** DEVELOP *********
                    real subclean_real = 1.;    // Subsidy      // ******** DEVELOP *********
                    real abat_real = 1.;
                    
                    // Calculate clean energy use, equation (53) NOT USED YET
                    //real clean =const_energy_l_over_price_energy*pow((1.-env->fossil_share)*price_energy_real/(subclean_real*price_clean_real),env__eps);
                    
                    // Calculate CO2 emissions, equation (52) // DIFFERENT FROM BWD for taxes
                    real emiCO2_ff=const_energy_l_over_price_energy*pow(env->fossil_share*price_energy_real/(taxCO2_real*price_fossil_real),env__eps);
                    emi_ff_f +=emiCO2_ff*env->H[i];
                    
                    // Update CO2 emissions by abatement
                    real emiCO2_ff_abat = abat_real*emiCO2_ff;
                    emi_ff_f_abat +=emiCO2_ff_abat*env->H[i];
                }
                
                // Compare global CO2 emissions
                error_e=fabs(emi_ff_f-emi_ff_i);
                emi_ff_i = UPDATE_FW_EE*emi_ff_f + (1.-UPDATE_FW_EE)*emi_ff_i;
                
                costCO2_avg_i = 0.;
                real step = emi_ff_i/99.; //(100-1)
                for (int i = 0; i < 100; i++){
                    real costCO2_fct;
                    real CO2_real = cumCO2_ff + step * i; // DIFFERENT FROM BWD_INDUCTION: goes opposite direction with steps
                    
                    costC02_fun(env,&CO2_real,&costCO2_fct);
                    costCO2_avg_i += costCO2_fct;
                }
                costCO2_avg_i = costCO2_avg_i/100.;
                
                // Used for updating amen and prod
                emiCO2_total = emi_ff_f_abat + env->emi_no_ff[t];         // CHECK IF IT COINCIDES WITH YEAR ***** DEVELOP
                
            }
            
            // Compare growth rate realgdp
            realgdp_growth_f = realgdp_w_next/realgdp_w;
            error_realgdp = fabs(realgdp_growth_f-realgdp_growth_i);
            realgdp_growth_i = UPDATE_FW_R*realgdp_growth_f + (1.-UPDATE_FW_R)*realgdp_growth_i;
    
            iter_realgdp++;
        }
        
        // Set growth rate of previous period
        realgdp_growth_i = realgdp_growth_f;
        
        for (int i = 0; i < NPOSLAND; i++)
        {
            // Self updating
            zeta_fossil[i] = zeta_fossil[i]*RHS_zeta_fossil;
            zeta_clean[i]  = zeta_clean[i] *RHS_zeta_clean;
        }
        
        
        // Set/Update CO2 stock, forcing and temperature, equations (15), (17), (37)-(41)
        update_stockCO2_temp_amen_prod_fun(env,stockCO2_layers[0],stockCO2_layers[1],stockCO2_layers[2],stockCO2_layers[3],emiCO2_total,env->forc_noCO2[0],temp_layers[t+1],temp_layers[1],stockCO2_layers,temp_layers,&temp_global,temp_local,amen,prod);
        
        // Update global population
        real lbar_time; // Global Population
        update_globalpop(env,
                         l_vec,
                         realgdp,
                         realgdp_w,
                         temp_local,                     // temperature
                         env->coeff_pop_i,
                         &lbar_time);
        lbar_time = round(lbar_time);

        
        // Update energy productivity, equation (9)
        realgdp_w = realgdp_w_next;
        
        
        for (int i = 0; i < NPOSLAND; i++){
            sym_->amen[IPOSLANDT(0,i)]=amen[i];
            sym_->prod[IPOSLANDT(0,i)]=prod[i];
            sym_->temp_local[IPOSLANDT(0,i)]=temp_local[i];
        }
        
    } // t
    
}
void update_price_energy(env_t *env,sym_t *sym_,real *price_energy)
/*
    Output: price_energy
 */
{
    const real fossilshare_to_epsilon = pow(env->fossil_share,env__eps);
    const real one_minus_fossilshare_to_epsilon = pow(1.-env->fossil_share,env__eps);
    const real one_minus_epsilon=(1.-env__eps);
    const real one_over_one_minus_epsilon=1./one_minus_epsilon;
    for (int i = 0; i < NPOSLAND; i++)
    {
        int is = IPOSLANDT(T_M2_MIGRATION_COSTS, i);
        real fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon =
        fossilshare_to_epsilon*pow(sym_->price_emi[is],one_minus_epsilon);
        real one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon =
        one_minus_fossilshare_to_epsilon*pow(sym_->price_clean[is],one_minus_epsilon);
        
        price_energy[i]= pow(fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon
                               +
                             one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon
                             ,one_over_one_minus_epsilon);
        
    }
    
}
void update_upsilon(env_t *env,sym_t *sym_)
/*
 // Update upsilon
 // 1. Update variables of period 20: l20,realgdp20,temp20 guesses
 // 2/ Update Migration Costs
 */
{
    // Update variables of period 20: l20,realgdp20,temp20 guesses
    forward_climate(env,sym_);
    update_period20(env,sym_);
    update_b0T_bw_coeff_pop(env,env->coeff_pop_i);        // Update b0T and bw when you update period0 and period20
    
    // Update Migration Costs
    real price_energy[NPOSLAND];
    update_price_energy(env,sym_,price_energy);             // Compute price_energy
    // Update Migration Costs:
    int is = IPOSLANDT(T_M2_MIGRATION_COSTS, 0);
    migration_costs(env,&sym_->amen[is],&sym_->prod[is],env->pop5_dens,price_energy,env->m2_i);
}
void update_upsilon_clean(env_t *env,sym_t *sym_,real *error)
/*
    Input: price_emi,price_clean (from forward)
    Output: env->upsilon_fossil_i
 */
{
    //                                                                JOONGSAN DEVELOP: CONSTRUCT emi_ff_model = fliplr(sum(emiCO2_b.*repmat(H,1,T_back)))';
    real clean_model[T_BACK-15];
    real T_real = (real) T_BACK-15;
    // Compute Error_m2: NOTICE: it is a mean squared error
    *error =0.;
    for (int i = 0; i < T_BACK; i++){
        real diff = clean_model[i] - env__tCO2_toe*env->clean_energy_data[i];
        *error +=diff*diff;
    }
    *error =sqrt(*error/T_real);
    real slope_model = (                        clean_model[0]-                         clean_model[T_BACK-16])/T_real;
    real slope_tend = (env__tCO2_toe*env->clean_energy_data[0]-env__tCO2_toe*env->clean_energy_data[T_BACK-16])/T_real;
    env->upsilon_clean_i = (UPDATE_UPSILON_CLEAN + (1.-UPDATE_UPSILON_CLEAN)*slope_tend/slope_model)*env->upsilon_clean_i;
    // Update upsilon
    // 1. Update variables of period 20: l20,realgdp20,temp20 guesses
    // 2/ Update Migration Costs: env->m2_i
    update_upsilon(env,sym_);
}
void update_upsilon_fossil(env_t *env,sym_t *sym_,real *error)
/*
    Input: price_emi,price_clean (from forward)
    Output: env->upsilon_fossil_i
 */
{
    //                                                                JOONGSAN DEVELOP: CONSTRUCT emi_ff_model = fliplr(sum(emiCO2_b.*repmat(H,1,T_back)))';
    real emi_ff_model[T_BACK];
    real T_real = (real) T_BACK;
    // Compute Error_m2: NOTICE: it is a mean squared error
    *error =0.;
    for (int i = 0; i < T_BACK; i++){
        real diff = emi_ff_model[i] - env->emi_ff_data_tend[i];
        *error +=diff*diff;
    }
    *error =sqrt(*error/T_real);
    real slope_model = (        emi_ff_model[0]-         emi_ff_model[T_BACK-1])/T_real;
    real slope_tend = (env->emi_ff_data_tend[0]-env->emi_ff_data_tend[T_BACK-1])/T_real;
    
    env->upsilon_fossil_i = (UPDATE_UPSILON_FOSSIL + (1.-UPDATE_UPSILON_FOSSIL)*slope_tend/slope_model)*env->upsilon_fossil_i;
    
    // Update upsilon
    // 1. Update variables of period 20: l20,realgdp20,temp20 guesses
    // 2/ Update Migration Costs: env->m2_i
    update_upsilon(env,sym_);
}
void update_migration_costs(env_t *env,sym_t *sym_,real *error)
/*
    Input: price_emi,price_clean (from forward)
    Output: m2_i
 */
{
    /*
    const real fossilshare_to_epsilon = pow(env->fossil_share,env__eps);
    const real one_minus_fossilshare_to_epsilon = pow(1.-env->fossil_share,env__eps);
    const real one_minus_epsilon=(1.-env__eps);
    const real one_over_one_minus_epsilon=1./one_minus_epsilon;
    for (int i = 0; i < NPOSLAND; i++)
    {
        int is = IPOSLANDT(T_M2_MIGRATION_COSTS, i);
        real fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon =
        fossilshare_to_epsilon*pow(sym_->price_emi[is],one_minus_epsilon);
        real one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon =
        one_minus_fossilshare_to_epsilon*pow(sym_->price_clean[is],one_minus_epsilon);
        
        price_energy[i]= pow(fossilshare_to_epsilon_price_fossil_to_one_minus_epsilon
                               +
                             one_minus_fossilshare_to_epsilon_price_clean_to_one_minus_epsilon
                             ,one_over_one_minus_epsilon);
        
    }
    */
    // Compute price_energy
    real price_energy[NPOSLAND];
    update_price_energy(env,sym_,price_energy);
    // Update Migration Costs: env->m2_i
    real m2_f[NPOSLAND];
    int is = IPOSLANDT(T_M2_MIGRATION_COSTS, 0);
    migration_costs(env,&sym_->amen[is],&sym_->prod[is],env->pop5_dens,price_energy,m2_f);
    
    // Compute Error_m2
    error_sqrt_sum_squared_residual(m2_f, env->m2_i,error);
    
    // Update m2_i
    env->m2_i[0] = UPDATE_M2*m2_f[0] + (1.-UPDATE_M2)*env->m2_i[0];
    real min_m2_i=env->m2_i[0];
    for (int i = 1; i < NPOSLAND; i++)
    {
        env->m2_i[i] = UPDATE_M2*m2_f[i] + (1.-UPDATE_M2)*env->m2_i[i];
        if(env->m2_i[i]<min_m2_i)
            min_m2_i=env->m2_i[i];
    }
    
    // Update variables of period 0: l0_model,realgdp0_model
    model_initial_period(env);
    update_b0T_bw_coeff_pop(env,env->coeff_pop_i);        // Update b0T and bw when you update period0 and period20
    // Update variables of period 20: l20,realgdp20,temp20 guesses
    forward_climate(env,sym_);
    update_period20(env,sym_);
    update_b0T_bw_coeff_pop(env,env->coeff_pop_i);        // Update b0T and bw when you update period0 and period20
    
}
void backward_climate(env_t *env, sym_t *sym_)
/* Returns:
 sym_.l_b: cell-level population
 sym_.realgdp_b: real GDP (NPOSLAND * T_BACK)
 sym_.emiCO2_b: CO2 emissions from fossil fuel combustion (NPOSLAND * T_BACK)
 sym_.clean_b: clean energy use (NPOSLAND * T_BACK)
 */
{
    // 1. Initialize output variables
    // 2. Initialize parameters and variables of initital period
    init_worldgdp(env); // Initializes realgdp0_w
#ifdef DEBUG_MODE
    printf("\n\nrealgdp0_w = %.16lf", env->realgdp0_w);
#endif
    // Set damages on amenities and productivities
    // temp_past_out = temp_past; (Not used)
    real *theta_amen_temp = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));
    real *theta_prod_temp = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));

#ifdef DEBUG_MODE
    printf("\n----------------------------theta_amen\n");                   // NPOSLAND * T_BACK
    printf("%.16g %.16g %.16g %.16g\n", env->theta_amen_scen[ISCEN(0, 8)], // min
           env->theta_amen_scen[ISCEN(1, 8)],                               // max
           env->theta_amen_scen[ISCEN(2, 8)],                               // center
           env->theta_amen_scen[ISCEN(3, 8)]                               // steep
    );
#endif
    climate_theta(T_BACK,
                  env->theta_amen_scen[ISCEN(0, 8)], // min
                  env->theta_amen_scen[ISCEN(1, 8)], // max
                  env->theta_amen_scen[ISCEN(2, 8)], // center
                  env->theta_amen_scen[ISCEN(3, 8)], // steep
                  env->temp_past,
                  theta_amen_temp); // output
    climate_theta(T_BACK,
                  env->theta_prod_scen[ISCEN(0, 8)], // min
                  env->theta_prod_scen[ISCEN(1, 8)], // max
                  env->theta_prod_scen[ISCEN(2, 8)], // center
                  env->theta_prod_scen[ISCEN(3, 8)], // steep
                  env->temp_past,
                  theta_prod_temp); // output
#ifdef DEBUG_MODE
    debug_init_backward_climate(env, theta_amen_temp);
#endif
    // Precompute auxiliary variables
    // ******************* INITIALIZATIONS: model_initial_period; backward_climate; forward_climate
    real BL_H_m2[NPOSLAND];
    real BR_H_m2[NPOSLAND];
    real uhat_i[NPOSLAND];
    env->dummy_m=1; // env->dummy_m: 0 if {model_initial_period}; 1 if backward_climate; 2 if forward_climate
    // Initialize: env->flat, env->exp_uhatL env->exp_uhatR L_H_m2 R_H_m2, uhat_i
    // *** NOTE: flat = natural
    init_model(env,env->m2_i,BL_H_m2,BR_H_m2,uhat_i,env__gamma1);
    // ********************************************** END INITIALIZATIONS
    
    // Set Guesses
    real ltilde = round(env__lbar/(1.+env->natal0)); // guess for global population -- n = int(floor(x + 0.5f)): https://en.wikibooks.org/wiki/Optimizing_C%2B%2B/Code_optimization/Faster_operations
    real lbar1 = env__lbar;
    real emi_ff_i = env->emi0_ff;                     // guess for global CO2 emissions
    real realgdp_growth_i = GUESS_realgdp_growth_i;     // guess for global realgdp growth

    // ***********************************************************
    //                    3. Simulate the model backwards
    // ***********************************************************
    // Auxiliary variables
    // Retrieve utility, equation (90)
    real one_over_omega = 1. / env__Omega;
    real one_minus_epsilon=(1.-env__eps);
    real one_over_one_minus_epsilon=1./one_minus_epsilon;
    real one_over_gamma2= 1./env__gamma2;
    real gamma2_minus_1=env__gamma2-1;
    real minus_gamma1_gamma2=-env__gamma1*one_over_gamma2;
    real const_phi_to_minus_gamma12= pow(env->const_phi,minus_gamma1_gamma2);
    real gamma2_minus_1_over_gamm2theta=gamma2_minus_1*one_over_gamma2/env__theta;
    
    // Compute previous period's energy productivity, global real GDP and cummulative CO2 emissions
    real prod[NPOSLAND];
    real amen[NPOSLAND];
    real zeta_fossil[NPOSLAND];
    real zeta_clean[NPOSLAND];
    real realgdp_w,cumCO2;
    
    // Auxiliary pointers to previous period
    real *prod_fp, *amen_fp, *zeta_fossil_next, *zeta_clean_next;
    real prod_next[NPOSLAND]; // prod of current period feeding next period
    real realgdp_w_next;
    real cumCO2_next;               // we can get rid of it ****** DEVELOP ******
    // Initialization period 0
    prod_fp = env->prod0;
    amen_fp = env->a_norm;
    zeta_fossil_next = env->zeta_fossil0;
    zeta_clean_next = env->zeta_clean0;
    // Real
    realgdp_w_next = env->realgdp0_w;
    realgdp_w=cumCO2=0.;    // Initialized later
    cumCO2_next = 0.;
    
    for (size_t t = 0; t < T_BACK; t++)
    {
        // Initialization period 0 and successive periods with previous values
        if (t != 0)
        {
            // Pointers
            prod_fp = prod;
            amen_fp = amen;
            zeta_fossil_next = zeta_fossil;
            zeta_clean_next = zeta_clean;
            // Real
            realgdp_w_next = realgdp_w;
            cumCO2_next = cumCO2;
        }
        for (int i = 0; i < NPOSLAND; i++)
        {
            int is = IPOSLANDT(t, i);
            prod_next[i]=prod_fp[i]/(1.+theta_prod_temp[is]*env->Delta_temp[is]);
            amen[i]     =amen_fp[i]/(1.+theta_amen_temp[is]*env->Delta_temp[is]);
        }
        // Output: prod_fp,amen_fp,zeta_fossil_next,zeta_clean_next,realgdp_w_next,cumCO2_next
        // Compute extraction cost
        real costCO2_avg_i;
        costC02_fun(env, &cumCO2_next, &costCO2_avg_i);

        // Precompute auxiliary variables to equation (88): BL_aux, BR_aux
        real BL_aux[NPOSLAND];
        real BR_aux[NPOSLAND];
        init_L_R_eq_75_88_part_1(env,amen,prod_next,BL_H_m2,BR_H_m2,BL_aux,BR_aux);
        /*
        for (int i = 0; i < NPOSLAND; i++)
        {
            real amen_real = amen[i];
            real prod_real = prod_next[i];
            real BL_H_m2 = env->BL_H_m2_left[i] * pow(env->m2_i[i], env->BL_H_m2_right_exp);                // outside the integral
            real BR_H_m2 = env->BR_H_m2_left[i] * pow(env->m2_i[i], env->BR_H_m2_right_exp);                // inside the integral
            BL_aux[i] = pow(amen_real, env->BL_a_norm_exp) * pow(prod_real, (env->BL_prod0_exp)) * BL_H_m2; // outside the integral
            BR_aux[i] = pow(amen_real, env->BR_a_norm_exp) * pow(prod_real, (env->BR_prod0_exp)) * BR_H_m2; // inside the integral
        }
        */
        // ***********************************************************
        //                        FIXED POINT
        // ***********************************************************
        real error_realgdp = BW_tol_realgdp + 1.;
        int iter_realgdp = 0;
        while (error_realgdp >= BW_tol_realgdp)
        {
            real RHS_zeta_fossil = pow(realgdp_growth_i,-GUESS_upsilon_fossil_i);
            real RHS_zeta_clean = pow(realgdp_growth_i,-GUESS_upsilon_clean_i);
            // Update energy productivity, equation (9)
            for (int i = 0; i < NPOSLAND; i++)
            {
                // Self updating
                zeta_fossil[i] = zeta_fossil_next[i]*RHS_zeta_fossil;
                zeta_clean[i]  = zeta_clean_next[i] *RHS_zeta_clean;
            }
            
            real error_e = BW_tol_e + 1.;
            int iter_e = 0;
            while (error_e >= BW_tol_e)
            {
                // Pre-compute auxiliary variables to equation (88)
                real BL[NPOSLAND];
                real BR[NPOSLAND];
                real price_energy[NPOSLAND];
                
                
                real denom = 1. + 2. * env__theta;
                real L_price_energy_exp = -env__theta * env__mu * (1. - env->chi) / (denom * env->exp_uhatL);
                real R_price_energy_exp = L_price_energy_exp * (1. + env__theta)  * env->exp_uhatL;
                real fossilshare_to_epsilon = pow(env->fossil_share,env__eps);
                real one_minus_fossilshare_to_epsilon = pow(1.-env->fossil_share,env__eps);
                
                for (int i = 0; i < NPOSLAND; i++)
                {
                    // Construct energy price, equations (44) and (46)
                    real price_fossil= costCO2_avg_i/zeta_fossil[i];
                    real price_clean = env__price_clean0_world/zeta_clean[i];
                    price_energy[i]= pow(fossilshare_to_epsilon*pow(price_fossil,one_minus_epsilon)
                                           +
                                         one_minus_fossilshare_to_epsilon*pow(price_clean,one_minus_epsilon)
                                         ,one_over_one_minus_epsilon);
                    BL[i] = BL_aux[i]* pow(price_energy[i], L_price_energy_exp); // outside the integral
                    BR[i] = BR_aux[i]* pow(price_energy[i], R_price_energy_exp); // inside the integral
                    // printf("%lf %lf %lf %lf\n",FL[i],FR[i],uhat_i[i],integral[i]);
                }
                // Iterate uhat, equation (88)
                loop_uhat(BW_tol,env->trmult_reduced,BL,env->uhat_f_exp,uhat_i,BR, env->exp_uhatR);
                
                // Preallocate loop that does not depend on the next while but for ltilde
                real l_vec[NPOSLAND];
                real sum_u0m2 = 0.;
                for (int i = 0; i < NPOSLAND; i++){
                    // Solve for population, equation (3), and scale it to add up to ltilde
                    real aux_u0m2 = pow(uhat_i[i]/env->m2_i[i],one_over_omega);
                    sum_u0m2 += aux_u0m2;
                    l_vec[i] = 1./env->H[i]*aux_u0m2;
                }

                real error_l = BW_tol_l + 1.;
                int iter_l = 0;
                while (error_l >= BW_tol_l)
                {
                    real scaler_u0m2_over_ltilde = ltilde /sum_u0m2;
                    real inverse_scaler_u0m2_over_ltilde = 1./scaler_u0m2_over_ltilde;
                    
                    real avgprod = 0.;
                    for (int i = 0; i < NPOSLAND; i++){
                        // Solve for population, equation (3), and scale it to add up to ltilde
                        l_vec[i] = l_vec[i] * scaler_u0m2_over_ltilde;
                        // Calculate innovation, equations (49) and (51)
                        real phi_real = env->const_phi*pow(l_vec[i],1./env__ksi);
                        // Back out productivity (Part 1)
                        prod[i] = pow(phi_real,env__theta*minus_gamma1_gamma2) * pow(prod_next[i],one_over_gamma2);
                        avgprod +=prod[i];
                    }
                    avgprod = avgprod/((real) NPOSLAND);
                    real avgprod_scaler = pow(avgprod,gamma2_minus_1);
                    real avgprod_scaled = avgprod_scaler*avgprod;
                    /* NOT NEEDED SINCE PROD IS NOT RETURNED BY THE FUNCTION
                    real avgprod_scaled = 0.;
                    for (int i = 0; i < NPOSLAND; i++){
                        prod[i] = prod[i]*avgprod_aux;
                        avgprod_scaled +=prod[i];
                    }
                    */
                    real u_i_scaler = const_phi_to_minus_gamma12 *
                                      pow(avgprod_scaled,gamma2_minus_1_over_gamm2theta)*
                                      pow(scaler_u0m2_over_ltilde,env->flat/env__theta);        // this third part could be preallocated // ****** DEVELOP ******
                    
                    real *realgdp = (real *)malloc(NPOSLAND * sizeof(real));
                    realgdp_w =0.;
                    for (int i = 0; i < NPOSLAND; i++){
                        // Back out productivity (Part 2) -> feed prod_fp
                        prod[i]=prod[i]*avgprod_scaler;
                        // Retrieve utility, equation (90)
                        real u_i = uhat_i[i]*u_i_scaler; // ---> ltilde enter here
                        // Calculate real GDP per capita, equation (4)
                        real real_gdp_i= u_i /amen[i] * pow(l_vec[i],env__lambda);
                        realgdp_w += real_gdp_i*env->H[i]*l_vec[i]/ltilde;
                        // Calculate real GDP per capita, equation (4)
                        realgdp[i]= real_gdp_i;
                    }
                    // Update global population
                    real ltilde1;
                    update_globalpop(env,l_vec,realgdp,realgdp_w,&env->temp_past[IPOSLANDT(t, 0)],env->coeff_pop_i,&ltilde1);
                    ltilde1 = ltilde + ltilde1; // ltilde1 is sum netbirths*H
                    error_l=fabs(lbar1-ltilde1);// Compare global populations
                    ltilde = round((UPDATE_BW_L*lbar1/ltilde1+(1.-UPDATE_BW_L))*ltilde);// Update ltilde
                    
                    // Store Results
                    for (int i = 0; i < NPOSLAND; i++){
                        // Return:
                        uint32_t is = IPOSLANDT(t, i);
                        sym_->l_b[is] = l_vec[i];       // cell-level population (NPOSLAND * T_BACK)
                        // Reset l_vec[i] for next iteration (get rid of old ltilde to later update with new one)
                        l_vec[i]=l_vec[i]*inverse_scaler_u0m2_over_ltilde;
                        sym_->realgdp_b[is]=realgdp[i];
                    }
                    free(realgdp);
                    iter_l++;
                    
                } // error_l
                // Calculate energy use, equations (52) and (53)
                real emi_ff_f =0.;
                for (int i = 0; i < NPOSLAND; i++){
                    uint32_t is = IPOSLANDT(t, i);
                    real l_real = sym_->l_b[is];
                    real price_energy_real= price_energy[i];
                    real price_clean_real = env__price_clean0_world/zeta_clean[i];
                    real price_fossil_real= costCO2_avg_i/zeta_fossil[i];
                    real const_energy_l_over_price_energy =env->const_energy*(l_real/price_energy_real);
                    real emiCO2_ff=const_energy_l_over_price_energy*pow(env->fossil_share*price_energy_real/price_fossil_real,env__eps);
                    real clean =const_energy_l_over_price_energy*pow((1.-env->fossil_share)*price_energy_real/price_clean_real,env__eps);
                    emi_ff_f +=emiCO2_ff*env->H[i];
                    
                    // Return:
                    sym_->emiCO2_b[is] =emiCO2_ff;  // CO2 emissions from fossil fuel combustion (NPOSLAND * T_BACK)
                    sym_->clean_b[is] =clean;       // clean energy use (NPOSLAND * T_BACK)
                }

                // Compare global CO2 emissions
                error_e=fabs(emi_ff_f-emi_ff_i);
                emi_ff_i = UPDATE_BW_EE*emi_ff_f + (1.-UPDATE_BW_EE)*emi_ff_i;
                cumCO2 = cumCO2_next - emi_ff_f;

                costCO2_avg_i = 0.;
                real step = emi_ff_i/99.; //(100-1)
                for (int i = 0; i < 100; i++){
                    real costCO2_fct;
                    real CO2_real = cumCO2_next - step * i;
                    costC02_fun(env,&CO2_real,&costCO2_fct);
                    costCO2_avg_i += costCO2_fct;
                }
                costCO2_avg_i = costCO2_avg_i/100.;

                iter_e++;
            }

            // Compare growth rate realgdp
            real realgdp_growth_f = realgdp_w_next/realgdp_w;
            error_realgdp = fabs(realgdp_growth_f-realgdp_growth_i);
            realgdp_growth_i = UPDATE_BW_R*realgdp_growth_f + (1.-UPDATE_BW_R)*realgdp_growth_i;
    
            iter_realgdp++;
        }
        
        // Update lbar1
        lbar1 = ltilde;

    } // t<T

    free(theta_amen_temp);
    free(theta_prod_temp);
}
void initialize_weight_pop_matrix(env_t *env, real *weight_pop_matrix)
{

    // real sum_pop[T_BACK_AUX];
    int offset = 0;
    for (int t = 0; t < T_BACK_AUX; t++)
    {
        real sum_pop = 0.; //[t]=0.;
        offset = offset + t;
        for (int i = 0; i < LENGTH_ISO; i++)
        {
            int index = (i)*T_BACK_AUX + offset;
            sum_pop = sum_pop + env->pop_data[index];
        }
        for (int i = 0; i < LENGTH_ISO; i++)
        {
            int index = (i)*T_BACK_AUX + offset;
            weight_pop_matrix[index] = env->pop_data[index] / sum_pop; // sum_pop[t];
        }
    }
    /*
    #ifdef DEBUG_MODE
        printf("weight_pop_matrix (which in reality is a vector):\n");
        for(int i=0;i<NDATA;i++)
        {
            printf("%f ",weight_pop_matrix[i]);
        }
        printf("\n");
    #endif
    */
    // Arrange data
    /*
    length_ISO = length(year_data)/(2000-1950+1);
    pop_data_resh = reshape(pop_data,[2000-1950+1 length_ISO]);
    pop_tot_data = repmat(sum(pop_data_resh,2),length_ISO,1);
    weight_pop_data = pop_data./pop_tot_data;
    weight_pop_matrix = diag(weight_pop_data).*diag(kron(linspace(1,1,(2000-1950+1))',ones(length_ISO,1)));
    */
}
void initialize_period_20(env_t *env)
{
    real growth_l = pow(1.01, 20);
    real growth_gdp = pow(1.02, 20);
    for (int i = 0; i < NPOSLAND; i++)
    {
        env->l20_model[i] = growth_l * env->l0_model[i];
        env->realgdp20_model[i] = growth_gdp * env->realgdp0_model[i];
        env->temp20_local[i] = env->temp0_local[i] + TEMPLINSCALER * env->scaler_temp[i];
    }
}
void estim_model(env_t *env)
/* Function that estimates the parameters of the natality rate function,
 * the migration cost function and the elasticities of energy productivity
 * growth to global real income growth.
 */
{
    real *weight_pop_matrix = (real *)calloc(NDATA, sizeof(real)); // Population Shares, NDATAx1
    sym_t sym_;
    // Simulation Backward variables
    sym_.l_b = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));
    sym_.realgdp_b = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));
    sym_.emiCO2_b = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));
    sym_.clean_b = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));
    // Simulation Forward variables
    sym_.l = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));
    sym_.prod = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));
    sym_.realgdp = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));
    sym_.amen = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));
    sym_.temp_local = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));
    sym_.price_emi = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));
    sym_.price_clean = (real *)calloc(NPOSLAND * T_FORWARD, sizeof(real));

    // Update variables of period 0: l0_model,realgdp0_model
    model_initial_period(env);
    printf("env->realgdp0_model: %lf, %lf, %lf", env->realgdp0_model[0], env->realgdp0_model[NPOSLAND - 2], env->realgdp0_model[NPOSLAND - 1]);
    initialize_period_20(env);
    update_b0T_bw_coeff_pop(env,env->coeff_pop_i);
    initialize_weight_pop_matrix(env, weight_pop_matrix);
        
    real error_clean = 1. + TOLL_CLEAN;
    while (error_clean >= TOLL_CLEAN){
        
        real error_fossil = 1. + TOLL_FOSSIL;
        while(error_fossil > TOLL_FOSSIL){
            
            real error_m2 = 1. + TOLL_M2;
            while(error_m2 > TOLL_M2){
                
                real error_l = 1. + TOLL_L;
                while(error_l > TOLL_L){
                    
                    // 2. Run model backwards, given m_2 and coeff_pop
                    backward_climate(env, &sym_);
                    
                    // 3. Perform NLLS on natality function
                    NLLS(env, &sym_);
                    
                    // 4. Run model forward to update l20, given natality parameters
                    forward_climate(env, &sym_);
                    // Compute error_l
                    error_sqrt_sum_squared_residual(env->l20_model,sym_.l,&error_l);
                    // Update variables of period 20: l20,realgdp20,temp20 guesses
                    update_period20(env,&sym_);
                    update_b0T_bw_coeff_pop(env,env->coeff_pop_i);        // Update b0T and bw when you update period0 and period20
                    
                    /*
                    error_l =0.;
                    for (int i = 0; i < NPOSLAND; i++){
                        int is = IPOSLANDT(19, i);
                        real diff = env->l20_model[i] - sym_.l[is];
                        error_l+=diff*diff;
                        
                        // Update Period 20
                        env->l20_model[i] = sym_.l[is];
                        env->realgdp20_model[i] = sym_.realgdp[is];
                        env->temp20_local[i] = sym_.temp_local[is];
                        
                    }
                    error_l =sqrt(error_l);
                    */
                }
                // 5. Update Migration Costs: env->m2_i
                update_migration_costs(env,&sym_,&error_m2);
                
            }
            // 6. Update upsilon fossil
            update_upsilon_fossil(env,&sym_,&error_fossil);
            
        }

        // 7. Update upsilon clean
        update_upsilon_clean(env,&sym_,&error_clean);
        
    }   // uspilon clean loop
    
    
    // Deallocate Memory
    free(weight_pop_matrix);
    free(sym_.l_b);
    free(sym_.realgdp_b);
    free(sym_.emiCO2_b);
    free(sym_.clean_b);
    free(sym_.l);
    free(sym_.prod);
    free(sym_.realgdp);
    free(sym_.amen);
    free(sym_.temp_local);
    free(sym_.price_emi);
    free(sym_.price_clean);
}
// *************************************************************
//                        END: KERNEL (estim_model)
// *************************************************************
void init_all(env_t *env) //, input_t *in, vars_t *vars)
{
    // Prellocate
    env->H = (real *)calloc(NPOSLAND, sizeof(real));
    env->prod0 = (real *)calloc(NPOSLAND, sizeof(real)); // productivities in 2000
    env->pop5_dens = (real *)calloc(NPOSLAND, sizeof(real));
    env->u0 = (real *)calloc(NPOSLAND, sizeof(real));                         // utility in 2000
    env->a_norm = (real *)calloc(NPOSLAND, sizeof(real));                     // amenities in 2000
    env->trmult_reduced = (real *)calloc(NPOSLAND * NPOSLAND, sizeof(real)); // Bilateral trade cost on Earth cells at t=0 only
    env->C_vect = (small_idx_t *)calloc(NPOSLAND, sizeof(small_idx_t));         // national demarcations with H0>0
    env->emi_no_ff = (real *)calloc(N2600, sizeof(real));                     // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC                    // utility in 2000
    env->price_energy0 = (real *)calloc(NPOSLAND, sizeof(real));
    env->zeta_clean0 = (real *)calloc(NPOSLAND, sizeof(real));
    env->zeta_fossil0 = (real *)calloc(NPOSLAND, sizeof(real));
    env->forc_noCO2 = (real *)calloc(N2600_2, sizeof(real)); // Read non CO2 radiative forcing, 601x1
    env->temp0_local = (real *)calloc(NPOSLAND, sizeof(real));
    env->temp_past = (real *)calloc(NPOSLAND * T_BACK_AUX, sizeof(real));
    env->Delta_temp = (real *)calloc(NPOSLAND * T_BACK, sizeof(real));
    env->scaler_temp = (real *)calloc(NPOSLAND, sizeof(real));
    env->theta_amen_scen = (real *)calloc(NSCEN, sizeof(real)); // 4x9
    env->theta_prod_scen = (real *)calloc(NSCEN, sizeof(real)); // 4x9
    env->natal_data = (real *)calloc(NDATA, sizeof(real));
    env->pop_data = (real *)calloc(NDATA, sizeof(real));
    env->m2_i = (real *)calloc(NPOSLAND, sizeof(real)); // Guesses

    // Auxiliary Variables
    env->l0_model = (real *)calloc(NPOSLAND, sizeof(real));
    env->realgdp0_model = (real *)calloc(NPOSLAND, sizeof(real));
    env->l20_model = (real *)calloc(NPOSLAND, sizeof(real));
    env->realgdp20_model = (real *)calloc(NPOSLAND, sizeof(real));
    env->temp20_local = (real *)calloc(NPOSLAND, sizeof(real));
    
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
    real *C_vect_real = (real *)malloc(NPOSLAND * sizeof(real));
    strcpy(variablename, "C_vect");
    read_binary(C_vect_real, variablename, NPOSLAND); // ************* VARIABLE
    for (int i = 0; i < NPOSLAND; i++)
        env->C_vect[i] = (small_idx_t)C_vect_real[i];
    free(C_vect_real);
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
    // Guess for the elasticity of fossil fuel productivity growth to global real GDP growth
    env->upsilon_fossil_i = GUESS_upsilon_fossil_i;
    // Guess for the elasticity of clean energy productivity growth to global real GDP growth
    env->upsilon_clean_i = GUESS_upsilon_clean_i;
    // ---------------------------------------------------------------------------
    memset(variablename, '\0', sizeof(variablename));
    strcpy(variablename, "m2_i");
    read_binary(env->m2_i, variablename, NPOSLAND); // SET VARIABLE

    // Initialize Auxiliary to model_init_period, backward_climate, forward_climate
    //init_model_TBD(env);

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
    free(env->C_vect);
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
    free(env->realgdp0_model);
    free(env->l20_model);
    free(env->realgdp20_model);
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
    printf("\n---------------------------- TRMULT REDUCED\n");
    printf("%.16g %.16g %.16g %.16g\n", env.trmult_reduced[IPOSLAND(0, 12354)],
           env.trmult_reduced[IPOSLAND(NPOSLAND - 1, NPOSLAND - 1)],
           env.trmult_reduced[IPOSLAND(1, NPOSLAND - 6)],
           env.trmult_reduced[IPOSLAND(NPOSLAND - 12000, 1200)]);
    printf("\n----------------------------theta_amen\n");                  // NPOSLAND * T_BACK
    printf("%.16g %.16g %.16g %.16g\n", env.theta_amen_scen[ISCEN(0, 8)], // min
           env.theta_amen_scen[ISCEN(1, 8)],                              // max
           env.theta_amen_scen[ISCEN(2, 8)],                              // center
           env.theta_amen_scen[ISCEN(3, 8)]                                  // steep
    );
    printf("\n----------------------------temp_past\n"); // NPOSLAND * T_BACK_AUX
    printf("%.16g %.16g %.16g %.16g\n", env.temp_past[IPOSLANDT(0, 0)],
           env.temp_past[IPOSLANDT(T_BACK_AUX - 1, NPOSLAND - 1)],
           env.temp_past[IPOSLANDT(3, 14000)],
           env.temp_past[IPOSLANDT(47, 15650)]);
    printf("\n----------------------------Delta_temp\n"); // NPOSLAND * T_BACK
    printf("%.16g %.16g %.16g %.16g\n", env.Delta_temp[IPOSLANDT(0, 0)],
           env.Delta_temp[IPOSLANDT(T_BACK - 1, NPOSLAND - 1)],
           env.Delta_temp[IPOSLANDT(3, 11000)],
           env.Delta_temp[IPOSLANDT(47, 17000)]);

    /*
    printf("\n----------------------------theta_amen\n"); // NPOSLAND * T_BACK
    for (size_t i = 0; i < 32; i++)
        printf("%.16lf ",env.theta_amen_scen[i]);
    printf("\n----------------------------temp_past\n"); // NPOSLAND * T_BACK_AUX
    printf("%.16g %.16g %.16g %.16g\n", env.temp_past[IPOSLANDT(0, 0)],
           env.temp_past[IPOSLANDT(NPOSLAND - 1, T_BACK_AUX - 1)],
           env.temp_past[IPOSLANDT(14000, 3)],
           env.temp_past[IPOSLANDT(15650, 47)]);
    */

    // Kernel
    estim_model(&env);
    // Deallocate
    free_all(&env);
}
// 21. Preallocation model_initial_period
/*
void init_model_TBD(env_t *env)
{
    // ****************************** model_initial_period.m ******************************
    // Compute parameters
    real denom = 1. + 2. * env__theta;
    real squ = (env__alpha - 1. + (env__lambda + env__gamma1 / env__ksi - (1. - env__mu)) * env__theta); // term in square brackets of flat_R and flat_L
    real flatL = env__lambda - squ / denom;
    real flatR = 1. - env__lambda * env__theta + (1. + env__theta) * squ / denom;
    real flat = flatR - env__theta * flatL;
    real exp_uhatL = flatL / env__Omega + (1. + env__theta) / denom;
    real exp_uhatR = flatR / env__Omega - env__theta * env__theta / denom;

    // Precompute auxiliary variables to equation (75)
    for (int i = 0; i < NPOSLAND; i++)
    {
        env->FL_H_m2_left[i] = pow(env->H[i], (flatL - 1 / denom) / exp_uhatL);
        env->FR_H_m2_left[i] = pow(env->H[i], (-flatR + env__theta / denom));
    }
    env->FL_H_m2_right_exp = flatL / (env__Omega * exp_uhatL);
    env->FR_H_m2_right_exp = -flatR / env__Omega;
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
    // Backward Climate Preallocation: Precompute auxiliary variables
    env->const_phi = pow((env__gamma1 / env__ksi) / (env__nu * (env__mu + env__gamma1 / env__ksi)), (1. / env__ksi));
    env->const_energy = (1 - env->chi) * env__mu / (env__mu + env__gamma1 / env__ksi);
    real squ_b = (env__alpha - 1 + (env__lambda + env__gamma1 / env__ksi - (1 - env__mu) - env__gamma1 / (env__ksi * env__gamma2)) * env__theta); // term in square brackets of natural_R and natural_L
    real naturalL = env__lambda - squ_b / denom;
    real naturalR = 1 - env__lambda * env__theta + (1 + env__theta) * squ_b / denom;
    real natural = naturalR - env__theta * naturalL;
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
}*/
