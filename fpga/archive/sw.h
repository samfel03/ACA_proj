#pragma once

#ifdef FPGA_MODE
#include <hls_math.h>
#else
#include <math.h>
#endif

#include <iostream>
#include <ctime>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "definitions.h"

extern "C"
{
	/** Initialization */
	void top_init(real *V_in, real *st_V);

	/** Simulation */
	void sw_vfi(real *st_V, small_idx_t *st_Gk, env_t *env, int &hw_iter);

	/**
	 * @brief kernel function to run on FPGA
	 *
	 * @param env input env variables
	 * @param out output final kprime, kcross, r2, coeff
	 * @param iter_out  output number of iteration of EGM function
	 */
	void runOncpu(
		env_t *env,
		out_t *out,
		int *iter_out);
}