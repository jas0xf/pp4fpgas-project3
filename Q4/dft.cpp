#include<math.h>
#include "dft.h"
#include"coefficients32_2D.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE])
{
//Write your code here
  
  #pragma HLS array_partition variable=real_sample block factor=32 dim=1
  #pragma HLS array_partition variable=imag_sample block factor=32 dim=1
  #pragma HLS array_partition variable=real_out block factor=32 dim=1
  #pragma HLS array_partition variable=imag_out block factor=32 dim=1
  #pragma HLS array_partition variable=cos_coeff_table block factor=32 dim=2
  #pragma HLS array_partition variable=sin_coeff_table block factor=32 dim=2

  for(int i=0; i<SIZE; i++){
    #pragma HLS pipeline II=1

    real_out[i] = 0;
    imag_out[i] = 0;
    
    float c,s;
    for(int j=0; j<SIZE; j++){
      #pragma HLS pipeline II=1

      c = cos_coeff_table[i][j];
      s = sin_coeff_table[i][j];

      real_out[i] += real_sample[j] * c - imag_sample[j] * s;
      imag_out[i] += real_sample[j] * s + imag_sample[j] * c;
    }
  }
}
