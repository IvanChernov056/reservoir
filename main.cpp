#include    "nnlib.h"
#include    <fstream>

int main (int argc, char* argv[]) {


    int         datasetsNum = 10;
    int         ni = 1, nr = 400, no = 1, T1 = 1500, T2 = 2000, T3 = 200;
    std::ofstream   outFile("THIS MUST BE DELETED.dat");
    
    nn::DataLoader  dataLoader ("mgs1.dat");

    nn::Conveyor conveyor;

    std::unique_ptr<nn::IUnit> inpUnit (new nn::SimpleLayer(nr));    //nr/4
    std::unique_ptr<nn::IUnit> resUnit (new nn::ESNReservoir(nr, 1.0, 0.03, [](double& x){x=1.0/(1 + exp(-x));}));
    std::unique_ptr<nn::IUnit> reduceUnit (new nn::PcaReducer());
    std::unique_ptr<nn::IUnit> outUnit (new nn::RidgeReadout(no, 0.03));

    conveyor.addUnit(std::move(inpUnit));
    conveyor.addUnit(std::move(resUnit));
    conveyor.addUnit(std::move(reduceUnit));
    conveyor.addUnit(std::move(outUnit));

    for (int dsNum=0; dsNum < datasetsNum; ++dsNum) {
        try {
            std::cout << "dataset #" << dsNum << '\n';
            dataLoader.formDataSet({ni, no, T1, T2, T3});
            conveyor.test(dataLoader.get(dsNum), 500, outFile);
            std::cout << "\n\n";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
    outFile.close();
    
    return 0;
}