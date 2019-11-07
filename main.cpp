#include    "nnlib.h"
#include    <fstream>

int main (int argc, char* argv[]) {


    int         datasetsNum = 130;
    int         ni = 1, nr = 40, no = 1, T1 = 1500, T2 = 2000, T3 = 200;
    std::ofstream   outFile("mgs1_4u_sim_esn_som_rid_log_130_msre.dat");
    
    nn::DataLoader  dataLoader ("mgs1.dat");

    nn::Conveyor conveyor;

    std::unique_ptr<nn::IUnit> inpUnit (new nn::SimpleLayer(ni, nr));    //nr/4
    std::unique_ptr<nn::IUnit> resUnit (new nn::ESNReservoir(nr, 0.03, [](double& x){x=1.0/(1 + exp(-x));}));
    std::unique_ptr<nn::IUnit> reducUnit (new nn::SomLayer(nr, nr/2, nr/4));
    std::unique_ptr<nn::IUnit> outUnit (new nn::RidgeReadout(nr, no, 0.03));

    conveyor.addUnit(std::move(inpUnit));
    conveyor.addUnit(std::move(resUnit));
    conveyor.addUnit(std::move(reducUnit));
    conveyor.addUnit(std::move(outUnit));

    std::vector<int>    settings{500, 500, 500, 500};

    for (int dsNum=0; dsNum < datasetsNum; ++dsNum) {
        try {
            std::cout << "dataset #" << dsNum << '\n';
            dataLoader.formDataSet({ni, no, T1, T2, T3});
            conveyor.test(dataLoader.get(dsNum), settings, outFile);
            std::cout << "\n\n";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
    outFile.close();
    
    return 0;
}