#ifndef     SOM_INPUT_H
#define     SOM_INPUT_H

#include    "nn_unit.h"


namespace nn {
    class   SomInp : public IUnit {

        private:

            Matrix_t    d_w1;
            Matrix_t    d_w2;

        public:
            SomInp(int i_in, int i_d, int i_out);

            Column_t operator()(const Column_t& i_x) override;
            bool fit (const Data_t& i_inp, int i_iterations) override;
    };
}
#endif