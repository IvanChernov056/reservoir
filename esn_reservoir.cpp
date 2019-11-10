#include    "esn_reservoir.h"

namespace nn {
    ESNReservoir::ESNReservoir (int i_nr, double i_radius, double i_sp, Activation_t i_f) : 
        d_f(i_f) 
    {
        d_wr = arma::sprandn(i_nr, i_nr, i_sp);
        double norm = arma::norm(d_wr);
        if (norm > 0) d_wr *= i_radius/norm;
        d_state = arma::zeros<Column_t>(i_nr);
        d_b = arma::randn<Column_t>(i_nr);
    }

    Column_t ESNReservoir::operator()(const Column_t& i_x) {
        d_state = d_wr*d_state + i_x + d_b;
        return d_state.for_each(d_f);
    }

    bool    ESNReservoir::fit(const Data_t& i_inp, int iterations) {
        return !d_wr.empty();
    }
}