#ifndef     NN_UNIT_H
#define     NN_UNIT_H


#include    "types.h"


namespace nn {
    class   IUnit {

        public:

            virtual ~IUnit() {}
            Data predict (const Data& i_inp) {
                Data out;
                for (const auto& v: i_inp) {
                    out.push_back(operator()(v));
                }
                return out;
            }
            virtual Column operator()(const Column& i_x) {return i_x;}

            virtual bool fit (const Data& i_inp, int i_iterations = 100) {return true;}
            virtual bool learn (const Data& i_inp, const Data& i_out, int i_iterations = 100) {return true;}
    };
}
#endif