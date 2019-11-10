#ifndef     SOM_LAYER_H
#define     SOM_LAYER_H

#include    "simple_layer.h"


namespace nn {
    class   SomLayer : public SimpleLayer {

        private:

            Matrix    d_w2;
            int         d_d;

        public:
            SomLayer(int i_in, int i_d, int i_out);
            SomLayer(int i_d, int i_neuronsCount);

            Column operator()(const Column& i_x) override;
            bool fit (const Data& i_inp, int i_iterations) override;
    };
}
#endif