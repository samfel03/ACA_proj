#include "hw.h"
#include "hls_stream.h"
#include <ap_int.h>
#include <ap_fixed.h>
#include "assert.h"

#ifndef __SYNTHESIS__
#define PRINTF 1
#endif
#define CHUNK_SIZE 17048
using namespace hls;

#define MUL_UNROLL_FACTOR 8

typedef double real_e; //TODO: check why fpga values are little different from cpu, sw_emu
// typedef ap_fixed<72, 16> real_e; //TODO: check what should be < >

void read_trmult(real *trmult_reduced, stream<real> &trmult_reduced_stream, int n) {
	for (int i = 0; i < CHUNK_SIZE; i++) {
		trmult_reduced_stream << trmult_reduced[n*CHUNK_SIZE + i];  // definition of the stream. We are not storing the trmult_reduced...just streaming it and send it to compute. you have to consume it.
	}
}

void compute(stream<real> &a_stream, real x_local[NPOSLAND], stream<real> &y_stream) {
	real_e y_tmp = 0;
    for (int j = 0; j < NPOSLAND; j+=MUL_UNROLL_FACTOR) {
        if (j == 0)
            y_tmp = 0;

        real_e a_l[MUL_UNROLL_FACTOR];
#pragma HLS array_partition variable = a_l complete

        // FIRST SPEEDUP: Increase width of the stream. Instead of 64bit (1 real), read more 512 (8 reals) -> 8x speedup
        // SECOND SPEEDUP: store trmult_reduced in PLRAMS + DDRs = 6/7 RAMS from which to stream: 6*8 speedup -> 48x speedup. 
        // THIRD SPEEDUP: 3 SLR but the sharey PLRAMS + DDRs. So evaluate.

        //TODO: Fix memory dependency by using hls::vectors to gain 8x speedup
        for (int k = 0; k < MUL_UNROLL_FACTOR; k++)
            a_l[k] = (real_e)a_stream.read();

        // Multiply accumulate may need fixed precision to do it in one clock cycle (unless we drop math safe)
        real_e y_tmp_l = 0;
        for (int k = 0; k < MUL_UNROLL_FACTOR; k++) {
#pragma HLS unroll 
            y_tmp_l += a_l[k]*(real_e)x_local[j+k];
        }

        y_tmp += y_tmp_l;

        if (j+MUL_UNROLL_FACTOR == NPOSLAND)
            y_stream << (real)y_tmp;
    }
// Simplest implementation: element by element
/*
	real_e y_tmp = 0;
	for (int j= 0; j< CHUNK_SIZE; j++){
		//make the imperfect loop as perfect loop
//		if(j==0)
//				y_tmp = 0;

		real_e a_l = (real_e)a_stream.read();
		y_tmp += a_l * (real_e)x_local[j];

		// if(j+1 == CHUNK_SIZE)
		// 	y_stream << (real)y_tmp;
	}
	y_stream << (real)y_tmp;
*/
}
// Write back to global memory
void write_rhs(stream<real> &y_stream, real *y, int n) {
//	real y_break = 0;
//	for (int i = 0; i < CHUNK_SIZE; i++) {
		real y_l = y_stream.read();
		y[n] = y_l;
//		y[i] = y_l;
//	}
}

void accel_mca(real *trmult_reduced, real l_integral[NPOSLAND], real *rhs){

	//split the trmult_reduced to NPOSLAND vectors of NPOSLAND elements each and perform Vector multiplication
    // for every row 
	for (int i=0; i<NPOSLAND; i++){
#pragma HLS DATAFLOW                // at every clock cycle one row
        stream<real> trmult_reduced_stream;
        stream<real> rhs_stream;
#pragma HLS STREAM variable= trmult_reduced_stream depth=17048          // stream row by row in a FIFO way from shared memory to BRAM
#pragma HLS STREAM variable= rhs_stream depth=1

        read_trmult(trmult_reduced, trmult_reduced_stream, i);              // i idnex of row
        compute(trmult_reduced_stream, l_integral, rhs_stream);
        write_rhs(rhs_stream, rhs, i);

	}
}



