#include    "esn_reservoir.h"

namespace nn {
    ESNReservoir::ESNReservoir (int i_nr, double i_radius, double i_sp, Activation i_f) : 
        d_f(i_f) 
    {
        d_wr = arma::sprandn(i_nr, i_nr, i_sp);
        double norm = arma::norm(d_wr);
        if (norm > 0) d_wr *= i_radius/norm;
        d_state = arma::zeros<Column>(i_nr);
        d_b = arma::randn<Column>(i_nr);
    }

    Column ESNReservoir::operator()(const Column& i_x) {
        d_state = d_wr*d_state + i_x + d_b;
        return d_state.for_each(d_f);
    }

    bool    ESNReservoir::fit(const Data& i_inp, int iterations) {
        return !d_wr.empty();
    }
}