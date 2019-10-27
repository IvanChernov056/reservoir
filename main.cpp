#include    "som_input.h"
#include    "esn_reservoir.h"
#include    "timer.h"
#include    "ridge_readout.h"
#include    <iostream>



int main (int argc, char* argv[]) {


    int         ni = 1, nd = 40, nr = 50, T = 1000;
    nn::RidgeReadout    rd (nd, nr, 0.03);

    Data_t  inp;
    Data_t  out;
    for (int t = 0; t < T; ++t) {
        inp.push_back(arma::randn<Column_t>(nd));
        out.push_back(arma::randn<Column_t>(nr));
    }

    Data_t  pred;
    if (rd.fit(inp, out))
        pred = rd.predict(inp);
    
    std::cout << ((pred.empty()) ? "all is bad\n" : "good\n");

    return 0;
}