#include    "nnlib.h"
#include    <fstream>


#define     DATA_LOG(n, ds)     for (const auto& v: std::get<n>(ds)) \
                            std::cout << v.t() << std::endl; \
                            std::cout << std::endl;


int main (int argc, char* argv[]) {

    using namespace nn;
    int         nr = 400, no = 1, t1 = 1500, t2 = 2000, t3 = 30;
    DataLoader  loader("mgs1.dat");

    Conveyor    conveyor;

    std::unique_ptr<IUnit>  inpUnit(new SimpleLayer(nr));
    std::unique_ptr<IUnit>  reservoirUnit(new ESNReservoir(nr));
    std::unique_ptr<IUnit>  outUnit(new RidgeReadout(no, 0.03));

    conveyor.addUnit(inpUnit);
    conveyor.addUnit(reservoirUnit);
    conveyor.addUnit(outUnit);
    return 0;
}