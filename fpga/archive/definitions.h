#pragma once
#include <stdio.h>
#include <stdlib.h> // must be prior to sds_lib.h
#include <string.h>
#include <assert.h>
// #include <cstdint>

/** Development options */
#include "dev_options.h"

/** Hardware includes */
//#include <ap_int.h>
//#include <ap_fixed.h>

/** Typedefs */
typedef double real;
typedef unsigned short small_idx_t;
typedef unsigned int idx_t;
typedef unsigned char shock_t; 

// #if FIXED_ACC
// typedef ap_fixed<72, 21> fixed_t;	// ap_[u]fixed<W,I,Q,O,N> where W is word length in bits and I is no. of bits above the decimal point
// typedef ap_fixed<72, 21> emu_s_t;	// fixed precision
// typedef ap_fixed<72, 21> kc_t;		// data type for agg capital calc
// #else
typedef real fixed_t;	
typedef real emu_s_t;	 // data type for expectation term in IAP
typedef real spread_t; // data type for agg capital calc
//#endif

#define ID_MASTER           0       ///< never touch it
#define N_MODEL             1       ///< total number of models

/** Paths */
#define FPGA_V_OUT_FILE				"./results/fpga/V_"
#define CPU_V_OUT_FILE			"./results/seq_cpu/V_"
#define CPU_EXEC_OUT_FILE			"./results/seq_cpu/exec_time_"
#define FPGA_EXEC_OUT_FILE			"./results/fpga/exec_time_"


/** Application constants */
#define NKGRID 8 //512
#define NSTATES 8
const real KMIN(0.1);				// minimum grid-value of capital
const real KMAX(1000.0);			// maximum grid-value of capital
const real power_polynomial_KGRID(7.);	// Exponent of polynomial rule on capital grid
const real VERY_SMALL_POSITIVE_SCALAR(0.0000000001);
const real VERY_NEGATIVE_SCALAR(-1.7977e+300);

/** Programming constants */
#define MAX_FILENAME_LEN 150

/** Auxiliary constants */
#define XMIN ((real)0.0)
#define BYTE_PACK_FACTOR 8 // 8 bits to byte

/** Environment variables */
const real env__alpha(0.36);			   // 0.36 (Output capital share)
const real env__alpha_c((-0.64));		   // alpha - 1
const real env__beta(0.99);				   // 0.99 (Quarterly subjective discount factor)
// CRRA
const real env__gamma(2.0);				   // 1 (Arrow-Pratt relative risk aversion coefficien)
const real env__one_minus_gamma(-1.);	   // Utility exponent: 1-gamma
const real env__one_over_one_minus_gamma(-1.);	// Scaling utility: 1/(1-gamma)
// END CRRA
const real env__delta(0.025);			   // 0.025 (Quarterly depreciation rate)
const real env__delta_c(0.975);			   // 1. - delta

/** Macros */
//#define IXV(a, km, id, k) (NKM_GRID * NSTATES_ID * NKGRID * a + NSTATES_ID * NKGRID * km + NKGRID * id + k)

/** Convergence */
#define TOLL_V ((real)(1e-10))

/** Parameters and constant arrays */
typedef struct env_t
{
	// full: 1618+16+10+100+4+100+4+14
	real k[NKGRID];								// grid of capital
	real wealth[NSTATES];						// wealth	
	real V[NSTATES]; 							// Value function
} env_t;

/**
 * @brief Container for inputs
 *
 * Stores randomly generated indiviual shocks
 * and aggregate shocks.
 */
typedef struct input_t		// Required for two reasons: 1. same type; 2. because created multiple copies for each SLR
{
	/*
	shock_t *idshock;		// array of size 1,375,000
	shock_t *agshock; // array of size 138 ceil(1100/8)
	*/
} input_t;

/**
 * @brief Container for value/policy functions
 *
 *
 */
typedef struct vars_t
{
	/*
	*/
	
} var_t;

/**
 * @brief final results to be read back
 *
 */
typedef struct out_t
{
	real V[NSTATES];
	small_idx_t Gk[NSTATES]; 	// index of capital function
	
} out_t;

/**
 * @brief pre initialized values to device
 *
 */
typedef struct preinit_t
{
	real k[NKGRID];
	real wealth[NSTATES];
	real V[NSTATES];
} preinit_t;
