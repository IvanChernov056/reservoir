#include    "global_functions.h"


namespace nn {
    double  locRelfMSRE (const Column& i_inp1, const Column& i_inp2) {
        double  n1 = arma::norm(i_inp1);
        double  n2 = arma::norm(i_inp2);
        double  err = arma::norm(i_inp1 - i_inp2);
        return err / n1 > n2 ? n1 : n2;
    }

    double locMSE (const Column& i_inp1, const Column& i_inp2) {
        Column e = i_inp2 - i_inp1;
        double  err = 0;
        e.for_each([&err](double x){err += x*x;});
        return err/e.n_elem;
    }

    double locMSRE (const Column& i_inp1, const Column& i_inp2) {
        return sqrt(locMSE(i_inp1, i_inp2));
    }

    std::tuple<double, double, double> globMSRE (const Data& i_inp1, const Data& i_inp2) {
        int T = i_inp1.size();
        if (T != i_inp2.size()) throw std::runtime_error("data lengthes are different");

        double  err = locMSRE(i_inp2[0], i_inp1[0]);
        double  min = err, max = err;
        for (int t = 1; t < T; ++t) {
            double tmp = locMSRE(i_inp2[t], i_inp1[t]); 
            err += tmp; 
            if (tmp < min) min = tmp;
            if (tmp > max) max = tmp;
        }
        return std::make_tuple(err / T, min, max);
    }

    std::vector<double> getErrorsVector (const Data& i_inp1, const Data& i_inp2, double (*i_localError)(const Column&, const Column&)) {
        std::vector<double> errorsVector;
        auto iter1 = i_inp1.begin(); 
        auto iter2 = i_inp2.begin();
        for (; iter1 != i_inp1.end() && iter2 != i_inp2.end(); ++iter1, ++iter2) {
            double  locError = i_localError(*iter1, *iter2);
            errorsVector.push_back(locError);
        }
        return errorsVector;
    }
}