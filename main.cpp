#include    "nnlib.h"
#include    <fstream>


#define     DATA_LOG(n, ds)     for (const auto& v: std::get<n>(ds)) \
                            std::cout << v.t() << std::endl; \
                            std::cout << std::endl;


int main (int argc, char* argv[]) {

   
    int         datasetsNum = 1;
    int         ni = 1, nr = 400, no = 1, T1 = 1500, T2 = 2000, T3 = 200;
    std::ofstream   outFile("THIS MUST BE DELETED.dat");
    
    nn::DataLoader  dataLoader ("mgs1.dat");

    nn::Conveyor conveyor;

    std::unique_ptr<nn::IUnit> inpUnit (new nn::SomLayer(ni, nr));    //nr/4
    std::unique_ptr<nn::IUnit> resUnit (new nn::ESNReservoir(nr));
    std::unique_ptr<nn::IUnit> outUnit (new nn::RidgeReadout(no, 0.03));

    conveyor.addUnit(std::move(inpUnit));
    conveyor.addUnit(std::move(resUnit));
    conveyor.addUnit(std::move(outUnit));

    for (int dsNum=0; dsNum < datasetsNum; ++dsNum) {
        try {
            std::cout << "dataset #" << dsNum << '\n';
            dataLoader.formTableSet(T1, T2, T3);
            conveyor.testByExact(dataLoader.get(dsNum), 500, outFile);
            std::cout << "\n\n";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
    outFile.close();
    
    return 0;
}