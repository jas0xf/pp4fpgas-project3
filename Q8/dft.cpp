#include<math.h>
#include "dft.h"
#include"coefficients1024.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE],DTYPE real_op[SIZE],DTYPE imag_op[SIZE])	//Use pointers while doing the demo for streaming//
  {
//Write your code here

  #pragma HLS array_partition variable=real_sample cyclic dim=1 factor=5
  #pragma HLS array_partition variable=imag_sample cyclic dim=1 factor=5
  #pragma HLS array_partition variable=real_op cyclic dim=1 factor=5
  #pragma HLS array_partition variable=imag_op cyclic dim=1 factor=5
  #pragma HLS array_partition variable=cos_coefficients_table cyclic dim=1 factor=5
  #pragma HLS array_partition variable=sin_coefficients_table cyclic dim=1 factor=5

  int k;
  for(int j=0; j<SIZE; j++){
    for(int i=0; i<SIZE; i++){
      #pragma HLS pipeline II=1
      #pragma HLS unroll factor=5
      k = (i*j) & (SIZE-1);;
      DTYPE c = cos_coefficients_table[k];
      DTYPE s = sin_coefficients_table[k];

      real_op[i] += real_sample[j] * c - imag_sample[j] * s;
      imag_op[i] += real_sample[j] * s + imag_sample[j] * c;
    }
  }
}

