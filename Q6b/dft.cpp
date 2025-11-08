#include<math.h>
#include "dft.h"
#include"coefficients1024.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE],DTYPE real_op[SIZE],DTYPE imag_op[SIZE])	//Use pointers while doing the demo for streaming//
  {
//Write your code here
  int k;
  DTYPE temp_real[SIZE];
  DTYPE temp_imag[SIZE];

  for(int i=0; i<SIZE; i++){
    for(int j=0; j<SIZE; j++){

      k = (i*j)%SIZE;
      DTYPE c = cos_coefficients_table[k];
      DTYPE s = sin_coefficients_table[k];

      real_op[i] += real_sample[j] * c - imag_sample[j] * s;
      imag_op[i] += real_sample[j] * s + imag_sample[j] * c;
    }
  }
}

