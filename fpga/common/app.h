#pragma once

#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include <time.h>
#include <math.h>
#include <cstdint>
#include <chrono>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sstream>
#include <array>
#include <map>

#ifdef _FPGA_MODE
#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl2.hpp>
#include "xcl2.hpp"
#include "../fpga/hw.h"
// /#elif _SERIAL_CPU_MODE
// #include "sw.h"
// #elif OMPI_MODE
// #include "mpi.h"
// #include "sw.h"
#endif

#include "stopwatch.h"
#include "dev_options.h"
#include "definitions.h"

const size_t size_of_trmult_reduced = sizeof(real);

extern std::string binaryFile;

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
