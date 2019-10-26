#ifndef     ESN_RESERVOIR_H
#define     ESN_RESERVOIR_H


#include    "nn_unit.h"

namespace nn {
    class ESNReservoir : public IUnit {

        protected:

            Matrix_t    d_wr;

            Column_t    d_state;
            Column_t    d_b;

            Activation_t    d_f;

        public:

            ESNReservoir(int i_nr, double i_sp = 0.05, Activation_t i_f = [](double& x){x = tanh(x);});
            ~ESNReservoir(){}

            Column_t operator()(const Column_t& i_x) override;
            bool    fit(const Data_t& i_inp, int iterations = 1) override;
    };
}
#endif