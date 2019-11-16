#include    "nnlib.h"
#include    <fstream>


#define     DATA_LOG(n, ds)     for (const auto& v: std::get<n>(ds)) \
                            std::cout << v.t() << std::endl; \
                            std::cout << std::endl;


int main (int argc, char* argv[]) {

    using namespace nn;
    int         datasetsNumber = 3;
    int         nr = 400, no = 1, t1 = 5, t2 = 5, t3 = 5;
    DataLoader  loader("THIS MUST BE DELETED2.dat");
    std::ofstream   outFile;

    Conveyor    conveyor;

    std::unique_ptr<IUnit>  somUnit(new SomLayer(nr/4));
    std::unique_ptr<IUnit>  simpleUnit(new SimpleLayer(nr));
    std::unique_ptr<IUnit>  reservoirUnit(new ESNReservoir(nr, 1.0 +0.5, 0.025));
    std::unique_ptr<IUnit>  outUnit(new RidgeReadout(no, 0.03));

    conveyor.addUnit(std::move(somUnit));
    conveyor.addUnit(std::move(simpleUnit));
    conveyor.addUnit(std::move(reservoirUnit));
    conveyor.addUnit(std::move(outUnit));

    try {
        loader.formTableSet(t1, t2, t3);
        loader.formTableSet(t1, t2, t3);
        DATA_LOG(4, loader.get());
        std::cout << '\n';
        DATA_LOG(0, loader.get(1));
        std::cout << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    if (outFile.is_open()) outFile.close();
    return 0;
}