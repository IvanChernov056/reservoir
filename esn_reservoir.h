#ifndef     ESN_RESERVOIR_H
#define     ESN_RESERVOIR_H


#include    "nn_unit.h"

namespace nn {
    class ESNReservoir : public IUnit {

        protected:

            Matrix    d_wr;

            Column    d_state;
            Column    d_b;

            Activation    d_f;

        public:

            ESNReservoir(int i_nr, double i_radius = 0.98, double i_sp = 0.03, Activation i_f = [](double& x){x=1.0/(1 + exp(-x));});
            ~ESNReservoir(){}

            Column operator()(const Column& i_x) override;
            bool    fit(const Data& i_inp, int iterations = 1) override;
    };
}
#endif