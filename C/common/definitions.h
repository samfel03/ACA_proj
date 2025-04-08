#pragma once
#include <stdio.h>
#include <stdlib.h> // must be prior to sds_lib.h
#include <string.h>
#include <assert.h>
// #include <cstdint>

/** Development options */
//#include "dev_options.h"
#define DETAILED_PERF_METRICS	1 // set to print detailed timing values
/** Hardware includes */
/*
#include <ap_int.h>
#include <ap_fixed.h>
*/
#define N_MODEL 1
#define IND_DAM 9	// Level of the damage function, 9 is the benchmark

/** Typedefs */
typedef double real;
typedef unsigned short small_idx_t;
typedef unsigned int idx_t;
typedef unsigned char shock_t;

const real b0y_max = 0.045;
const real b1y_min = 0.01;
const real b1y_max = 0.03;
const real b2y_min = -0.00090;
const real b2y_max = -0.00050;
const real b2T_max = 0.015;
const real bsy_min = 0;
const real bsy_max = 8;
const real bsT_min = 14;
const real bsT_max = 22;

// 1. ****************************** main.m ******************************
// Initialize model with Benchmark Estimation: initialize(ind_RCP,maxCO2,eps)
const real env__ind_RCP = 8.5;	// RCP scenario for the CO2 emissions from non-fossil fuel combustion and the forcing from non-CO2sources; can take the value of 8.5, 6.0, 4.5 or 2.6;    8.5 is the baseline.
const real env__maxCO2 = 19500; // Total stock of CO2 available in the ground; 19500 is the baseline.
const real env__eps = 1.6;		// Elasticity of substitution between fossil fuels and clean energy;
// ----------------------------------------------
//	INITILIZE THE GUESSES
// Estimates natality function, migration costs and energy productivities
//  Guess on natality function, migration costs, upsilon_fossil and upsilon_clean
const real GUESS_coeff_pop_i[8] = {-0.69, 0, -5, -0.51, -0.25, -5, 2.88, -0.67};// [ b0y, b1y, b1y', b2y, bsy, b1T, b2T, bsT ]
const real GUESS_upsilon_fossil_i = 1.15;
const real GUESS__upsilon_clean_i = 1.15;
const real GUESS_realgdp_growth_i=1.017; // guess for global realgdp growth (backward_climate and forward_climate)
// ----------------------------------------------
// update_vect = [1 0.95 0.95]: Set speed of update for migration costs, upsilon_fossil and upsilon_clean
const real UPDATE_M2 = 1;		
const real UPDATE_UPSILON_FOSSIL = 0.95;
const real UPDATE_UPSILON_CLEAN = 0.95;
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
// 2. ****************************** backward_CLIMATE.m ******************************
// ----------------------------------------------
const real BW_UPDATEL = 1.;	// speed of update when iterating over l	
const real BW_UPDATEE = 1.;
const real BW_UPDATER = 1.;
#define BW_tol ((real)(1e-2))   // tolerance for error when iterating over uhat
#define BW_tol_l ((real)(1e+1)) // tolerance for error when iterating over l
#define BW_tol_e ((real)(1e-3))
#define BW_tol_realgdp ((real)(1e-2))

