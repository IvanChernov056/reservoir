#include    "simple_input.h"


namespace nn {
    SimpleInput::SimpleInput(int i_in, int i_out) {
        d_w1 = arma::randn<Matrix_t>(i_in, i_out);
    }

    Column_t    SimpleInput::operator()(const Column_t& i_x) {
        return d_w1*i_x;
    }
}