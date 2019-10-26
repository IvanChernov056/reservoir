#include    "som_input.h"
#include    "esn_reservoir.h"
#include    <iostream>



int main (int argc, char* argv[]) {


    int         ni = 1, nd = 5, nr = 30, T = 100;
    nn::SomInp unit(ni, nd, nr);
    nn::ESNReservoir res (nr);

    Data_t  inp_data;
    Data_t  out_data;
    for (int t = 0; t < T; ++t) 
        inp_data.push_back(arma::randn<Column_t>(ni));

    if (unit.fit(inp_data, 100)) 
        out_data = std::move (unit.predict(inp_data));
    else std::cout << "input unit failed\n";

    if (!res.fit(out_data))
        std::cout << "res failed\n";

    std::cout << "all successn\n";    

    return 0;
}