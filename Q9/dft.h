#include <ap_fixed.h>
#include <hls_stream.h>

typedef  ap_fixed<45,20> DTYPE;
#define SIZE 1024 		/* SIZE OF DFT */

void dft(hls::stream<DTYPE> &in_r,
                hls::stream<DTYPE> &in_i,
                hls::stream<DTYPE> &out_r,
                hls::stream<DTYPE> &out_i);
