#include <iostream>
#include <stdlib.h>
#include <cstring> // memset,strcpy,strcat
using namespace std;
//#define real double
typedef double real;
typedef unsigned short small_idx_t;
#define INPUTPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/"
#define PRINTPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/output/"
#define N_MODEL 1
#define IND_DAM 9		// Level of the damage function, 9 is the benchmark
#define NPOSLAND 17048	// Number of cells with positive land
#define N2600 600		// Years period: 2000-2600
#define N2600_2 601		// Years period: 2000-2600 (forc_noCO2)
#define NDATA 6		// country_data, year_data, natal_data, pop_data
#define LENGTH_ISO 3		// NDATA/(2000-1950+1)=168
#define T_BACK_AUX 2	// Used in temp_past

#define NCLEANENERGY 35 // clean_energy_data
/** Simulation settings */
#define T_BACK 50								// Number of periods to run backward the model
#define T_FORWARD 50							// Number of periods to run forward the model
#define IPOSLAND(i,j) ((j) * NPOSLAND + (i))		// location i-location j cost: col_idx*NROWS+ row_idx 
#define IPOSLANDT(i,t) ((t) * NPOSLAND + (i))		// time t-location i: col_idx*NROWS+ row_idx 
#define DEBUG 1
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
	real cost_emi_param[7];				  // Redefine extraction cost function 1x7: [cost_emi_param_f maxCO2 3];
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
	real emi_ff_data[T_BACK];			  // Historical fossil fuel CO2 emission and its trend, 50x1
	real emi_ff_data_tend[T_BACK];		  // , 50x1
	real coeff_pop_i[8];				  // Guess for coefficients on the natality rate function.
	real upsilon_fossil_i;				  // Guess for the elasticity of fossil fuel productivity growth to global real GDP growth
	real upsilon_clean_i;				  // Guess for the elasticity of clean energy productivity growth to global real GDP growth
	real m2_i;							  // Load guess for migration costs (estim_model.m)
	real l0_model;
	real realgdp0_model;
	real flatL;
	real flatR;
	real flat;
	real exp_uhatL;
	real exp_uhatR;
	real aux_denom;
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
int main()
{
	real pop_data[NDATA] = {1,2,3,4,5,6};
	real weight_pop_data[NDATA];
	real sum_pop[T_BACK_AUX];
	printf("pop_data:\n");
	for(int i=0;i<NDATA;i++)
	{
		printf("%f ",pop_data[i]);
	}
	printf("\n");

	// Real 
	real offset = 0;
	for(int t=0;t<T_BACK_AUX;t++)
	{
		sum_pop[t]=0;
		offset = offset + t;
		for(int i=0;i<LENGTH_ISO;i++){
			int index = (i)*T_BACK_AUX+offset;
        	sum_pop[t]=sum_pop[t]+pop_data[index];
		}
		for(int i=0;i<LENGTH_ISO;i++){
			int index = (i)*T_BACK_AUX+offset;
			weight_pop_data[index]=pop_data[index]/sum_pop[t];
		}
	}

	printf("weight_pop_data:\n");
	for(int i=0;i<NDATA;i++)
	{
		printf("%f ",weight_pop_data[i]);
	}
	printf("\n");
	return 0;

}

