#ifndef     SOM_LAYER_H
#define     SOM_LAYER_H

#include    "simple_layer.h"


namespace nn {
    class   SomLayer : public SimpleLayer {

        private:

        public:
            SomLayer(int i_in, int i_out);
            SomLayer(int i_neuronsCount);

            bool fit (const Data& i_inp, int i_iterations) override;
    };
}
#endif