// 2. ****************************** initialize.m ******************************
// 1. Initialize the Parameters
const real env__lbar = 5.9174e+09; // total population
const real env__lambda = 0.32;	   // congestion externalities
const real env__gamma1 = 0.319;	   // elasticity of tomorrow's productivity relative to today's innovation
const real env__gamma2 = 0.99246;  // elasticity of tomorrow's productivity relative to today's productivity
const real env__eta = 1;		   // parameter driving scale of technology diffusion
const real env__mu = 0.8;		   // labor share in production
const real env__nu = 0.15;		   // intercept parameter in innovation cost function
const real env__ksi = 125;		   // elasticity of innovation costs relative to innovation
const real env__sigma = 4;		   // elasticity of substitution
const real env__psi_util = 0.045;  // wellbeing parameter
const real env__beta = 0.965;	   // discount factor for present discounted values
const real env__alpha = 0.06;	   // agglomeration externalities
const real env__theta = 6.5;	   // variance productivity shocks
const real env__Omega = 0.5;	   // variance taste shocks
// NOT USED const real env__max_cumCO2 = maxCO2;							// total stock of CO2 in the ground
//  USE env__eps const real env__epsilon = eps;								// elasticity of substitution between fossil fuels and clean energy
const real env__tCO2_toe = 2.8466;									   // conversion factor: GtCO2 per Gtoe
const real env__price_fossil0_world = 72.99 * pow(10.,9.);				   // price of fossil fuels in usd/GtCO2
const real env__price_clean0_world = 1.15 * 76.34 * pow(10.,9.) / env__tCO2_toe; // price of clean energy in usd/GtCO2

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
const real env__temp_preind = 8.1; // temperature in pre-industrial era
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
const real natal_param[10] = {b0y_max, b1y_min, b1y_max, b2y_min, b2y_max, b2T_max, bsy_min, bsy_max, bsT_min, bsT_max};
//// 22. Define colors and variable names for plots
/* DO NOT TRANSLATE
//color_olive = [128 128 0]/255;
//color_darkgreen = [0 100 0]/255;
//color_darkcyan = [0 139 139]/255;
//color_yellowgreen = [154 205 50]/255;
//color_greenyellow = [173 255 47]/255;
//name_type_vect = {'Warm', 'WarmAm', 'WarmPr'};
//name_long_type_vect = {'', 'onlyAm_', 'onlyPr_'};
//name_maps_type_vect = {'', 'effect only on amenities', 'effect only on productivity'};
//name_dam_vect = {'low95' 'high95' 'low90' 'high90' 'low80' 'high80' 'low60' 'high60' 'med'};
//name_dam_long_vect = {'Low 95//' 'High 95//' 'Low 90//' 'High 90//' 'Low 80//' 'High 80//' 'Low 60//' 'High 60//' 'Baseline'};
//table_prop = {' ' 'BGP Real GDP' 'PDV Real GDP' 'BGP Welfare' 'PDV Welfare'};
*/
// 3. ****************************** fundamentals.m ******************************
// Set energy parameters
// DOUBLE DECLARATION
/*
const real env__tCO2_toe = 2.8466;			   // conversion factor: GtCO2 per Gtoe
const real env__fossil0 = 25.284967 / env__tCO2_toe; // 25.284967 GtCO2 expressed in Gtoe
const real env__clean0 = 1.3179;				   // 1.3179 Gtoe
*/
/** Simulation settings */
#define T_BACK = 50	       // Number of periods to run backward the model
#define T_FORWARD = 50	   // Number of periods to run forward the model

/** Set numerical parameters for the estimation of the natality function */
const real size_deriv = 1e-5;
const real scal_nlls = 1e-5;
const real lev_nlls = 1e-3;
const real count_max = 50;


