#include "init.h"
#include "definitions.h"

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
	env->beta = 0.99;

	return;
}

void init_shock(env_t *env)
{
	env->P[IXP(0, 0, 0, 0)] = 0.525;
	env->P[IXP(0, 0, 0, 1)] = 0.35;
}

void init_prealloc(env_t *env, vars_t *vars)
{
	for (int ia = 0; ia < NSTATES_AG; ++ia) {
		env->trate[ia] = env->mu * (1.-env->er[ia]) / (env->l_bar*env->er[ia]);
		real taxrate = env->trate[ia];

		for(int ikm=0;ikm<NKM_GRID;ikm++)
		{
			// Interest Rate
			real irate = env->alpha*(env->ag[ia]*pow(env->km[ikm]/env->er[ia]/env->l_bar,env->alpha-1));
			// Wage
			real wage  =(1.-env->alpha)*(env->ag[ia]*pow(env->km[ikm]/env->er[ia]/env->l_bar,env->alpha));

			for(int iid=0;iid<NSTATES_ID;iid++)
				for(int ik=0;ik<NKGRID;ik++)
				{
					env->wealth[IXV(ia, ikm, iid, ik)] = (irate + 1.-env->delta) * env->k[ik] +
					wage * ( (1.-taxrate)* env->epsilon[iid]*env->l_bar+
							(1.-env->epsilon[iid]) * env->mu
							);
					vars->kprime_a[IXV(ia, ikm, iid, ik)]=0.9*env->k[ik];
				}
		}
	}
}

void init_k(env_t *env, vars_t *vars)
{
	real *x = (real *) malloc(NKGRID*sizeof(real));
	real xmin = 0;
	real xmax = 0.5;

	linear_space(KM_MIN, KM_MAX, NKM_GRID,env->km);
	// linear_space(KM_MIN, KM_MAX, NKM_GRID,env->km_egm);
	for(int ja=0;ja<NSTATES_AG;ja++)
		for(int jkm=0;jkm<NKM_GRID;jkm++)
			for(int jid=0;jid<NSTATES_ID;jid++)
				for(int jk=0;jk<NKGRID;jk++)
					vars->kprime_a[IXV(ja,jkm,jid,jk)] = NKPRIME_SCALE*env->k[jk];
	
	free(x);
	return;
}

void init_all(env_t *env, input_t *in, vars_t *vars)
{
	// Load global variables from C/input
	init_environment(env);
	init_shock(env);
	init_k(env, vars);
	init_prealloc(env, vars);
	return;
}

void free_all(input_t *in)
{
	free(in->idshock);
	free(in->agshock);
	return;
}
