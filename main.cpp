#include    "nnlib.h"
#include    <fstream>


#define     DATA_LOG(n, ds)     for (const auto& v: std::get<n>(ds)) \
                            std::cout << v.t() << std::endl; \
                            std::cout << std::endl;


int main (int argc, char* argv[]) {

    nn::DataLoader  loader ("tadtd");
    int         T1 = 3, T2 = 4, T3 = 2;
    loader.formDataSet({T1, T2, T3});
    loader.formDataSet({T1, T2, T3});


    DataSet ds1 = loader.get(0);
    DATA_LOG(0, ds1);
    DATA_LOG(1, ds1);
    DATA_LOG(2, ds1);
    DATA_LOG(3, ds1);
    DATA_LOG(4, ds1);
    return 0;
}