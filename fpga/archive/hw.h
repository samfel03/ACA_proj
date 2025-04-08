/**
 * @file hw.h
 * @brief A Documented file of functions used in fpga code.
 */
#pragma once

#include "../common/definitions.h"
#if USE_HLS_LIB
// #include <hls_math.h>
#else
#include <math.h>
#endif

#include <iostream>
#include <ctime>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/** Structs */
typedef struct hw_env_t
{
	real alpha;			///< share of the capital in production {0-1}
	
#if !USE_PREALLOC_VALUES
	real k[NKGRID];		  ///< grid of capital
#endif

} hw_env_t;

extern "C"
{
	/** Initialization */
	/** Utilities */
	real hw_pow(real x, real y);
	real hw_exp(real b);
	real hw_log(real b);
	real hw_sqrt(real b);
	real hw_fabs(real b);
	
	/**
	 * @brief initialize
	 *
	 * @param st_kprimes	capital
	 * @param st_kcross		capital distribution
	 */
	void hw_top_init(real *V_in,real st_V[NUM_KPRIMES][NSTATES],
					 real *k_in,real st_k[NKGRID],
					 real *wealth_in,real st_wealth[NSTATES]);

	void hw_vfi(real st_V[NUM_KPRIMES][NSTATES],
				real st_wealth[NSTATES],
				small_idx_t st_Gk[NUM_KPRIMES][NSTATES],
				real st_k[NKGRID],
				int &ihp_iter);
	void runOnfpga(
		preinit_t *preinit,
		out_t *results,
		int *iter_out);

} // end extern C

