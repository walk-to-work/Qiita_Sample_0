#include "sample.hpp"

int main(){

    hls::stream<my_axis> in_a, in_b, in_c, out_exp_res, out_act_res;
    
    std::mt19937 engine(0);
    const uint32_t TEST_SIZE = 1024;
    const uint32_t RAND_LIM  = 10000;

    for( uint32_t i = 0 ; i < TEST_SIZE ; ++i ){

        my_axis a,b,c,res;

        a.data = engine() % RAND_LIM ;
        b.data = engine() % RAND_LIM ;
        c.data = engine() % RAND_LIM ;

        a.user = i;
        b.user = i + 1000;
        c.user = i + 2000;

        a.last = (i == TEST_SIZE - 1) ? 1 : 0;

        in_a.write(a);
        in_b.write(b);
        in_c.write(c);

        res.data = a.data + b.data - c.data;
        res.last = a.last;

        out_exp_res.write( res );
    }

    for( int i = 0 ; i < TEST_SIZE ; ++i ){
        top_func( in_a, in_b, in_c, out_act_res );
    }

    for( int i = 0 ; i < TEST_SIZE ; ++i ) {
        my_axis act_res, exp_res;
        out_act_res.read( act_res );
        out_exp_res.read( exp_res );

        if( act_res.data != exp_res.data ) {
            printf("result is not same\n");
            return 1;
        }

        if( act_res.last != exp_res.last ) {
            printf("TLAST timing is not same\n");
            printf("TEST FAILED\n");
            return 1;
        }

        if( act_res.last == 1 )
            printf("TLAST is detected at %d\n" , i );
    }

    printf("TEST PASSED\n");

    return 0;
}