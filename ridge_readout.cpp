#include    "ridge_readout.h"

namespace nn {

    namespace {
        static Matrix_t    formMatrix (const Data_t& i_inp, bool i_withOnes = false) {
            int T = i_inp.size();
            int N = i_inp[0].n_elem;

            Matrix_t    S(N, T);
            for (int t = 0; t < T; t++) 
                S.col(t) = i_inp[t];
            
            if (i_withOnes) {
                Row_t   ones = arma::ones<Row_t>(T);
                return  arma::join_cols (S, ones);
            } 
            return S;
        }
    }

    RidgeReadout::RidgeReadout(int i_in, int i_out, double i_ridge) :
        d_ridge(i_ridge), d_w(i_out, i_in), d_b(i_out) {}

    Column_t    RidgeReadout::operator()(const Column_t& i_x) {
        return d_w*i_x + d_b;
    }

    bool    RidgeReadout::fit (const Data_t& i_inp, const Data_t& i_out, int iterations) {
        try{
            Matrix_t    X = formMatrix(i_inp, true);
            Matrix_t    Y = formMatrix(i_out, false);

            Matrix_t    W = Y*X.t()*arma::inv(X*X.t() + d_ridge*arma::eye(X.n_rows, X.n_rows));

            d_w = W.cols(0, i_inp[0].n_elem-1);
            d_b = W.col(i_inp[0].n_elem);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            return false;
        }

        return true;
    }
}