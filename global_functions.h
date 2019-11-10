#ifndef     GLOBAL_FUNCTIONS_H
#define     GLOBAL_FUNCTIONS_H


#include    "types.h"

#include    <utility>

namespace nn {
    
    double locMSRE (const Column& i_inp1, const Column& i_inp2);
    std::tuple<double, double, double> globMSRE (const Data& i_inp1, const Data& i_inp2);
}

#endif