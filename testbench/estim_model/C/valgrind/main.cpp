#include <iostream>
#include <stdlib.h>
#include <cstring> // memset,strcpy,strcat
#include <math.h>  // definitions.h
#define DEBUG_MODE 1
using namespace std;
//#define real double
typedef double real;
typedef unsigned short small_idx_t;
#define INPUTPATH "/scratch/summit/alpe9373/CCE-C/input/"
#define PRINTPATH "/scratch/summit/alpe9373/CCE-C/output/"
#define N_MODEL 1
#define IND_DAM 9		// Level of the damage function, 9 is the benchmark
#define NPOSLAND 17048	// Number of cells with positive land
#define N2600 600		// Years period: 2000-2600
#define N2600_2 601		// Years period: 2000-2600 (forc_noCO2)
#define NDATA 8568		// country_data, year_data, natal_data, pop_data
#define NCOSTEMIPARAM 7 // size of cost_emi_param
#define NSCEN 36		// size of theta_amen_scen and theta_prod_scen
#define NCLEANENERGY 35 // clean_energy_data
#define T_BACK_AUX 51	// Used in temp_past
// estim_model
#define TEMPLINSCALER 0.7	// Scaler impact of temperature in 20 periods (constructed)
#define LENGTH_ISO 168		// NDATA/(2000-1950+1)=168


/** Simulation settings */
#define T_BACK 50							 // Number of periods to run backward the model
#define T_FORWARD 20						 // Number of periods to run forward the model
#define IPOSLAND(i, j) ((i)*NPOSLAND + (j))	 // location i-location j cost: col_idx*NROWS+ row_idx
#define IPOSLANDT(i, t) ((t)*NPOSLAND + (i)) // time t-location i: col_idx*NROWS+ row_idx
#define ISCEN(i, j) ((i)*9 + (j))			 // amen_scen, prod_scen (4x9)

// *************************************************************
//						BEGIN: definition.s
// *************************************************************
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
const real GUESS_coeff_pop_i[8] = {-0.69, 0, -5, -0.51, -0.25, -5, 2.88, -0.67}; // [ b0y, b1y, b1y', b2y, bsy, b1T, b2T, bsT ]
const real GUESS_upsilon_fossil_i = 1.15;
const real GUESS__upsilon_clean_i = 1.15;
const real GUESS_realgdp_growth_i = 1.017; // guess for global realgdp growth (backward_climate and forward_climate)
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
const real BW_UPDATEL = 1.; // speed of update when iterating over l
const real BW_UPDATEE = 1.;
const real BW_UPDATER = 1.;
#define BW_tol ((real)(1e-2))	// tolerance for error when iterating over uhat
#define BW_tol_l ((real)(1e+1)) // tolerance for error when iterating over l
#define BW_tol_e ((real)(1e-3))
#define BW_tol_realgdp ((real)(1e-2))

