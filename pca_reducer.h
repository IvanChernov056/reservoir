#ifndef     PCA_REDUCER_H
#define     PCA_REDUCER_H


#include    "nn_unit.h"

namespace nn {
    class   PcaReducer : public IUnit {

        private:
            Matrix    d_w;
            int         d_d{0};
    
        public:
            
            PcaReducer (){}

            Column    operator()(const Column& i_x) override;
            bool        fit(const Data& i_inp, int i_iterations = 1) override;
    };
}

#endif