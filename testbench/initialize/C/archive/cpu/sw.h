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
	void model_initial_period(real *m2, real *l0_model, real *realgdp0_model);
	/**
	 * @brief kernel function to run on FPGA
	 *
	 * @param env input env variables
	 * @param vars input variables
	 * @param agshock_in input aggregate shocks
	 * @param idshock_in input idiosyncratic shocks
	 * @param out output final kprime, kcross, r2, coeff
	 * @param iter_out  output number of iteration of EGM function
	 */
	void runOncpu(env_t *env);
	/*
		var_t *vars,
		const unsigned char *agshock_in,
		const unsigned char *idshock_in,
		out_t *out,
		int *iter_out);
		*/
}