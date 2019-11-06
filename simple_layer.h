#ifndef     SIMPLE_LAYER_H
#define     SIMPLE_LAYER_H


#include    "nn_unit.h"
namespace nn {
    class SimpleLayer : public IUnit {

        protected:

            Matrix_t    d_w1;

        public:

            SimpleLayer(int i_in, int i_out);
            Column_t    operator()(const Column_t& i_x) override;
    };
}
#endif