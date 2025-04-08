#include "sw.h"

extern "C"
{

	/**
	 * First-time setup as separate top-level function
	 */
	void top_init(real *V_in, real st_V[NSTATES])
	{
		// SIMPLE
		for (int i = 0; i < NSTATES; ++i)
			st_V[i] = V_in[i];
		return;
	}

	void runOncpu(
		env_t *env,
		out_t *out,
		int *hw_iter)
	{
		// Local variables
		real st_V[NSTATES];
		small_idx_t st_Gk[NSTATES];
		
		// Copy data global memory to local memory
		top_init(env->V, st_V);

		// Estimation Loop
		int curr_egm_iter= 0;	  ///< number of egm iterations in each egm call
		sw_vfi(st_V,st_Gk, env, curr_egm_iter);

		// Report Results back
		for (int i = 0; i < NSTATES; i++)
		{ // main_5
			out->V[i] = st_V[i];
			out->Gk[i] = st_Gk[i];
		}	
		
		hw_iter[0] = curr_egm_iter;	

		return;
	}

	/**
	 * EGM:
	 *	Consumes:
	 *		kmprime[]: in order
	 *	Updates:
	 *		kprimes[]
	 */
	void sw_vfi(real *st_V, small_idx_t *st_Gk,env_t *env, int &hw_iter)
	{
		real metric = 1;
		while (metric > (real)TOLL_V)
		{ 	// egm_1
			hw_iter++;
			
			real spread_scalar = VERY_SMALL_POSITIVE_SCALAR;
			for (small_idx_t is = 0; is < NSTATES; ++is)
			{ // egm_2

				small_idx_t ik = is;
				real wealth = env->wealth[is];

				// Grid Search
				real obj_func_star = VERY_NEGATIVE_SCALAR;
            	small_idx_t ikpstar  = 0;
				for(small_idx_t ikp=0;ikp<NKGRID;ikp++){

					// Compute objective function for (k,k')
                	real consumption = wealth - env->k[ikp];   // c = w(k) - k'
                	real ret_func = env__one_over_one_minus_gamma * (pow(consumption,env__one_minus_gamma)-1.);  //(c^(1-sigma)-1)/(1-sigma) = (wealth - k')^(1-sigma)/(1-sigma)  (c>0)
					
                	// Continuation Value V(k')
                	real cont_value = env__beta * st_V[ikp];
                
                	// Objective Function (k,k')
                	real obj_func = ret_func + cont_value;
                
                	if(consumption < 0)
                    	obj_func = VERY_NEGATIVE_SCALAR;
                
                	if(obj_func>obj_func_star)
                	{
                    	obj_func_star = obj_func;
                    	ikpstar = ikp;
                	}
                
            	} // ikp control variable

				// Update the Metric
            	real spread = fabs(obj_func_star - st_V[is]);
				if (spread > spread_scalar)
					spread_scalar = spread;

				// Store Maximizers
            	st_V[is]  = obj_func_star;
            	st_Gk[ik] = ikpstar;
			}

			// ~ Update metric
			metric = spread_scalar;
			if (hw_iter % 100 == 0)
				printf("Iteration dV: %d metric %18.15lf\n", hw_iter, metric);
		}
		printf("Iteration dV: %d metric %18.15lf\n", hw_iter, metric);
	}

}
