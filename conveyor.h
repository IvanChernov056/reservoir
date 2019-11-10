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

            Column  operator() (const Column& i_x);
            bool    fit (Data i_inp, int i_iterations);
            bool    learn (Data i_inp, const Data& i_out, int iterations);
            Data    predict (Data i_inp);
            Data    predict (const Column& i_inp, int i_horizon);

            bool    testByExact(const DataSet& i_dataset, int i_iterations, std::ostream& io_os);
            bool    testBySelf(const DataSet& i_dataset, int i_iterations, std::ostream& io_os);
    };
}

#endif