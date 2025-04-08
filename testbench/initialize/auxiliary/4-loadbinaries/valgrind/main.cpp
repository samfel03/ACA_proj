#include <iostream>
#include <stdlib.h>
#include <cstring>  // memset,strcpy,strcat
using namespace std;
//#define real double
typedef double real;
typedef unsigned short small_idx_t;
#define INPUTPATH "/scratch/summit/alpe9373/CCE-C/input/"
#define N_MODEL 1
#define IND_DAM 9	 	// Level of the damage function, 9 is the benchmark
#define NPOSLAND 17048	// Number of cells with positive land
#define N2600 600 		// Years period: 2000-2600
#define N2600_2 601 	// Years period: 2000-2600 (forc_noCO2)
#define NDATA 8568		// country_data, year_data, natal_data, pop_data
#define NCLEANENERGY 35	// clean_energy_data
#define T_BACK_AUX 51 	// Used in temp_past
/** Simulation settings */
#define T_BACK 50	   	// Number of periods to run backward the model
#define T_FORWARD 50	// Number of periods to run forward the model
typedef struct env_t
{
	real *H;			 // NPOSLAND 
	real *prod0;		 // productivities in 2000
	real *pop5_dens;	 //
	real *u0;	 // utility in 2000
	real *a_norm; // amenities in 2000
	real *trmult_reduced; // Bilateral trade cost on Earth cells at t=0 only
	small_idx_t *C_vect;		// national demarcations with H0>0
	small_idx_t length_C_vect; // length of C_vect
	real emi0_ff;	  // Global CO2 emissions from fossil fuels for 2000 (interpreted *****) - scalar
	real *emi_no_ff; // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC, N2600x1 (600x1)
	real emi0;		  // total CO2 emissions for 2000, scalar
	real fossil_share; // Construct share of fossil fuels in energy composite, scalar
	real chi;		   // Construct share of energy in production, equations (7) and (44), scalar
	real cost_CO2_data;		 // Cost extraction data, 202x2
	real cost_emi_param[7];	 // Redefine extraction cost function 1x7: [cost_emi_param_f maxCO2 3];
	real price_clean0_world; // Define normalization relative to Princeton wage: usdP/GtCO2
	real *price_energy0; 	//, (17048x1)
	real *zeta_clean0; 		// Construct initial energy productivities, (17048x1)
	real *zeta_fossil0;		//, (17048x1)
	real S0;	// Initialize CO2 stock layers, equations (38) and (39), scalar
	real S1;	// , scalar
	real S2;	// , scalar
	real S3;	// , scalar
	real *forc_noCO2; // Read non CO2 radiative forcing, 601x1
	real temp1;			// Initialize temperature layers, equation (41), scalar
	real temp2;			// , scalar
	real temp0_global;	// , scalar
	real *temp0_local; 		// Local temperatures, 17048x1
	real *temp_past;		// , 17048x51 (NPOSLAND,T_BACK_AUX)
	real *Delta_temp;		// , 17048x50 (NPOSLAND,T_BACK)	 
	real *scaler_temp;		// , 17048x1
	real *theta_amen_scen;	// 4x9
	real *theta_prod_scen;	// 4x9
	real *natal_data;		// data for years < 2001, 8568x1 
	real *pop_data;			// data for years < 2001, 8568x1 
	real natal0;			// Natality rates of 2000, scalar
	real natal20;			// Natality rates of 2020, scalar
	real clean_energy_data[NCLEANENERGY];	//35x1
	real emi_ff_data[T_BACK]; // Historical fossil fuel CO2 emission and its trend, 50x1
	real emi_ff_data_tend[T_BACK];	// , 50x1
	real coeff_pop_i[8];	// Guess for coefficients on the natality rate function.
	real upsilon_fossil_i;  // Guess for the elasticity of fossil fuel productivity growth to global real GDP growth
	real upsilon_clean_i;	// Guess for the elasticity of clean energy productivity growth to global real GDP growth
	real m2_i;				// Load guess for migration costs (estim_model.m)
	real l0_model;
	real realgdp0_model;
	real flatL;
	real flatR;
	real flat;
	real exp_uhatL;
	real exp_uhatR;
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

void read_binary(real *X_var, char *variablename, int dim_n){

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
  fprintf(stderr, "\nVariable %s is of size: %lu bytes\n",variablename,SIZE_var);

  // Read binary
  for(int i=0;i<dim_n;i++){
    fread(&X_var[i],sizeof(X_var[0]),1,fp);
  }  

  fclose(fp);
  fp = NULL;
  return;
}
void init_all(env_t *env) //, input_t *in, vars_t *vars)
{
  // Prellocate
	env->H = (real *)calloc(NPOSLAND,sizeof(real));
	env->prod0 = (real *)calloc(NPOSLAND,sizeof(real)); // productivities in 2000
	env->pop5_dens = (real *)calloc(NPOSLAND,sizeof(real));
	env->u0 = (real *)calloc(NPOSLAND,sizeof(real));						  // utility in 2000
	env->a_norm = (real *)calloc(NPOSLAND,sizeof(real));					  // amenities in 2000
	env->trmult_reduced = (real *)calloc(NPOSLAND*NPOSLAND,sizeof(real)); // Bilateral trade cost on Earth cells at t=0 only
	env->C_vect = (small_idx_t *)calloc(NPOSLAND,sizeof(small_idx_t));	  // national demarcations with H0>0
	env->emi_no_ff = (real *)calloc(N2600,sizeof(real));					  // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC					// utility in 2000
	env->price_energy0 = (real *)calloc(NPOSLAND,sizeof(real));
	env->zeta_clean0 = (real *)calloc(NPOSLAND,sizeof(real));
	env->zeta_fossil0 = (real *)calloc(NPOSLAND,sizeof(real));
	env->forc_noCO2 = (real *)calloc(N2600_2,sizeof(real)); // Read non CO2 radiative forcing, 601x1
	env->temp_past = (real *)calloc(NPOSLAND * T_BACK_AUX,sizeof(real));
	env->Delta_temp = (real *)calloc(NPOSLAND * T_BACK,sizeof(real));
	env->scaler_temp = (real *)calloc(NPOSLAND,sizeof(real));
	env->theta_amen_scen = (real *)calloc(4 * 9,sizeof(real));
	env->theta_prod_scen = (real *)calloc(4 * 9,sizeof(real));
	env->natal_data = (real *)calloc(NDATA,sizeof(real));
	// ********************************** READ THE VARIABLES FROM INPUT
	char variablename[250] = {'\0'};
	// ---------------------------------------------------------------------------
  memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "H");read_binary(env->H, variablename,NPOSLAND); // SET VARIABLE
  	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "prod0");read_binary(env->prod0, variablename,NPOSLAND); // SET VARIABLE
  	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "pop5_dens");read_binary(env->pop5_dens, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "u0");read_binary(env->u0, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "a_norm");read_binary(env->a_norm, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "trmult_reduced");read_binary(env->trmult_reduced, variablename,NPOSLAND* NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	real *C_vect_real = (real *)malloc(NPOSLAND * sizeof(real));
  	strcpy(variablename, "C_vect");read_binary(C_vect_real, variablename, NPOSLAND); // ************* VARIABLE
  	for(int i=0;i<NPOSLAND;i++)
    	env->C_vect[i]=(small_idx_t) C_vect_real[i];
  	free(C_vect_real);
  // ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "emi_no_ff");read_binary(env->emi_no_ff, variablename,N2600); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "price_energy0");read_binary(env->price_energy0, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "zeta_clean0");read_binary(env->zeta_clean0, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "zeta_fossil0");read_binary(env->zeta_fossil0, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "forc_noCO2");read_binary(env->forc_noCO2, variablename,N2600_2); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "temp_past");read_binary(env->temp_past, variablename,(int)(NPOSLAND* T_BACK_AUX)); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "Delta_temp");read_binary(env->Delta_temp, variablename,NPOSLAND * T_BACK); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "scaler_temp");read_binary(env->scaler_temp, variablename,NPOSLAND); // SET VARIABLE
	// ---------------------------------------------------------------------------
	//BABA memset(variablename, '\0', sizeof(variablename));
	//BABA strcpy(variablename, "theta_amen_scen");read_binary(env->theta_amen_scen, variablename,4*9); // SET VARIABLE
	// ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "natal_data");read_binary(env->natal_data, variablename,NDATA); // SET VARIABLE
	// ---------------------------------------------------------------------------
	//BABA memset(variablename, '\0', sizeof(variablename));
	//BABA strcpy(variablename, "theta_prod_scen");read_real_1D(env->theta_prod_scen, variablename); // ************* VARIABLE
	// ********************************** END READ THE VARIABLES FROM INPUT
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
	free(env->temp_past);
	free(env->Delta_temp);
	free(env->scaler_temp);
	free(env->theta_amen_scen);
	free(env->theta_prod_scen);
	free(env->natal_data);
	return;
}

