#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <hls_stream.h>          
#include "dft.h"               

struct Rmse
{
    int   num_sq;
    float sum_sq;
    float error;

    Rmse(){ num_sq = 0; sum_sq = 0; error = 0; }

    float add_value(float d_n)
    {
        num_sq++;
        sum_sq += (d_n*d_n);
        error = sqrtf(sum_sq / num_sq);
        return error;
    }
};

Rmse rmse_R, rmse_I;

int main()
{
    int   index;
    float gold_R, gold_I;

    // --- streams instead of arrays [CHANGED] ---
    hls::stream<DTYPE> in_r, in_i, out_r, out_i;

    FILE * fp = fopen("out.gold.dat","r");

    for (int i = 0; i < SIZE; i++)
    {
        in_r.write((DTYPE)i);
        in_i.write((DTYPE)0.0);
    }

    dft(in_r, in_i, out_r, out_i);

    for (int i = 0; i < SIZE; i++)
    {
        if (fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I) != 3) {
            fprintf(stderr, "ERROR: malformed golden at line %d\n", i+1);
            fclose(fp);
            return 3;
        }
        DTYPE R = out_r.read();
        DTYPE I = out_i.read();
        rmse_R.add_value((float)R - gold_R);
        rmse_I.add_value((float)I - gold_I);
    }
    fclose(fp);

    printf("----------------------------------------------\n");
    printf("   RMSE(R)           RMSE(I)\n");
    printf("%0.15f %0.15f\n", rmse_R.error, rmse_I.error);
    printf("----------------------------------------------\n");

    if (rmse_R.error > 0.1 || rmse_I.error > 0.1 ) {
        fprintf(stdout, "*******************************************\n");
        fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
        fprintf(stdout, "*******************************************\n");
        return 1;
    } else {
        fprintf(stdout, "*******************************************\n");
        fprintf(stdout, "PASS: The output matches the golden output!\n");
        fprintf(stdout, "*******************************************\n");
        return 0;
    }
}

