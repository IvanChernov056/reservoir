#include    "pca_reducer.h"


namespace nn {
    namespace {
        static Matrix    formMatrix (const Data& i_inp, bool i_withOnes = false) {
            int T = i_inp.size();
            int N = i_inp[0].n_elem;

            Matrix    S(N, T);
            for (int t = 0; t < T; t++) 
                S.col(t) = i_inp[t];
            
            if (i_withOnes) {
                Row   ones = arma::ones<Row>(T);
                return  arma::join_cols (S, ones);
            } 
            return S;
        }
    }

    Column    PcaReducer::operator()(const Column& i_x) {
        return d_w.empty() ? i_x : d_w*i_x;
    }

    bool    PcaReducer::fit(const Data& i_inp, int i_iterations) {
        try {
            Matrix    X = formMatrix(i_inp);
            Column    mean(X.n_rows, arma::fill::zeros);
            X.each_col([&mean](const auto& v){mean += v;});
            mean /= (double)X.n_cols;
            X.each_col([&mean](Column& v){v -= mean;});
            Matrix    covMat = X*X.t();
            double      criterion = arma::trace(covMat) / covMat.n_elem;


            Matrix    eigVec;
            Column    eigVal;
            arma::eig_sym(eigVal, eigVec, covMat);

            Data      condidates;
            for (int i = 0; i < eigVal.n_elem; ++i) {
                if(eigVal[i] > criterion)
                    condidates.push_back((Column)eigVec[i]);
            }
            
            d_w = formMatrix(condidates).t();
            d_d = d_w.n_rows;
            std::cout << "pca reducer reduce inpSize : " << i_inp[0].n_elem 
                    << " to : " << d_d << '\n';
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }


        return true;
    }
}