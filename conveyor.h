#ifndef      CONVEYOR_H
#define     CONVEYOR_H

#include    "nn_unit.h"

#include    <memory>
#include    <vector>

namespace nn {
    class Conveyor {
        private:
            using UnitPtr = std::unique_ptr<IUnit>;

            std::vector<UnitPtr> d_units;

        public:
            Conveyor(/* args */){}
            ~Conveyor(){}

            void addUnit (UnitPtr i_unit);

            bool    fit (Data_t i_inp, const std::vector<int>& i_iterations);
            bool    learn (Data_t i_inp, const Data_t& i_out, int iterations);
            Data_t  predict (Data_t i_inp);

            bool    test(const DataSet& i_dataset, const std::vector<int>& i_settings, std::ostream& io_os);
    };
}

#endif