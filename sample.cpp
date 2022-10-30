#include "sample.hpp"

void add_st (
    hls::stream<my_axis>& in_a,
    hls::stream<my_axis>& in_b,
    hls::stream<internal_st>& out_res
){

    my_axis a, b;
    internal_st res;

    in_a.read(a);
    in_b.read(b);
    res.data = a.data + b.data;
    res.user = a.user;
    res.last = a.last;
    out_res.write( res );

}

void sub_st (
    hls::stream<internal_st>& in_a,
    hls::stream<my_axis>& in_b,
    hls::stream<my_axis>& out_res
){

    internal_st a;
    my_axis b, res;
    in_a.read(a);
    in_b.read(b);
    res.data = a.data - b.data;
    res.user = a.user;
    res.last = a.last;
    out_res.write( res );
}

void top_func(
    hls::stream<my_axis>& in_a, 
    hls::stream<my_axis>& in_b, 
    hls::stream<my_axis>& in_c, 
    hls::stream<my_axis>& out_res
){

    #pragma HLS INTERFACE axis port=in_a
    #pragma HLS INTERFACE axis port=in_b
    #pragma HLS INTERFACE axis port=in_c
    #pragma HLS INTERFACE axis port=out_res
    #pragma HLS DATAFLOW

    hls::stream<internal_st> a_plus_b_st;

    add_st( in_a , in_b , a_plus_b_st );
    sub_st( a_plus_b_st , in_c , out_res );
}