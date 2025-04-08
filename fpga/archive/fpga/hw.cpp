#include "hw.h"
#ifndef __SYNTHESIS__
#define PRINT_LOOP_CNT 1
#endif

extern "C"
{
	/** Static on-PL memories */
	static hw_env_t st_env;

	/**
	 * First-time setup as separate top-level function
	 * Copy objects from Global to Local Memory (BRAM/URAM)
	 */
	void hw_top_init(real *V_in, real st_V[NUM_KPRIMES][NSTATES],
	                real *k_in, real st_k[NKGRID],
					real *wealth_in,real st_wealth[NSTATES]){
		init_1:
		for (int i = 0; i < NSTATES; ++i){
			real V_scalar = V_in[i];
			real w_scalar = wealth_in[i];
			for (int k = 0; k < NUM_KPRIMES; ++k){
				st_V[k][i] = V_scalar;
				st_wealth[i] = w_scalar;
			}
		}
		init_2:
		for (int i = 0; i < NKGRID; ++i)
			st_k[i] = k_in[i];
		return;
	}

	void runOnfpga(
		preinit_t *preinit,
		out_t *out,
		int *hw_iter)
	{
		// Bundle all ports and call the bundle gmem0
		#pragma HLS INTERFACE m_axi port=preinit offset=slave bundle=gmem0
		#pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0
		#pragma HLS INTERFACE m_axi port=hw_iter offset=slave bundle=gmem0

		// Local variables
		real st_k[NKGRID];
		real st_wealth[NSTATES];
		real st_V[NUM_KPRIMES][NSTATES];//real st_V[NUM_KPRIMES][NSTATES];
		small_idx_t st_Gk[NUM_KPRIMES][NSTATES]; // consider increasing this
		//#pragma HLS bind_storage variable = idshock type = RAM_1P impl = URAM
		//#pragma HLS array_partition variable = kmprime complete
		
		// Copy data global memory to on-chip memory (BRAM, URAM) - burst transfer
		hw_top_init(preinit->V, st_V,preinit->k,st_k,preinit->wealth,st_wealth);

		// Estimation Loop
		int ihp_iter= 0;	  ///< number of egm iterations in each egm call
		//int hw_ihp_iter[300] = {0}; // local mem array to store the number of ihp iterations

		hw_vfi(st_V,st_wealth,st_Gk,st_k,ihp_iter);

		// Report Results back: burst transfer from on-chip memory to global memory
		out_1:
		for (int i = 0; i < NSTATES; i++)
		{ 
			out->V[i] = st_V[0][i];
		}
		out_2:
		for (int i = 0; i < NSTATES; i++)
		{ 
			out->Gk[i] = st_Gk[0][i];
		}
			
		hw_iter[0] = ihp_iter;

		return;
	}

	void hw_vfi(real st_V[NUM_KPRIMES][NSTATES],
				real st_wealth[NSTATES],
				small_idx_t st_Gk[NUM_KPRIMES][NSTATES],
				real st_k[NKGRID],
				int &ihp_iter){

		#pragma HLS array_partition variable = st_wealth factor = 8 type = cyclic
		#pragma HLS array_partition variable = st_k complete dim = 1
		#pragma HLS array_partition variable = st_V complete dim = 1			
		#pragma HLS array_partition variable = st_Gk complete dim = 1		
		// What type of RAM
		#pragma HLS bind_storage variable = st_V type = RAM_1WNR impl = BRAM	
		#pragma HLS bind_storage variable = st_wealth type = RAM_1WNR impl = BRAM
		#pragma HLS bind_storage variable = st_Gk type = RAM_1WNR impl = BRAM	
		// question on rAM: #pragma HLS bind_storage variable = st_kcross type = RAM_S2P impl = BRAM


		real metric = 1;
		while (metric > (real)TOLL_V)
		{ 	// egm_1
			ihp_iter++;
			
			real spread_scalar = VERY_SMALL_POSITIVE_SCALAR;

			main_1:
			for (small_idx_t is = 0; is < NSTATES; ++is)
			{ 	
				#pragma HLS loop_tripcount min = 8 avg = 8 max = 8
				// egm_2
				#pragma HLS unroll
				
				small_idx_t ik = is;

				real wealth = st_wealth[is];
				small_idx_t ikpstar  = 0;
				real obj_func_star = VERY_NEGATIVE_SCALAR;
				main_2:
				for(small_idx_t ikp=0;ikp<NKGRID;ikp++){
					#pragma HLS pipeline
					// Compute return function for (k,k')
                	real consumption = wealth - st_k[ikp];   // c = w(k) - k'
					real pow_ret_func_aux = hw_pow(consumption,env__one_minus_gamma);
					real pow_ret_func = pow_ret_func_aux-1.;
                	real ret_func = env__one_over_one_minus_gamma * pow_ret_func;  //(c^(1-sigma)-1)/(1-sigma) = (wealth - k')^(1-sigma)/(1-sigma)  (c>0)
					
                	// Continuation Value V(k')
                	real cont_value = env__beta * st_V[0][ikp];
                
                	// Objective Function (k,k')
                	real obj_func_scalar = ret_func + cont_value;
                	obj_func_scalar = (consumption >= 0) ? obj_func_scalar: VERY_NEGATIVE_SCALAR;
					bool select = obj_func_scalar>=obj_func_star;
					obj_func_star = (select)?obj_func_scalar:obj_func_star;
					ikpstar =  (select)?ikp:ikpstar;
				}


				// Update the Metric
				real spread = hw_fabs(obj_func_star - st_V[0][is]);
				if (spread > spread_scalar)
					spread_scalar = spread;
				// Store Maximizers
            	st_V[0][is]  = obj_func_star;
            	st_Gk[0][ik] = ikpstar;	
	
			}

			// ~ Update metric
			metric = spread_scalar;
#if PRINT_LOOP_CNT			
			if (ihp_iter % 100 == 0)
				printf("Iteration dV: %d metric %18.15lf\n", ihp_iter, metric);
#endif				
		}
					

	}


	real hw_exp(real b)
	{
#pragma HLS inline
#if USE_HLS_LIB
		return hls::exp(b);
#else
		return exp(b);
#endif
	}

	real hw_log(real b)
	{
#pragma HLS inline
#if USE_HLS_LIB
		return hls::log(b);
#else
		return log(b);
#endif
	}

	real hw_sqrt(real b)
	{
#pragma HLS inline
#if USE_HLS_LIB
		return hls::sqrt(b);
#else
		return sqrt(b);
#endif
	}

	real hw_fabs(real b)
	{
#pragma HLS inline
#if USE_HLS_LIB
		return hls::fabs(b);
#else
		return fabs(b);
#endif
	}

	real hw_pow(real x, real y)
	{
#pragma HLS inline
#if USE_HLS_LIB
		return hls::pow(x, y);
#else
		return pow(x, y);
#endif
	}

}



