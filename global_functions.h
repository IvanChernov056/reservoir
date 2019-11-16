#ifndef     GLOBAL_FUNCTIONS_H
#define     GLOBAL_FUNCTIONS_H


#include    "types.h"

#include    <utility>

namespace fn {
    
    double locMSRE (const Column& i_inp1, const Column& i_inp2);
    std::tuple<double, double, double> globMSRE (const Data& i_inp1, const Data& i_inp2);
    std::vector<double> getErrorsVector (const Data& i_inp1, const Data& i_inp2, double (*i_localError)(const Column&, const Column&));
    double  locRelfMSRE (const Column& i_inp1, const Column& i_inp2);
    Matrix  formMatrix (const Data& i_inp, bool i_withOnes = false);
    Matrix  getCovMat(const Data& i_inp);
    Matrix  pcaReduce (const Matrix& i_covMat, double i_criterion);
}

#endif