int main(){
  env_t env;
  // Initialize all variables
  init_all(&env);
  // Prellocate
  /*
	env.H = (real *)calloc(NPOSLAND,sizeof(real));
	env.prod0 = (real *)calloc(NPOSLAND,sizeof(real)); // productivities in 2000
	env.pop5_dens = (real *)calloc(NPOSLAND,sizeof(real));
	env.u0 = (real *)calloc(NPOSLAND,sizeof(real));						  // utility in 2000
	env.a_norm = (real *)calloc(NPOSLAND,sizeof(real));					  // amenities in 2000
	env.trmult_reduced = (real *)calloc(NPOSLAND*NPOSLAND,sizeof(real)); // Bilateral trade cost on Earth cells at t=0 only
	env.C_vect = (small_idx_t *)calloc(NPOSLAND,sizeof(small_idx_t));	  // national demarcations with H0>0
	env.emi_no_ff = (real *)calloc(N2600,sizeof(real));					  // Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC					// utility in 2000
	env.price_energy0 = (real *)calloc(NPOSLAND,sizeof(real));
	env.zeta_clean0 = (real *)calloc(NPOSLAND,sizeof(real));
	env.zeta_fossil0 = (real *)calloc(NPOSLAND,sizeof(real));
	env.forc_noCO2 = (real *)calloc(N2600_2,sizeof(real)); // Read non CO2 radiative forcing, 601x1
	env.temp_past = (real *)calloc(NPOSLAND * T_BACK_AUX,sizeof(real));
	env.Delta_temp = (real *)calloc(NPOSLAND * T_BACK,sizeof(real));
	env.scaler_temp = (real *)calloc(NPOSLAND,sizeof(real));
	env.theta_amen_scen = (real *)calloc(4 * 9,sizeof(real));
	env.theta_prod_scen = (real *)calloc(4 * 9,sizeof(real));
	env.natal_data = (real *)calloc(NDATA,sizeof(real));
  */
  // Free all Variables you have malloced in init_all
  free_all(&env);
  /*
  free(env.H);
	free(env.prod0);
	free(env.pop5_dens);
	free(env.u0);
	free(env.a_norm);
	free(env.trmult_reduced);
	free(env.C_vect);
	free(env.emi_no_ff);
	free(env.price_energy0);
	free(env.zeta_clean0);
	free(env.zeta_fossil0);
	free(env.forc_noCO2);
	free(env.temp_past);
	free(env.Delta_temp);
	free(env.scaler_temp);
	free(env.theta_amen_scen);
	free(env.theta_prod_scen);
	free(env.natal_data);
  */
}