// Grid Search
				/*
				small_idx_t ikpstar  = NKGRID-1;
				real obj_func_star = obj_func[NKGRID-1];
				main_3:
				for(small_idx_t ikp=NKGRID-1;ikp>=0;ikp=ikp-4){
					#pragma HLS loop_tripcount min = 32 avg = 32 max = 32
					//#pragma HLS pipeline
					if(obj_func[ikp-0]>obj_func_star){
						obj_func_star = obj_func[ikp-0];
						ikpstar = ikp;
					}
					else if (obj_func[ikp-1]>obj_func_star){
						obj_func_star = obj_func[ikp-1];
						ikpstar = ikp-1;
					}
					else if (obj_func[ikp-2]>obj_func_star){
						obj_func_star = obj_func[ikp-2];
						ikpstar = ikp-2;
					}
					else{
						obj_func_star = obj_func[ikp-3];
						ikpstar = ikp-3;
					}

				}
				*/
				/*
				for(small_idx_t ikp=NKGRID-2;ikp>0;ikp--){
					#pragma HLS pipeline

					if(obj_func[ikp]>obj_func_star)
                	{
                    	obj_func_star = obj_func[ikp];
                    	ikpstar = ikp;
                	}
				}
				*/
				/*
				// Update the Metric
				real spread = hw_fabs(obj_func_star - st_V[0][is]);
				if (spread > spread_scalar)
					spread_scalar = spread;
				// Store Maximizers
            	st_V[0][is]  = obj_func_star;
            	st_Gk[0][ik] = ikpstar;
				*/
			/*
				real spread = 10;
				if (spread > spread_scalar)
					spread_scalar = spread;
				// Store Maximizers
            	st_V[0][is]  = obj_func[10];
            	st_Gk[0][ik] = 10;
			*/	