typedef struct env_t
{
	// full: 1618+16+10+100+4+100+4+14
	// Initialized in: init_environment()
	// DECLARED AS CONSTANTS
	// Initialized in: init_land_amen_prod_pop_wages()
	real H0;		 //
	real H;			 //
	real n;			 // number of cells with positive land
	real amen_util0; // ratio of amenities to utility in 2000
	real prod0;		 // productivities in 2000
	real pop0;		 // population in 2000
	real pop0_dens;	 //
	real pop1_dens;	 //
	real pop5_dens;	 //
	// real pop5;								// population in 2005
	// real w0;	   							    // wage in 2000
	//  Initialized in: init_uti_HDI
	real HDI0;	 // Human Development Index in 2000
	real u0;	 // utility in 2000
	real a_norm; // amenities in 2000
	// Initialized in: init_trmult
	real trmult_reduced; // Bilateral trade cost on Earth cells at t=0 only
	// Initialized in: init_countries_indices
	real C_vect;		// national demarcations with H0>0
	real length_C_vect; // length of C_vect
	// Initialized in: init_CO2_clean_energy
	real emi0_ff;	  // Global CO2 emissions from fossil fuels for 2000 (interpreted *****)
	real emi_ff;	  // Global CO2 emissions from fossil fuels from 2000 to 2600, by IPCC
	real emi0_no_ff;  // Global CO2 emissions from non fossil fuels for 2000 (interpreted *****)
	real emi_no_ff;	  // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC
	real emi0;		  // total CO2 emissions for 2000
	real emi0_cell;	  // CO2 emissions at cell level for 2000
	real clean0_cell; // CO2 emissions and clean energy at the country level for 2000
	// Initialized in: init_energy_tech
	real fossil_share; // Construct share of fossil fuels in energy composite
	real chi;		   // Construct share of energy in production, equations (7) and (44)
	// GDP0 used later
	// Initialized in: init_extraction_cost_fun
	real cost_CO2_data;		 // Cost extraction data
	real cost_emi_param;	 // Redefine extraction cost function
	real price_clean0_world; // Define normalization relative to Princeton wage: usdP/GtCO2
	real conv_usd;			 // Dollar conversion
	// costCO2_fct NOT USED
	// Initialized in: init_energy_productivity
	real fossil0_cell; // Construct energy use at the cell level, equation (7)
	real price_clean0; // Construct energy price at the cell level by source, equations (52), (53)
	real price_fossil0;
	real price_energy0;
	real zeta_clean0; // Construct initial energy productivities
	real zeta_fossil0;
	// Initialized in: init_carbon_circulation
	real S0; // Initialize CO2 stock layers, equations (38) and (39)
	real S1;
	real S2;
	real S3;
	// Initialized in: init_forcing_sensitivity
	real forc_noCO2; // Read non CO2 radiative forcing
	// Initialized in: init_temperature_global
	real forc_data; // Read forcing from 2000 to 1825
	real temp1;		// Initialize temperature layers, equation (41)
	real temp2;
	real temp0_global;
	// Initialized in: init_temperature_local
	real temp0_local_long;
	real temp0_local; // Local temperatures
	real Delta_temp1;
	real temp_past;
	real Delta_temp;
	// Initialized in: init_temperature_scaler
	real scaler_temp;
	// Initialized in: init_
	real theta_amen_scen;
	real theta_prod_scen;
	// Undeclared function: theta_prod_temp = @(temp) theta_prod_min + ...(theta_prod_max - theta_prod_min)./ ...(1 + exp(theta_prod_steep * (temp - theta_prod_center)));
	// Initialized in: init_population_historical
	real country_data; // Read net birth historical data
	real year_data;
	real natal_data;
	real pop_data;
	real natal0;
	real natal20;
	// Initialized in: init_population_prediction
	real pop_low95;
	real pop_low80;
	real pop_med;
	real pop_high80;
	real pop_high95;
	real pop_low95_hist;
	real pop_low80_hist;
	real pop_med_hist;
	real pop_high80_hist;
	real pop_high95_hist;
	// Initialized in: init_climate_prediction
	real emiCO2_RCP; // Construct CO2 stock, forcing and temperature, using data on CO2 emissions and non-CO2 forcing, equations (15) and (37)-(41)
	real forc_RCP;
	real stockCO2_RCP;
	real temp_global_RCP;
	// Initialized in: init_CO2_historical
	real clean_energy_data;
	real emi_ff_data; // Historical fossil fuel CO2 emission and its trend
	real emi_ff_data_tend;
	// Initialized in: init_map
	real map;
	// Guess on natality function, migration costs, upsilon_fossil and upsilon_clean
	real coeff_pop_i[8];	// Guess for coefficients on the natality rate function.
	real upsilon_fossil_i;  // Guess for the elasticity of fossil fuel productivity growth to global real GDP growth
	real upsilon_clean_i;	// Guess for the elasticity of clean energy productivity growth to global real GDP growth
	real m2_i;				// Load guess for migration costs (estim_model.m)
	// Initialized in: model_initial_period (used in forward)
	real l0_model;
	real realgdp0_model;
	real flatL;
	real flatR;
	real flat;
	real exp_uhatL;
	real exp_uhatR;
	// Auxiliary
	real aux_denom;
	real const_phi;
	real const_energy;	// notice this may differ in forward and backward looking --> check
	real ones_N;
	real naturalL;
	real naturalR;
	real natural;
	real BL_H_m2_left;
	real BL_H_m2_left_exp;
	real BR_H_m2_right;
	real BR_H_m2_right_exp;

} env_t;

/*
real lbar;										// total population
real lambda;											// congestion externalities
real gamma1;										// elasticity of tomorrow's productivity relative to today's innovation
real gamma2;										// elasticity of tomorrow's productivity relative to today's productivity
real eta;												// parameter driving scale of technology diffusion
real mu;												// labor share in production
real nu;												// intercept parameter in innovation cost function
real ksi;												// elasticity of innovation costs relative to innovation
real sigma;												// elasticity of substitution
real psi_util;										// wellbeing parameter
real beta;											// discount factor for present discounted values
real alpha;											// agglomeration externalities
real theta;											// variance productivity shocks
real Omega;											// variance taste shocks
//NOTUSED: real max_cumCO2;									// total stock of CO2 in the ground
real epsilon;											// elasticity of substitution between fossil fuels and clean energy
real price_fossil0_world;					// price of fossil fuels in usd/GtCO2
real price_clean0_world 					// price of clean energy in usd/GtCO2
*/

/*
real km[NKM_GRID];							// grid of mean of capital distribution
	real k[NKGRID];								// grid of capital
	real epsilon2[NSTATES_ID];					// employed idiosyncratic shock?
	real trate[NSTATES_AG];						// labor-income tax rate
	real ag[NSTATES_AG];						// aggregate productivity shock
	real ag2[NSTATES_AG];						// What is this for?
	real epsilon[NSTATES_ID];					// unemployed idiosyncratic shock?
	real P[SIZE_P];								// matrix of transiiton probabilities
	real wealth[NSTATES];						// intermediate result for capital tomm
	real ur[NSTATES_AG];						// unemployment rate for aggregate states
	real er[NSTATES_AG];						// employment rate for bad aggregate states
	real er_inv[NSTATES_AG];					//
	real irate_factor[NSTATES_AG];				//
	real wage_factor[NSTATES_AG];				//
	real cons2_factor[NSTATES_AG * NSTATES_ID]; //
	real log_env_km[NKM_GRID];					//
*/

