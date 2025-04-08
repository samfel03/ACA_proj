#include <hls_stream.h>
#include <ap_axi_sdata.h>

int add(int a, int b) {

#pragma HLS INTERFACE s_axilite port=return bundle=CRTLS
#pragma HLS INTERFACE s_axilite port=a bundle=CRTLS
#pragma HLS INTERFACE s_axilite port=b bundle=CRTLS

	return a + b;
}
