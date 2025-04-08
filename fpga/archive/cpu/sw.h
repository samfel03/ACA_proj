#pragma once
/*
#ifdef FPGA_MODE
#include <hls_math.h>
#else
#include <math.h>
#endif

#include "definitions.h"

extern "C"
{
	/**
	 * @brief kernel function to run on FPGA
	 *
	 * @param env input env variables
	 * @param out output final kprime, kcross, r2, coeff
	 * @param iter_out  output number of iteration of EGM function
	 *
	void runOncpu(
		env_t *env,
		out_t *out,
		int *iter_out);
}
*/