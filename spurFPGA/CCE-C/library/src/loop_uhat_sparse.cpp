typedef double real;
#define NPOSLAND 17048
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <math.h>
#include "C:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include/initializations.h"
using namespace hls;

struct sparseInput {
    int rowStart[NPOSLAND];
    int colIndex[NPOSLAND];
    real value[NPOSLAND];
    real L[NPOSLAND];
    real R[NPOSLAND];
};


typedef struct {
    real uhat_i[NPOSLAND];
} uhatOutput;

// ap_axis arguments: <data, user, id, dest>
typedef ap_axis<64, 0, 0, 0> dataIn_t;
typedef ap_axis<64, 0, 0, 0> dataOut_t;
typedef hls::stream<dataIn_t> inStream;
typedef hls::stream<dataOut_t> outStream;

//void loop_uhat_sparse(int *rowStart, int *colIndex, real *value, int ELEMENTS, real tol, real *L, real L_exp, real *uhat_i, real *R, real R_exp)


void loop_uhat_sparse(inStream& inStream, outStream& outStream, int ELEMENTS, real tol, real L_exp, real R_exp)
{


//////////////////////////PRAGMAS///////////////////////////////


#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE axis port=outStream
#pragma HLS INTERFACE mode=s_axilite port=R_exp bundle=CTRL_BUS
#pragma HLS INTERFACE mode=s_axilite port=L_exp bundle=CTRL_BUS
#pragma HLS INTERFACE mode=s_axilite port=tol bundle=CTRL_BUS
#pragma HLS INTERFACE mode=s_axilite port=ELEMENTS bundle=CTRL_BUS
#pragma HLS INTERFACE mode=s_axilite port=return bundle=CTRL_BUS


////////////////////////////////////////////////////////////////


    sparseInput input_data;
    uhatOutput output_data;
    real integral[NPOSLAND];
    real error = tol + 1.0;
    int iter = 0;

    // Read struct variables from AXI Stream
    for (int i = 0; i < NPOSLAND; ++i) {
        dataIn_t data_in = inStream.read();
        input_data.rowStart[i] = data_in.data;
        input_data.colIndex[i] = inStream.read().data;
        input_data.value[i] = inStream.read().data;
        input_data.L[i] = inStream.read().data;
        input_data.R[i] = inStream.read().data;
    }

    while (error >= tol)
    {
        // Compute accuracy and update the guess

        for (int i = 0; i < NPOSLAND; i++)
            integral[i] = input_data.R[i] * pow(output_data.uhat_i[i], R_exp);
        error = 0;

        for (int i = 0; i < NPOSLAND; i++)
        {
            int e_max;
            if(i<NPOSLAND-1)
                e_max=input_data.rowStart[i+1];
            else
                e_max=ELEMENTS;
            real rhs = 0.0;

            for (int e = input_data.rowStart[i]; e < e_max; e++){
                rhs += input_data.value[e] * integral[input_data.colIndex[e]];
            }

            real uhat_f = input_data.L[i] * pow(rhs, L_exp);
            real deviation = (output_data.uhat_i[i] - uhat_f);
            error += deviation * deviation;
            // Update the Guess
            output_data.uhat_i[i] = uhat_f;
        }
        iter = iter + 1;
    }

    for (int i = 0; i < NPOSLAND; ++i) {
        dataOut_t data_out;
        data_out.data = output_data.uhat_i[i];
        outStream.write(data_out);
    }
    
}
