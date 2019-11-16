#include    "pca_reducer.h"
#include    "global_functions.h"


namespace nn {
  

    Column    PcaReducer::operator()(const Column& i_x) {
        return d_w.empty() ? i_x : d_w*i_x;
    }

    bool    PcaReducer::fit(const Data& i_inp, int i_iterations) {
        try {
            Matrix    covMat = fn::getCovMat(i_inp);
            double      criterion = arma::trace(covMat) / covMat.n_elem;

            d_w = fn::pcaReduce(covMat, criterion).t();
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