/*
	void grid_search(const real *obj_func,small_idx_t *ikpstar){

		js_1:
		for(small_idx_t ikp=NKGRID;ikp>0;ikp=ikp-32) //4 comparators
		{
			for(small_idx_t ikp_2=0;ikp_2<32;ikp_2++){

			}

			js_1_1:
			if (p <= src[i])
			{
				result_1 = i; //send the max idex
			}
		}
		js_2:
		for (signed short i = 4; i > 0; i--) // 4 comparators
		{
			js_2_2:
			if (p <= src[result_1])
			{
				result_2 = result_1; //send the max index
			}
			result_1 = result_1 - (small_idx_t)5;
		}

	fr100_5:
		for (signed short i = 5; i > 0; i--) //5 comparators
		{
		fr100_6:
			if (p <= src[result_2--])
			{
				result_3 = result_2; //send the min index
			}
		}
		return;
	}


	{
		int hMI[NKGRID*6];
		for(int s=0;s<6;s++)
        {
            int pow2s  = (int) pow(2,s);
            int Delta  = (int) NKGRID/pow(2,s+2);    // always integer (Denominator is power of two up to 16384)
            for (int i=0;i<4*pow2s;i++)
                hMI[s*NKGRID+i]   = i * Delta;
        }	

		// -------------------------- 15 BINARY STAGES ----------------------
		for(int s=0;s<14;s++)
		{
			// Formula (C.4)
			ik1 = MI[s*nk+hstar+1];
			ik2 = MI[s*nk+hstar+2];
			ik3 = MI[s*nk+hstar+3];
			
			// Expected Value
			Exp1 = 0.0;
			Exp2 = 0.0;
			Exp3 = 0.0;
			for(int l = 0 ; l < nz ; ++l){

				Exp1 += (*(P+l))*(*(V0+ik1*nz+l));
				Exp2 += (*(P+l))*(*(V0+ik2*nz+l));
				Exp3 += (*(P+l))*(*(V0+ik3*nz+l));
			}
			
			// Objective Function at three binary stage evaluation indexes
			w1 =(ik1<=khi)?(pow(ydepK-K[klo+ik1],1-eta)/(1-eta)+beta*Exp1):(-1.7977e+308);
			w2 =(ik2<=khi)?(pow(ydepK-K[klo+ik2],1-eta)/(1-eta)+beta*Exp2):(-1.7977e+308);
			w3 =(ik3<=khi)?(pow(ydepK-K[klo+ik3],1-eta)/(1-eta)+beta*Exp3):(-1.7977e+308);

			// Optimization
			int jstar;
					w = w1;ik = ik1;jstar = 0;
			if(w2>w) {w = w2;ik = ik2;jstar = 2;}
			if(w3>w) {w = w3;ik = ik3;jstar = 4;}
			// Handling Exceptions: MAPPING J TO JSTAR (Formula C.6)
			if((w3==w2) && (ik==ik2)) jstar = 3;
			if((w2==w1) && (ik==ik1)) jstar = 1;
			if((w3==w2) && (w3==w1))  jstar = 2;
			if((w3==w2) && (w3==w1) && (w3==-1.7977e+308))  jstar = 0;

			// Update of hstar (Formula C.5)
			hstar = 2*hstar + jstar;
		}

		// Last Stage 4 Index Comparison
		int s=14;
		ik0 = MI[s*nk+hstar+0];
		ik1 = MI[s*nk+hstar+1];
		ik2 = MI[s*nk+hstar+2];
		ik3 = MI[s*nk+hstar+3];

		// Expected Value
		Exp0 = 0.0;
		Exp1 = 0.0;
		Exp2 = 0.0;
		Exp3 = 0.0;
		for(int l = 0 ; l < nz ; ++l){
			Exp0 += (*(P+l))*(*(V0+ik0*nz+l));
			Exp1 += (*(P+l))*(*(V0+ik1*nz+l));
			Exp2 += (*(P+l))*(*(V0+ik2*nz+l));
			Exp3 += (*(P+l))*(*(V0+ik3*nz+l));
		}

		// Objective Function at four binary stage evaluation indexes
		w0 =(ik0<=khi)?(pow(ydepK-K[klo+ik0],1-eta)/(1-eta)+beta*Exp0):(-1.7977e+308);
		w1 =(ik1<=khi)?(pow(ydepK-K[klo+ik1],1-eta)/(1-eta)+beta*Exp1):(-1.7977e+308);
		w2 =(ik2<=khi)?(pow(ydepK-K[klo+ik2],1-eta)/(1-eta)+beta*Exp2):(-1.7977e+308);
		w3 =(ik3<=khi)?(pow(ydepK-K[klo+ik3],1-eta)/(1-eta)+beta*Exp3):(-1.7977e+308);

		// Optimization
				w = w0;ik = ik0;
		if(w1>w) {w = w1;ik = ik1;}
		if(w2>w) {w = w2;ik = ik2;}
		if(w3>w) {w = w3;ik = ik3;}
	}
*/
