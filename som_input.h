#ifndef     SOM_INPUT_H
#define     SOM_INPUT_H

#include    "simple_input.h"


namespace nn {
    class   SomInput : public SimpleInput {

        private:

            Matrix_t    d_w2;

        public:
            SomInput(int i_in, int i_d, int i_out);

            Column_t operator()(const Column_t& i_x) override;
            bool fit (const Data_t& i_inp, int i_iterations) override;
    };
}
#endif