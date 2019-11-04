#ifndef     IRO_MODULE_H
#define     IRO_MODULE_H


#include    "nn_unit.h"

#include    <memory>


namespace nn {
    class IROModule {

        private:
            using   UnitPtr_t = std::unique_ptr<IUnit>;

            UnitPtr_t   d_inpUnit;
            UnitPtr_t   d_resUnit;
            UnitPtr_t   d_outUnit;

        public:

            IROModule (UnitPtr_t i_inpUnit, UnitPtr_t i_resUnit, UnitPtr_t i_outUnit);

            bool fit (Data_t i_inp, const std::vector<int>& i_iterations = {1, 1});
            bool learn (Data_t i_inp, const Data_t& i_out,const std::vector<int>& i_iterations = {1, 1, 1});
            Data_t predict (Data_t i_inp);
    };
}

#endif