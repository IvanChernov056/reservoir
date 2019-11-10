#include    "nnlib.h"
#include    <fstream>


#define     DATA_LOG(n, ds)     for (const auto& v: std::get<n>(ds)) \
                            std::cout << v.t() << std::endl; \
                            std::cout << std::endl;


int main (int argc, char* argv[]) {

    using namespace nn;
    int         datasetsNumber = 3;
    int         nr = 400, no = 1, t1 = 1500, t2 = 2000, t3 = 30;
    DataLoader  loader("mgs1.dat");
    std::ofstream   outFile;

    Conveyor    conveyor;

    std::unique_ptr<IUnit>  inpUnit(new SimpleLayer(nr));
    std::unique_ptr<IUnit>  reservoirUnit(new ESNReservoir(nr, 1.0 +0.5, 0.025));
    std::unique_ptr<IUnit>  outUnit(new RidgeReadout(no, 0.03));

    conveyor.addUnit(std::move(inpUnit));
    conveyor.addUnit(std::move(reservoirUnit));
    conveyor.addUnit(std::move(outUnit));

    for (int dsNum = 0; dsNum < datasetsNumber; ++dsNum) {
        try {
            std::cout << "dataset #" << dsNum << '\n';
            loader.formDataSet({t1,t2,t3});
            conveyor.testBySelf(loader.get(dsNum), 500, outFile);
        } catch(std::exception& e) {
            std::cout << "\n\t!!!something wrong!!!\n\t" << e.what() << "\n\n";
            break;
        }
    }

    if (outFile.is_open()) outFile.close();
    return 0;
}