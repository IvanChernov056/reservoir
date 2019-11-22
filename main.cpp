#include    "nnlib.h"
#include    <fstream>


#define     DATA_LOG(n, ds)     for (const auto& v: std::get<n>(ds)) \
                            std::cout << v.t() << std::endl; \
                            std::cout << std::endl;


int main (int argc, char* argv[]) {

    using namespace nn;
    int         datasetsNumber = 3;
    int         nr = 400, no = 1, t1 = 0, t2 = 1000, t3 = 100;
    DataLoader  loader("mgs1.dat");
    std::ofstream   outFile;


    try {
        loader.formDelaySet (20, t1, t2, t3);
        Ssa ssa(std::get<1>(loader.get(0)));
        auto out = ssa.predict(t3, 10);
        auto err = fn::globMSRE(out ,std::get<4>(loader.get(0)));
        std::cout << std::get<0>(err) << ' ' << std::get<2>(err) << std::endl;
    } catch (...) {
        std::cout << "BOOM\n";
    }
    
    if (outFile.is_open()) outFile.close();
    return 0;
}