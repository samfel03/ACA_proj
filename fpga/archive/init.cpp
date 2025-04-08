#include "init.h"
#include "definitions.h"

// put constants in the bitstream? maybe declare as static
// initialization memory arrays (Hans has some experience)
// fpga rand generation distr check how they're doing this currently
// Imperial black shoals
// Rewrite packed file
// Probably use OCM
// Probably run it very fast on the ARM core (see if we can just use seed)
// Many of these are just LFSR

void linear_space(const real xmin,
				  const real xmax,
				  const int ngrid,
				  real *grid)
{
	real increment;
	increment = (real) ((xmax) - (xmin)) / (ngrid - 1);
	for (int i = 0; i < ngrid; ++i)
		grid[i] = (xmin) + i * increment;
	return;
}

void init_environment(env_t *env)
{
	/*
	env->beta = 0.99;
	env->gamma = 1;
	env->alpha = 0.36;
	env->delta = 0.025;
	env->delta_a = 0.01;
	env->mu = 0.15;
	env->l_bar = 1 / 0.9;

	env->l_bar_inv = 0.9;
	env->gamma_inv = 1;
	env->gamma_neg = -1;
	env->gamma_neg_inv = -1;

	env->epsilon_u = 0;
	env->epsilon_e = 1;

	env->ur[0] = 0.1;
	env->er[0] = (1 - env->ur[0]);
	env->ur[1] = 0.04;
	env->er[1] = (1 - env->ur[1]);

	env->er_inv[0] = 1/env->er[0];
	env->er_inv[1] = 1/env->er[1];

	env->kss = pow((1./env->beta-(1.-env->delta))/env->alpha,1./(env->alpha-1)); 
	*/
	return;
}

void init_transition(env_t *env)
{
	/*
	env->P[IXP(0, 0, 0, 0)] = 0.525;
	env->P[IXP(0, 0, 0, 1)] = 0.35;
	env->P[IXP(0, 0, 1, 0)] = 0.03125;
	env->P[IXP(0, 0, 1, 1)] = 0.09375;
	env->P[IXP(0, 1, 0, 0)] = 0.038889;
	env->P[IXP(0, 1, 0, 1)] = 0.836111;
	env->P[IXP(0, 1, 1, 0)] = 0.002083;
	env->P[IXP(0, 1, 1, 1)] = 0.122917;
	env->P[IXP(1, 0, 0, 0)] = 0.09375;
	env->P[IXP(1, 0, 0, 1)] = 0.03125;
	env->P[IXP(1, 0, 1, 0)] = 0.291667;
	env->P[IXP(1, 0, 1, 1)] = 0.583333;
	env->P[IXP(1, 1, 0, 0)] = 0.009115;
	env->P[IXP(1, 1, 0, 1)] = 0.115885;
	env->P[IXP(1, 1, 1, 0)] = 0.024306;
	env->P[IXP(1, 1, 1, 1)] = 0.850694;
	*/
}

void init_prealloc(env_t *env)
{
	for(int is = 0; is < NSTATES; is++){
		small_idx_t ik =is;
		env->wealth[is] = pow(env->k[ik],env__alpha)+(1. - env__delta)*env->k[ik];
		env->V[is] = env->wealth[is];
	}
}

void init_grids(env_t *env)
{

	// Individual Capital Holding Grid
	real *x = (real *) malloc(NKGRID*sizeof(real));
	real *y = (real *) malloc(NKGRID*sizeof(real));

	real xmin = 0;
	real xmax = 0.5;

	linear_space(xmin, xmax, NKGRID, x);
	for(int i=0;i<NKGRID;i++) {
		y[i] = pow(x[i],power_polynomial_KGRID)/pow(x[NKGRID-1],power_polynomial_KGRID);
		env->k[i] = KMIN+(KMAX-KMIN)*y[i];
		// env->k_egm[i] = env->k[i];
	}

	// Aggregate Capital Holding
	//linear_space(KM_MIN, KM_MAX, NKM_GRID,env->km);
	
	free(x);
	free(y);
	return;
}

void init_post (env_t *env)
{
	/*
	for (int i = 0; i < NKM_GRID; ++i)
		env->log_env_km[i] = log(env->km[i]);
	for (int i = 0; i < NSTATES_AG; ++i)
		env->irate_factor[i] = env->alpha * env->ag[i];
	for (int i = 0; i < NSTATES_AG; ++i)
		env->wage_factor[i] = (1. - env->alpha) * env->ag[i];

	int cidx = 0;
	for (int i = 0; i < NSTATES_AG; ++i)
		for (int j = 0; j < NSTATES_ID; ++j)
			env->cons2_factor[cidx++] = ((1.-env->trate[i]) 
										* env->epsilon[j]
										* env->l_bar
										+ (1. - env->epsilon[j])
										* env->mu);
	*/
}

void init_all(env_t *env, input_t *in)
{
	// @@ todo distinguish size in array nelem from bytes
	
	init_environment(env);

	init_transition(env);

	init_grids(env);

	init_prealloc(env);

	init_post(env);

	return;
}

void free_all(input_t *in)
{
	return;
}
