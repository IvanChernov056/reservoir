#ifndef     RIDGE_READOUT_H
#define     RIDGE_READOUT_H


#include    "nn_unit.h"

namespace nn {
    class   RidgeReadout : public IUnit {
        
        private:
            Matrix    d_w;
            Column    d_b;

            double      d_ridge;
            int         d_neuronsCount;

        public:

            RidgeReadout(int i_in, int i_out, double i_ridge = 0.03);
            explicit RidgeReadout(int i_out, double i_ridge = 0.03);

            Column    operator()(const Column& i_x) override;
            bool        learn(const Data& i_inp, const Data& i_out, int i_iterations = 1) override;
            bool        fit (const Data& i_inp, int i_iterations = 1) override;
    };
}

#endif