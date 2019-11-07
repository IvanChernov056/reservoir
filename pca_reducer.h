#ifndef     PCA_REDUCER_H
#define     PCA_REDUCER_H


#include    "nn_unit.h"

namespace nn {
    class   PcaReducer : public IUnit {

        private:
            Matrix_t    d_w;
            int         d_d;
    
        public:
            
            PcaReducer (){}

            Column_t    operator()(const Column_t& i_x) override;
            bool        fit(const Data_t& i_inp, int i_iterations = 1) override;
    };
}

#endif