#ifndef     SIMPLE_LAYER_H
#define     SIMPLE_LAYER_H


#include    "nn_unit.h"
namespace nn {
    class SimpleLayer : public IUnit {

        protected:

            Matrix_t    d_w1;

            int         d_neuronsCount;

        public:

            SimpleLayer(int i_in, int i_out);
            SimpleLayer(int i_neuronsCount);
            Column_t    operator()(const Column_t& i_x) override;

            bool        fit (const Data_t& i_inp, int i_iterations = 1) override;
    };
}
#endif