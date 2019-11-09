#ifndef     RIDGE_READOUT_H
#define     RIDGE_READOUT_H


#include    "nn_unit.h"

namespace nn {
    class   RidgeReadout : public IUnit {
        
        private:
            Matrix_t    d_w;
            Column_t    d_b;

            double      d_ridge;
            int         d_neuronsCount;

        public:

            RidgeReadout(int i_in, int i_out, double i_ridge = 0.03);
            RidgeReadout(int i_out, double i_ridge);

            Column_t    operator()(const Column_t& i_x) override;
            bool        learn(const Data_t& i_inp, const Data_t& i_out, int i_iterations = 1) override;
            bool        fit (const Data_t& i_inp, int i_iterations = 1) override;
    };
}

#endif