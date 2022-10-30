#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <iostream>
#include <ap_int.h>
#include <random>
#include "hls_stream.h"
#include "ap_axi_sdata.h"

const uint32_t W_USR = 32;
typedef hls::axis< uint32_t, W_USR, 0, 0> my_axis;

struct internal_st{
    uint32_t       data;
    ap_uint<W_USR> user;
    bool           last;
};

void top_func(
    hls::stream<my_axis>& in_a, 
    hls::stream<my_axis>& in_b , 
    hls::stream<my_axis>& in_c , 
    hls::stream<my_axis>& out_res  
);

#endif // SAMPLE_HPP