// 2. ****************************** initialize.m ******************************
// 1. Initialize the Parameters
const real env__lbar = 5.9174e+09; // total population
const real env__lambda = 0.32;	   // congestion externalities
const real env__gamma1 = 0.319;	   // elasticity of tomorrow's productivity relative to today's innovation
const real env__gamma2 = 0.99246;  // elasticity of tomorrow's productivity relative to today's productivity
const real env__eta = 1.;		   // parameter driving scale of technology diffusion
const real env__mu = 0.8;		   // labor share in production
const real env__nu = 0.15;		   // intercept parameter in innovation cost function
const real env__ksi = 125;		   // elasticity of innovation costs relative to innovation
const real env__sigma = 4.;		   // elasticity of substitution
const real env__psi_util = 0.045;  // wellbeing parameter
const real env__beta = 0.965;	   // discount factor for present discounted values
const real env__alpha = 0.06;	   // agglomeration externalities
const real env__theta = 6.5;	   // variance productivity shocks
const real env__Omega = 0.5;	   // variance taste shocks
// NOT USED const real env__max_cumCO2 = maxCO2;							// total stock of CO2 in the ground
//  USE env__eps const real env__epsilon = eps;								// elasticity of substitution between fossil fuels and clean energy
const real env__tCO2_toe = 2.8466;												  // conversion factor: GtCO2 per Gtoe
const real env__price_fossil0_world = 72.99 * pow(10., 9.);						  // price of fossil fuels in usd/GtCO2
const real env__price_clean0_world = 1.15 * 76.34 * pow(10., 9.) / env__tCO2_toe; // price of clean energy in usd/GtCO2 --> fundamentals.m is in usd/Gtoe

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
const real natal_param[10] = {b0y_max, b1y_min, b1y_max, b2y_min, b2y_max, b2T_max, bsy_min, bsy_max, bsT_min, bsT_max};
//// 22. Define colors and variable names for plots
// 3. ****************************** fundamentals.m ******************************
// Set energy parameters: DOUBLE DECLARATION: env__tCO2_toe, env__fossil0, env__clean0
/** Simulation settings: Set numerical parameters for the estimation of the natality function */
const real size_deriv = 1e-5;
const real scal_nlls = 1e-5;
const real lev_nlls = 1e-3;
const int count_max = 50;
// *************************************************************
//						END: definition.h
// *************************************************************
// Environmental Struct
typedef struct env_t
{
	real *H;							  // NPOSLAND
	real *prod0;						  // productivities in 2000
	real *pop5_dens;					  //
	real *u0;							  // utility in 2000
	real *a_norm;						  // amenities in 2000
	real *trmult_reduced;				  // Bilateral trade cost on Earth cells at t=0 only
	small_idx_t *C_vect;				  // national demarcations with H0>0
	small_idx_t length_C_vect;			  // length of C_vect
	real emi0_ff;						  // Global CO2 emissions from fossil fuels for 2000 (interpreted *****) - scalar
	real *emi_no_ff;					  // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC, N2600x1 (600x1)
	real emi0;							  // total CO2 emissions for 2000, scalar
	real fossil_share;					  // Construct share of fossil fuels in energy composite, scalar
	real chi;							  // Construct share of energy in production, equations (7) and (44), scalar
	real cost_CO2_data;					  // Cost extraction data, 202x2
	real cost_emi_param[NCOSTEMIPARAM];	  // Redefine extraction cost function 1x7: [cost_emi_param_f maxCO2 3];
	real price_clean0_world;			  // Define normalization relative to Princeton wage: usdP/GtCO2
	real *price_energy0;				  //, (17048x1)
	real *zeta_clean0;					  // Construct initial energy productivities, (17048x1)
	real *zeta_fossil0;					  //, (17048x1)
	real S0;							  // Initialize CO2 stock layers, equations (38) and (39), scalar
	real S1;							  // , scalar
	real S2;							  // , scalar
	real S3;							  // , scalar
	real *forc_noCO2;					  // Read non CO2 radiative forcing, 601x1
	real temp1;							  // Initialize temperature layers, equation (41), scalar
	real temp2;							  // , scalar
	real temp0_global;					  // , scalar
	real *temp0_local;					  // Local temperatures, 17048x1
	real *temp_past;					  // , 17048x51 (NPOSLAND,T_BACK_AUX)
	real *Delta_temp;					  // , 17048x50 (NPOSLAND,T_BACK)
	real *scaler_temp;					  // , 17048x1
	real *theta_amen_scen;				  // 4x9
	real *theta_prod_scen;				  // 4x9
	real *natal_data;					  // data for years < 2001, 8568x1
	real *pop_data;						  // data for years < 2001, 8568x1
	real natal0;						  // Natality rates of 2000, scalar
	real natal20;						  // Natality rates of 2020, scalar
	real clean_energy_data[NCLEANENERGY]; // 35x1
	real emi_ff_data[T_BACK];			  // Historical fossil fuel CO2 emission and its trend, 50x1, TBACKx1
	real emi_ff_data_tend[T_BACK];		  // , 50x1, TBACKx1
	real coeff_pop_i[8];				  // Guess for coefficients on the natality rate function.
	real upsilon_fossil_i;				  // Guess for the elasticity of fossil fuel productivity growth to global real GDP growth
	real upsilon_clean_i;				  // Guess for the elasticity of clean energy productivity growth to global real GDP growth
	real *m2_i;							  // Load guess for migration costs (estim_model.m)

	// Auxiliary Variables
	real *l0_model;		  // NPOSLANDx1, 17048x1
	real *realgdp0_model; // NPOSLANDx1, 17048x1
	// -------------- model_initial_period
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
	real uhat_f_exp;
	real flatL;
	real flatR;
	real flat;
	real exp_uhatL;
	real exp_uhatR;
	real aux_denom;
	// ------------- end: model_initial_period
	real *l20_model;			// NPOSLANDx1, 17048x1   ---> natal_fct (consider printing)
	real *realgdp20_model;		// NPOSLANDx1, 17048x1	 ---> natal_fct (consider printing)
	real *temp20_local;			// NPOSLANDx1, 17048x1	 ---> natal_fct (consider printing)
	
	real const_phi;
	real const_energy; // notice this may differ in forward and backward looking --> check
	real ones_N;
	real naturalL;
	real naturalR;
	real natural;
	real BL_H_m2_left;
	real BL_H_m2_left_exp;
	real BR_H_m2_right;
	real BR_H_m2_right_exp;

} env_t;
// *************************************************************
//					backward/forward_climate
// *************************************************************
typedef struct sym_t{
	// Backward
	real *l_b;
	real *realgdp_b;
	real *emiCO2_b;
	real *temp_b;
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
// *************************************************************
//						BEGIN: KERNEL (estim_model)
// *************************************************************
void costC02_fun(env_t *env,real * cumCO2,real * costCO2_fct){
			*costCO2_fct= env->cost_emi_param[0]/(env->cost_emi_param[1] + exp(-env->cost_emi_param[2]*(*cumCO2-env->cost_emi_param[3]))) -
    		              env->cost_emi_param[4]*pow((env->cost_emi_param[5]/(*cumCO2-env->cost_emi_param[5])),env->cost_emi_param[6]);
	}
void climate_theta(const real min,const real max,const real center,const real steep,real *past,real *theta_temp){
	
	real diff = (max - min);
	// theta_temp: theta_amen_temp or theta_real_temp
	for (size_t t = 0; t < T_FORWARD; t++)
		for (int i = 0; i < NPOSLAND; i++)
			theta_temp[IPOSLANDT(i, t)]= min + diff / (1+exp(steep*past[IPOSLANDT(i, t)] - center));
}
void climate_read_parameters(env_t *env,real *realgdp0_w){
	// Read parameters
		// - from env: m2_i,coeff_pop_i,upsilon_fossil_i,upsilon_clean_i
		// - from env: l0_model and realgdp0_model. 
		// 	- Consider not storing l0_model and realgdp0_model 			****** DEVELOP ******
	real sum = 0;
	for (int i = 0; i < NPOSLAND; i++){
		sum+=env->l0_model[i]*env->realgdp0_model[i]*env->H[i];
	}
	sum = sum/env__lbar;
	*realgdp0_w=sum;
}
void forward_climate(env_t *env){
	// 1. Initialize output variables
	// 2. Initialize parameters and variables of initital period
	real realgdp0_w;climate_read_parameters(env,&realgdp0_w);
#ifdef DEBUG_MODE	
	printf("\n\nrealgdp0_w = %.16lf",realgdp0_w);
#endif
}
void backward_climate(env_t *env){
	// 1. Initialize output variables
	// 2. Initialize parameters and variables of initital period
	real realgdp0_w;climate_read_parameters(env,&realgdp0_w);
#ifdef DEBUG_MODE	
	printf("\n\nrealgdp0_w = %.16lf",realgdp0_w);
#endif
	// Set damages on amenities and productivities
	// temp_past_out = temp_past; (Not used)
	real *theta_amen_temp = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	real *theta_prod_temp = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	
#ifdef DEBUG_MODE
	printf("\n----------------------------theta_amen\n"); // NPOSLAND * T_BACK
	printf("%.16g %.16g %.16g %.16g\n",env->theta_amen_scen[ISCEN(0,8)],	// min
	              env->theta_amen_scen[ISCEN(1,8)],	// max
				  env->theta_amen_scen[ISCEN(2,8)],	// center
				  env->theta_amen_scen[ISCEN(3,8)]	// steep		   
	);
#endif
	climate_theta(env->theta_amen_scen[ISCEN(0,8)],	// min
	              env->theta_amen_scen[ISCEN(1,8)],	// max
				  env->theta_amen_scen[ISCEN(2,8)],	// center
				  env->theta_amen_scen[ISCEN(3,8)],	// steep
				  env->temp_past,
				  theta_amen_temp);					// output
	climate_theta(env->theta_prod_scen[ISCEN(0,8)], // min
	              env->theta_prod_scen[ISCEN(1,8)],	// max
				  env->theta_prod_scen[ISCEN(2,8)],	// center
				  env->theta_prod_scen[ISCEN(3,8)],	// steep
				  env->temp_past,
				  theta_prod_temp);				  	// output
	
	free(theta_amen_temp);
	free(theta_prod_temp);

}
void initialize_weight_pop_matrix(env_t *env,real *weight_pop_matrix){
	
	real sum_pop[T_BACK_AUX];
	real offset = 0;
	for(int t=0;t<T_BACK_AUX;t++)
	{
		sum_pop[t]=0;
		offset = offset + t;
		for(int i=0;i<LENGTH_ISO;i++){
			int index = (i)*T_BACK_AUX+offset;
        	sum_pop[t]=sum_pop[t]+env->pop_data[index];
		}
		for(int i=0;i<LENGTH_ISO;i++){
			int index = (i)*T_BACK_AUX+offset;
			weight_pop_matrix[index]=env->pop_data[index]/sum_pop[t];
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
void update_period_20(env_t *env){
	real growth_l = pow(1.01,20);
	real growth_gdp = pow(1.02,20);
	for(int i=0;i<NPOSLAND;i++){
		env->l20_model[i] = growth_l*env->l0_model[i];
		env->realgdp20_model[i] = growth_gdp*env->realgdp0_model[i];
		env->temp20_local[i] = env->temp0_local[i] + TEMPLINSCALER*env->scaler_temp[i];
	}

}
void model_initial_period(env_t *env)
{
	real *FL = (real *)malloc(NPOSLAND * sizeof(real));
	real *FR = (real *)malloc(NPOSLAND * sizeof(real));
	real *uhat_i = (real *)malloc(NPOSLAND * sizeof(real));
	real *uhat_f = (real *)malloc(NPOSLAND * sizeof(real));
	real *integral = (real *)malloc(NPOSLAND * sizeof(real));
	// **** initalized in init_model_initial_period ****/
	// Precompute auxiliary variables to equation (75)
	for (int i = 0; i < NPOSLAND; i++)
	{
		real FL_H_m2 = env->FL_H_m2_left[i] * pow(env->m2_i[i], env->FL_H_m2_right_exp);																			   // outside the integral
		real FR_H_m2 = env->FR_H_m2_left[i] * pow(env->m2_i[i], env->FR_H_m2_right_exp);																			   // inside the integral
		FL[i] = pow(env->a_norm[i], env->FL_a_norm_exp) * pow(env->prod0[i], (env->FL_prod0_exp)) * pow(env->price_energy0[i], (env->FL_price_energy0_exp)) * FL_H_m2; // outside the integral
		FR[i] = pow(env->a_norm[i], env->FR_a_norm_exp) * pow(env->prod0[i], (env->FR_prod0_exp)) * pow(env->price_energy0[i], (env->FR_price_energy0_exp)) * FR_H_m2; // inside the integral
		uhat_i[i] = 1;																																				   // guess on utility function
		integral[i] = FR[i] * pow(uhat_i[i], env->exp_uhatR);
		//printf("%lf %lf %lf %lf\n",FL[i],FR[i],uhat_i[i],integral[i]);
	}
	// Iterate uhat, equation (75)
	real error = TOLL_MODEL_INITIAL_PERIOD + 1.;
	int iter=0;
	while (error >= TOLL_MODEL_INITIAL_PERIOD)
	{
		for (int i = 0; i < NPOSLAND; i++)
		{
			real rhs = 0;
			for (int j = 0; j < NPOSLAND; j++)
			{
				rhs += env->trmult_reduced[IPOSLAND(i, j)] * integral[j];
			}
			uhat_f[i] = FL[i] * pow(rhs, (env->uhat_f_exp));
			//printf("%lf \n",uhat_f[i]);
		}

		// Compute accuracy and update the guess
		error = 0;
		for (int i = 0; i < NPOSLAND; i++)
		{
			real deviation = (uhat_i[i] - uhat_f[i]);
			error += deviation * deviation;
			// Update the Guess
			uhat_i[i] = uhat_f[i];
			integral[i] = FR[i] * pow(uhat_i[i], env->exp_uhatR);
		}

		iter=iter+1;
		printf("%d\n",iter);

	} // end while

	printf("Error: %lf\n",error);
	// Accumulators
	real one_over_omega = 1./env__Omega;
	real sum_u0m2 = 0.;						
	for (int i = 0; i < NPOSLAND; i++){
		real aux_u0m2 = pow(uhat_i[i],one_over_omega)*pow(env->m2_i[i],(-one_over_omega));
		sum_u0m2 +=  aux_u0m2; 						
		env->l0_model[i]=1./env->H[i]*aux_u0m2;
	}
	real lbar_u0m2 = env__lbar / sum_u0m2;
	real lbar_u0m2_pow = pow(lbar_u0m2,env->flat/env__theta);
	for (int i = 0; i < NPOSLAND; i++)
	{
		env->l0_model[i]=env->l0_model[i] * lbar_u0m2;
		real u0 = uhat_i[i] * lbar_u0m2_pow;
		env->realgdp0_model[i] = (u0 / env->a_norm[i])*pow(env->l0_model[i],env__lambda);
	}

	// Free memory allocation
	free(FL);
	free(FR);
	free(uhat_i);
	free(uhat_f);
	free(integral);
}
void estim_model(env_t *env)
/* Function that estimates the parameters of the natality rate function,
 * the migration cost function and the elasticities of energy productivity
 * growth to global real income growth.
 */
{
	real *weight_pop_matrix = (real *)calloc(NDATA, sizeof(real));	// Population Shares, NDATAx1
	model_initial_period(env);
	printf("env->realgdp0_model: %lf, %lf, %lf",env->realgdp0_model[0],env->realgdp0_model[NPOSLAND-2],env->realgdp0_model[NPOSLAND-1]);
	update_period_20(env);
	initialize_weight_pop_matrix(env,weight_pop_matrix);
	free(weight_pop_matrix);

	sym_t sym_;
	// Simulation Backward variables
	sym_.l_b = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	sym_.realgdp_b = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	sym_.emiCO2_b = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	sym_.temp_b = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	sym_.clean_b = (real *)calloc(NPOSLAND*T_BACK, sizeof(real));
	// Simulation Forward variables
	sym_.l = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	sym_.prod = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	sym_.realgdp = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	sym_.amen = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	sym_.temp_local = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	sym_.price_emi = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	sym_.price_clean = (real *)calloc(NPOSLAND*T_FORWARD, sizeof(real));
	
	// Backward climate 
	backward_climate(env);

	// Deallocate Memory
	free(sym_.l_b);
	free(sym_.realgdp_b);
	free(sym_.emiCO2_b);
	free(sym_.temp_b);
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
//						END: KERNEL (estim_model)
// *************************************************************
// 21. Preallocation model_initial_period
void init_model_initial_period(env_t *env)
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

	/*
	// Backward Climate Preallocation
	// Precompute auxiliary variables
	env->const_phi = pow((env__gamma1/env__ksi)/(env__nu*(env__mu+env__gamma1/env__ksi)),(1./env__ksi));
	real squ_b = (env__alpha-1+(env__lambda+env__gamma1/env__ksi-(1-env__mu)-env__gamma1/(env__ksi*env__gamma2))*env__theta); // term in square brackets of natural_R and natural_L
	real naturalL = env__lambda - squ_b/denom;
	real naturalR = 1 - env__lambda*env__theta+(1+env__theta)*squ_b/denom;
	real natural = naturalR - env__theta*naturalL;
	exp_uhatL = naturalL/env__Omega + (1+env__theta)/denom;
	exp_uhatR = naturalR/env__Omega - env__theta*env__theta/denom;

	env->naturalL=naturalL;
	env->naturalR=naturalR;
	env->natural=natural;
	env->BW_exp_uhatL=exp_uhatL;
	env->BW_exp_uhatR=exp_uhatR;

	// Precompute auxiliary variables to equation (88)
	env->BL_H_m2_left[]=H.^((naturalL-1/denom)/exp_uhatL);
	env->BL_H_m2_left_exp=naturalL/(Omega*exp_uhatL);
	env->BR_H_m2_right[]=H.^(-naturalR+env__theta/denom);
	env->BR_H_m2_right_exp=-naturalR/Omega;

	// Set guesses
	ones_N = ones(env->n,1); // guess for uhat
	ltilde = round(env__lbar/(1+env->natal0)); // guess for global population
	lbar1 = env__lbar;
	*/
}
void init_all(env_t *env) //, input_t *in, vars_t *vars)
{
	// Prellocate
	env->H = (real *)calloc(NPOSLAND, sizeof(real));
	env->prod0 = (real *)calloc(NPOSLAND, sizeof(real)); // productivities in 2000
	env->pop5_dens = (real *)calloc(NPOSLAND, sizeof(real));
	env->u0 = (real *)calloc(NPOSLAND, sizeof(real));						 // utility in 2000
	env->a_norm = (real *)calloc(NPOSLAND, sizeof(real));					 // amenities in 2000
	env->trmult_reduced = (real *)calloc(NPOSLAND * NPOSLAND, sizeof(real)); // Bilateral trade cost on Earth cells at t=0 only
	env->C_vect = (small_idx_t *)calloc(NPOSLAND, sizeof(small_idx_t));		 // national demarcations with H0>0
	env->emi_no_ff = (real *)calloc(N2600, sizeof(real));					 // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC					// utility in 2000
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
	env->FL_H_m2_left = (real *)calloc(NPOSLAND, sizeof(real));
	env->FR_H_m2_left = (real *)calloc(NPOSLAND, sizeof(real));
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
	env->upsilon_clean_i = GUESS__upsilon_clean_i;
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "m2_i");
	read_binary(env->m2_i, variablename, NPOSLAND); // SET VARIABLE

	// Initialize Auxiliary to model_init_period
	init_model_initial_period(env);

	return;
}
void free_all(env_t *env)
{
	// Free all Variables you have malloced in init_all
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
	free(env->FL_H_m2_left);
	free(env->FR_H_m2_left);
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
	printf("\n----------------------------theta_amen\n"); // NPOSLAND * T_BACK
	printf("%.16g %.16g %.16g %.16g\n",env.theta_amen_scen[ISCEN(0,8)],	// min
	              env.theta_amen_scen[ISCEN(1,8)],	// max
				  env.theta_amen_scen[ISCEN(2,8)],	// center
				  env.theta_amen_scen[ISCEN(3,8)]	// steep		   
	);
	/*
	printf("\n----------------------------theta_amen\n"); // NPOSLAND * T_BACK
	for (size_t i = 0; i < 32; i++)
		printf("%.16lf ",env.theta_amen_scen[i]);
	printf("\n----------------------------temp_past\n"); // NPOSLAND * T_BACK_AUX
	printf("%.16g %.16g %.16g %.16g\n", env.temp_past[IPOSLANDT(0, 0)],
		   env.temp_past[IPOSLANDT(NPOSLAND - 1, T_BACK_AUX - 1)],
		   env.temp_past[IPOSLANDT(14000, 3)],
		   env.temp_past[IPOSLANDT(15650, 47)]);
	printf("\n----------------------------Delta_temp\n"); // NPOSLAND * T_BACK
	printf("%.16g %.16g %.16g %.16g\n", env.Delta_temp[IPOSLANDT(0, 0)],
		   env.Delta_temp[IPOSLANDT(NPOSLAND - 1, T_BACK - 1)],
		   env.Delta_temp[IPOSLANDT(11000, 3)],
		   env.Delta_temp[IPOSLANDT(17000, 47)]);
	*/

	// Kernel
	estim_model(&env);
	// Free all Variables you have malloced in init_all
	free_all(&env);
}
