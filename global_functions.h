#ifndef     GLOBAL_FUNCTIONS_H
#define     GLOBAL_FUNCTIONS_H


#include    "types.h"

#include    <utility>

namespace nn {
    
    double locMSRE (const Column_t& i_inp1, const Column_t& i_inp2);
    std::tuple<double, double, double> globMSRE (const Data_t& i_inp1, const Data_t& i_inp2);
}

#endif