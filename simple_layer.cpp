#include    "simple_layer.h"


namespace nn {
    SimpleLayer::SimpleLayer(int i_in, int i_out) : d_neuronsCount(i_out) {
        d_w1 = arma::randn<Matrix>(i_out, i_in);
    }
    SimpleLayer::SimpleLayer(int i_neurosCount) : d_neuronsCount(i_neurosCount)
        {}
    Column    SimpleLayer::operator()(const Column& i_x) {
        return d_w1*i_x;
    }

    bool    SimpleLayer::fit (const Data& i_inp, int i_iterations ) {
        if(!d_w1.empty()) return true;
        
        try {
            if (i_inp.empty()) throw std::runtime_error("input data is empty");
            d_w1 = arma::randn<Matrix>(d_neuronsCount, i_inp[0].n_elem);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
        return true;
    }
}