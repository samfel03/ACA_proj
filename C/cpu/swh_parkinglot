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
	void top_init(real *kp_in, real *st_kprimes, real *st_kcross);

	/** Utilities */
	void hw_rail_values(real *val, const real max, const real min);

	/** Linear interpolation */
	small_idx_t hw_findrange(real p, const real *src, int n_elem);

	void matrixfunction(double *resultmatrix, double *x, double *y, int ndim);

	double RSquaredCalc(double *coeff, double *x, double *y, int ndim);

	/** Simulation */
	void hw_sim_alm(real *kmprime, real *coeff, real *km_grid);

	void hw_sim_egm(real *kmprime, real *st_kprimes, env_t *st_env, int &hw_egm_iter);

	void hw_sim_ast(real *kmts, const unsigned char *idshock, const unsigned char *agshock,
					env_t *st_env, real *st_kprimes, real *st_kcross);

	void sim_alm_coeff(const real *kmts, real *coeff, double *metric, real *r2,
					   const unsigned char *agshock);

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
	void runOncpu(
		env_t *env,
		var_t *vars,
		const unsigned char *agshock_in,
		const unsigned char *idshock_in,
		out_t *out,
		int *iter_out);
}