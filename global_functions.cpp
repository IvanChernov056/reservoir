#include    "global_functions.h"


namespace nn {
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
}