#include    "simple_layer.h"


namespace nn {
    SimpleLayer::SimpleLayer(int i_in, int i_out) {
        d_w1 = arma::randn<Matrix_t>(i_out, i_in);
    }

    Column_t    SimpleLayer::operator()(const Column_t& i_x) {
        return d_w1*i_x;
    }
}