extern "C"
{

    // TODO: Write back more information for fpga (ex: error value of each iteration, 
    //       number of iterations similar to KS_FPGA). Currently only uhat is returned
    void runOnfpga(real tol, real *trmult_reduced, real *L, real L_exp,
                   real *uhat_i, real *R, real R_exp)
    /*
        input:
        - tol: level of tolerance, scalar, double
        - trmult_reduced: 17048x17048, double
        - L,R: 17048x1, double
        - L_exp,R_exp: scalar
        output:
        - uhat_i: 17048x1, real
     */
    {   
        //TODO: Split trmult_reduced across 3 DDR banks and 3 PLRAM 
        //      to launch 6 accel_mac simultaneously and gain 6x sppedup
		// Bundle all ports and call the bundle gmem0
//		#pragma HLS INTERFACE m_axi port=trmult_reduced offset=slave bundle=gmem0
//		#pragma HLS INTERFACE m_axi port=L offset=slave bundle=gmem0
//		#pragma HLS INTERFACE m_axi port=uhat_i offset=slave bundle=gmem0
//		#pragma HLS INTERFACE m_axi port=R offset=slave bundle=gmem0

        #ifdef PRINTF
            printf("hw Tol: %.16lf\n", tol);
            printf("hw R_exp: %.16lf\n", R_exp);
            printf("hw L_exp: %.16lf\n", L_exp);

            FILE *cfile;
            char FileName[512];
            printf("trmult\n");
            sprintf(FileName, "hw_trmult_reduced.txt");
            cfile = fopen(FileName, "w");
            for(int i=0; i<NPOSLAND; i++){
                fprintf(cfile, "%.15lf \n", trmult_reduced[i]);
            }
            fclose(cfile);

            printf("L\n");
            sprintf(FileName, "hw_L.txt");
            cfile = fopen(FileName, "w");
            for(int i=0; i<NPOSLAND; i++){
                fprintf(cfile, "%.15lf \n", L[i]);
            }
            fclose(cfile);

            printf("R\n");
            sprintf(FileName, "hw_R.txt");
            cfile = fopen(FileName, "w");
            for(int i=0; i<NPOSLAND; i++){
                fprintf(cfile, "%.15lf \n", L[i]);
            }
            fclose(cfile);
        #endif

    	// Local BRAM memory
        real error = tol + 1.;
        int iter = 0;

        //Additional local memory for speedup
        real l_uhat_i[NPOSLAND];

        //Burst copy uhat_i to l_uhat_i
        for (int i=0; i<NPOSLAND; i++)
        	l_uhat_i[i] = uhat_i[i];

        main_1:
        while (error >= tol)
        {
#pragma HLS LOOP_TRIPCOUNT min=77 max=100

        	// Local BRAM memory
            real l_integral[NPOSLAND];

            // Compute accuracy and update the guess
            main_2:
            if(iter == 0){
                for (int i = 0; i < NPOSLAND; i++){
        		l_integral[i] = R[i]; 
                }
            }
            else{
                for (int i = 0; i < NPOSLAND; i++){
                // assert(l_uhat_i[i]>0.0000001); 
                // development: power function may throw different numbers than in CPU. So, temporary fix
        		if(l_uhat_i[i] < 0.1){
                    l_integral[i] = R[i];
                }
                else{
                    l_integral[i] = R[i] * pow(l_uhat_i[i], R_exp); 
                }
                
                }
            }

        	// Matrix Vector multiply (trmult_reduced x l_integral = rhs)
        	real rhs[NPOSLAND];
			accel_mca(trmult_reduced, l_integral, rhs);

        	error = 0.;
			main_3:
			for (int i = 0; i < NPOSLAND; i++)
			{
                real uhat_f = L[i] * pow(rhs[i], L_exp);
                real deviation = (l_uhat_i[i] - uhat_f);
                error += deviation * deviation;
                // Update the Guess
                l_uhat_i[i] = uhat_f;
            }
            iter = iter + 1;

#ifdef PRINTF
            printf("%d\n", iter);
            printf("Error_%d : %.16lf\n", iter, error);
#endif
        } // end while

        //Burst copy l_uhat_i to uhat_i
        for (int i=0; i<NPOSLAND; i++)
        	uhat_i[i] = l_uhat_i[i];

#ifdef PRINTF
        printf("Error: %.16lf\n", error);
#endif
    }
}
