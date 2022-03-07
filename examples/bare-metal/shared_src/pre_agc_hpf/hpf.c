// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#include "hpf.h"

// Q30 coefficients for the 100 Hz high pass filter
const int32_t hpf_coef[10] = {
    1020035168, -2040070348, 1020035168, 2070720224, -998576072,
    1073741824, -2147483648, 1073741824, 2114066120, -1041955416
};

void pre_agc_hpf(xs3_biquad_filter_s32_t * filter, int32_t data[240]){
    int i = 0, j = 0;
    for(int v = 0; v < 10; v++){
        if(i == 5){i = 0; j++;}
        filter->coef[i][j] = hpf_coef[v];
        i++;
    }
    for(int v = 0; v < 240; v++) {
        // changing format to Q30 to match the coeficients
        data[v] >>= 1;
        data[v] = xs3_filter_biquad_s32(&filter, data[v]);
        // the output will be normalised to Q31 format
    }
}