#include<math.h>
#include "dft.h"
#include"coefficients32_2D.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE])
{
//Write your code here

  for(int i=0; i<SIZE; i++){
    real_out[i] = 0;
    imag_out[i] = 0;
    
    float c,s;
    for(int j=0; j<SIZE; j++){
      c = cos_coeff_table[i][j];
      s = sin_coeff_table[i][j];

      real_out[i] += real_sample[j] * c - imag_sample[j] * s;
      imag_out[i] += real_sample[j] * s + imag_sample[j] * c;
    }
  }
}