/*
int main()
{
  real *H = (real *)malloc(NPOSLAND * sizeof(real));
  small_idx_t *C_vect = (small_idx_t *)malloc(NPOSLAND * sizeof(small_idx_t));	  // national demarcations with H0>0
  real *trmult_reduced = (real *)malloc(NPOSLAND * NPOSLAND * sizeof(real));
  int indice;
  // ********************************** READ THE VARIABLES FROM INPUT
	char variablename[250] = {'\0'};
  // ---------------------------------------------------------------------------
  memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "trmult_reduced");read_binary(trmult_reduced, variablename,NPOSLAND* NPOSLAND); // SET VARIABLE
  indice=10000;printf("v[%d]=%.36g\n",indice,trmult_reduced[indice]);
  indice=14782;printf("v[%d]=%.36g\n",indice,trmult_reduced[indice]);
  // ---------------------------------------------------------------------------
  memset(variablename, '\0', sizeof(variablename));
	strcpy(variablename, "H");read_binary(H, variablename,NPOSLAND); // SET VARIABLE
  indice=10000;printf("v[%d]=%.36g\n",indice,H[indice]);
  indice=14782;printf("v[%d]=%.36g\n",indice,H[indice]);
  // ---------------------------------------------------------------------------
	memset(variablename, '\0', sizeof(variablename));
  real *C_vect_real = (real *)malloc(NPOSLAND * sizeof(real));
  strcpy(variablename, "C_vect");read_binary(C_vect_real, variablename, NPOSLAND); // ************* VARIABLE
  for(int i=0;i<NPOSLAND;i++)
    C_vect[i]=(small_idx_t) C_vect_real[i];
  free(C_vect_real);
	indice=10000;printf("v[%d]=%d\n",indice,C_vect[indice]);
  indice=14782;printf("v[%d]=%d\n",indice,C_vect[indice]);
  // Dellocate
  free(trmult_reduced);
  free(C_vect);
  free(H);
  return 0;
}
*/