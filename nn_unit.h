#ifndef     NN_UNIT_H
#define     NN_UNIT_H


#include    "types.h"


namespace nn {
    class   IUnit {

        public:

            virtual ~IUnit() {}
            Data_t predict (const Data_t& i_inp) {
                Data_t out;
                for (const auto& v: i_inp) {
                    out.push_back(operator()(v));
                }
                return out;
            }
            virtual Column_t operator()(const Column_t& i_x) {return i_x;}

            virtual bool fit (const Data_t& i_inp, int i_iterations = 100) {return false;}
            virtual bool fit (const Data_t& i_inp, const Data_t& i_out, int i_iterations = 100) {return false;}
    };
}
#endif