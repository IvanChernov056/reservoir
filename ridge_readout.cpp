#include    "ridge_readout.h"
#include    "global_functions.h"


namespace nn {

   
    RidgeReadout::RidgeReadout(int i_in, int i_out, double i_ridge) :
        d_w(i_out, i_in), d_b(i_out), d_neuronsCount(i_out), d_ridge(i_ridge) {}
    
    RidgeReadout::RidgeReadout(int i_out, double i_ridge) : 
        d_neuronsCount(i_out), d_ridge(i_ridge) {}

    Column    RidgeReadout::operator()(const Column& i_x) {
        return d_w*i_x + d_b;
    }

    bool    RidgeReadout::learn (const Data& i_inp, const Data& i_out, int iterations) {
        try{
            Matrix    X = fn::formMatrix(i_inp, true);
            Matrix    Y = fn::formMatrix(i_out, false);

            Matrix    W = Y*X.t()*arma::inv(X*X.t() + d_ridge*arma::eye(X.n_rows, X.n_rows));

            d_w = W.cols(0, i_inp[0].n_elem-1);
            d_b = W.col(i_inp[0].n_elem);
            std::cout << "something\n";
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            return false;
        }

        return true;
    }

    bool    RidgeReadout::fit (const Data& i_inp, int iterations) {
        if (!d_w.empty()) return true;

        try {
            if(i_inp.empty()) throw std::runtime_error("input data vector is empty");
            if(i_inp[0].empty()) throw std::runtime_error("data size is zero");

            int inpSize = i_inp[0].n_elem;
            d_w = Matrix(d_neuronsCount, inpSize);
            d_b = Column(d_neuronsCount);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
        return true;
    }
}