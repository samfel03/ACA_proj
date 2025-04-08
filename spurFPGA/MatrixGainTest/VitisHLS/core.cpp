#include <hls_stream.h>
#include <ap_axi_sdata.h>

// Declare 32-bit integer with side-channel (Includes TLAST signal)
typedef ap_axis<32,2,5,6> intSdCh;

void doGain(hls::stream<intSdCh> &inStream, hls::stream<intSdCh> &outStream, int gain) {
#pragma HLS INTERFACE axis port=outStream
#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE s_axilite port=gain bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

	// Indicate size of stream
	for (int idx = 0; idx < 1000; idx++) {
#pragma HLS PIPELINE

		// Read and cache
		intSdCh valIn = inStream.read();
		intSdCh valOut;

		// Calculate
		valOut.data = valIn.data * gain;

		// Copy side channel variables to the output
		valOut.keep = valIn.keep;
		valOut.strb = valIn.strb;
		valOut.user = valIn.user;
		valOut.last = valIn.last;
		valOut.id = valIn.id;
		valOut.dest = valIn.dest;

		// Send through stream
		outStream.write(valOut);
	}
}
