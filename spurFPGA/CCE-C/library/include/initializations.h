#include <iostream>
#include <stdlib.h>
#include <cstring> // memset,strcpy,strcat
#include <math.h>  // definitions.h
#include <cstdint>
extern "C" {
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\rt_nonfinite.h"
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\rtwtypes.h"
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\svd.h"
}
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\projectTypes.h"  // #typedef double real;

#define DEBUG_MODE 1
//#define DEBUG_MODE_DEEP 1
//#define DEBUG_MODE_ERROR_UHAT 1
//#define DEBUG_MODE_CLIMATE_THETA 1
//using namespace std;
//typedef double real;
typedef unsigned short small_idx_t;
/*
//////////////////////////////WSL PATHS
#define TRMULTPATH "/mnt/c/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/trmult_reduced.bin"
#define INPUTPATH "/mnt/c/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/"
#define PRINTPATH "/mnt/c/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/output/"
#ifdef DEBUG_MODE
    #define DEBUGPATH "/mnt/c/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/debug/"
#endif
///////////////////////////////////////
//*/

//////////////////////////////////WINDOWS PATHS
#define TRMULTPATH "C:/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/trmult_reduced.bin"
const size_t size_of_trmult_reduced = sizeof(real);
const real TRMULT_REDUCED_THRESHOLD = 1e-14;
#define BLOCK_SIZE 8 // 8*17048
#define BLOCK_SIZE_READ 136384 // 8*17048


//*
#define INPUTPATH "C:/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/"
#define PRINTPATH "C:/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/output/"
#ifdef DEBUG_MODE
    #define DEBUGPATH "C:/Users/seank/OneDrive - UCB-O365/Research/SPUR/Code/CCE-C/CCE-C/C/input/debug/"
#endif
///////////////////////////////////////////// */

#define N_MODEL 1
#define IND_DAM 9        // Level of the damage function, 9 is the benchmark
#define NPOSLAND 17048    // Number of cells with positive land          17048
#define N2600 600        // Years period: 2000-2600
#define N2600_2 601        // Years period: 2000-2600 (forc_noCO2)
#define NDATA 8568        // country_data, year_data, natal_data, pop_data
#define NCOSTEMIPARAM 7 // size of cost_emi_param
#define NSCEN 36        // size of theta_amen_scen and theta_prod_scen
#define NCLEANENERGY 35 // clean_energy_data
#define T_BACK_AUX 51    // Used in temp_past           ORIGINAL: 51
#define T_M2_MIGRATION_COSTS 4 // Year 5 in Matlab for Computing price_energy: [m2_f] = migration_costs(m2_i,amen(:,5),prod(:,5),pop5_dens,price_energy(:,5),tol_m2_inner);
// estim_model
#define TEMPLINSCALER 0.7 // Scaler impact of temperature in 20 periods (constructed)
#define LENGTH_ISO 168      // NDATA/(2000-1950+1)=168 ---> also length_C_vect
#define LENGTH_COEFF_POP 8 // length of coeff_pop_i

/** Simulation settings */
#define T_BACK 50                             // Number of periods to run backward the model            MINIMUM: 16         ORIGINAL: 50
#define T_FORWARD 20                         // Number of periods to run forward the model                                   ORIGINAL: 20
#define T_FORWARD_MINUS1 19                  // Number of periods to run forward the model minus 1                           ORIGINAL: 19
#define IPOSLAND(i, j) ((i)*NPOSLAND + (j))     // location i-location j cost: col_idx*NROWS+ row_idx
#define ISCEN(i, j) ((i)*9 + (j))             // amen_scen, prod_scen (4x9)
#define IPOSLANDT(t, i) ((t)*NPOSLAND + (i)) // time t-location i: col_idx*NROWS+ row_idx
#define ITBACKAUX(i,t) ((i) * T_BACK_AUX + (t))
#define ELEMENT(row,column,row_cnt) (column)*(row_cnt) + (row)
#define REV_ELEMENT(row,column,row_cnt,column_cnt) ((column_cnt)-(column)-1)*(row_cnt) + (row) // REV_ELEMENT(i, t, NPOSLAND, T_BACK_AUX)
#define REV_ELEMENT_NEW(row, column, row_cnt, column_cnt) (i * column_cnt + (row_cnt - t - 1))
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
const real env__lambda = 0.32;       // congestion elasticity of amenities externalities: amen = mean(amen) L^(-lambda) (first congestion force)
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
const real env__Omega = 0.5;       // variance taste shocks (second congestion force)
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
// Set energy parameters: REPEATED DECLARATION: env__tCO2_toe, env__fossil0, env__clean0
/** Simulation settings: Set numerical parameters for the estimation of the natality function */
const real size_deriv = 1e-5;
const real scal_nlls = 1e-5;
const real lev_nlls = 1e-3;
const int count_max = 50;
// *************************************************************
//                        END: definition.h
// *************************************************************
// Environmental Struct
typedef struct{
    int *rowStart;     // Index of the first nonzero value of each row
    int *colIndex;     // Column Index of non-zero value
    real *value;               // Value
} trmult_t;
typedef struct env_t
{
    real *H;                              // NPOSLAND
    real *prod0;                          // productivities in 2000
    real *pop5_dens;                      //
    real *u0;                              // utility in 2000
    real *a_norm;                          // amenities in 2000
    real *trmult_reduced;                  // Bilateral trade cost on Earth cells at t=0 only
    trmult_t trmult_sparse_;               // Bilateral trade cost on Earth cells at t=0 only
    real *weight_pop_matrix;              // Weighting matrix
    small_idx_t *C_vect;                  // national demarcations with H0>0
    int ELEMENTS;
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
