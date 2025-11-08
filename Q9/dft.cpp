#include "dft.h"
#include "coefficients1024.h"


void dft(hls::stream<DTYPE> &in_r,
                hls::stream<DTYPE> &in_i,
                hls::stream<DTYPE> &out_r,
                hls::stream<DTYPE> &out_i)
{
  #pragma HLS interface axis     port=in_r
  #pragma HLS interface axis     port=in_i
  #pragma HLS interface axis     port=out_r
  #pragma HLS interface axis     port=out_i
  #pragma HLS interface s_axilite port=return bundle=CTRL

  static DTYPE acc_r[SIZE], acc_i[SIZE];
  #pragma HLS bind_storage variable=acc_r type=ram_1p impl=bram
  #pragma HLS bind_storage variable=acc_i type=ram_1p impl=bram

  for (int i = 0; i < SIZE; ++i) {
    acc_r[i] = 0; acc_i[i] = 0;
  }

  for (int j = 0; j < SIZE; ++j) {
    DTYPE xr = in_r.read();
    DTYPE xi = in_i.read();

    for (int i = 0; i < SIZE; ++i) {
      int k = (i * j) & (SIZE - 1);
      DTYPE c =  cos_coefficients_table[k];
      DTYPE s =  sin_coefficients_table[k];

      acc_r[i] += xr * c - xi * s;
      acc_i[i] += xr * s + xi * c;
    }
  }

  for (int i = 0; i < SIZE; ++i) {
    out_r.write(acc_r[i]);
    out_i.write(acc_i[i]);
  }
}

