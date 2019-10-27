#ifndef     SIMPLE_INPUT_H
#define     SIMPLE_INPUT_H


#include    "nn_unit.h"
namespace nn {
    class SimpleInput : public IUnit {

        protected:

            Matrix_t    d_w1;

        public:

            SimpleInput(int i_in, int i_out);
            Column_t    operator()(const Column_t& i_x) override;
    };
}
#endif