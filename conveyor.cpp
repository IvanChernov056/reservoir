#include    "conveyor.h"
#include    "global_functions.h"
#include    "timer.h"


namespace nn {
    void Conveyor::addUnit (UnitPtr i_unit) {
        d_units.push_back(std::move(i_unit));
    }

    bool    Conveyor::fit (Data_t i_inp, const std::vector<int>& i_iterations) {
        std::cout << "fit stage :\n";
        int     numUnits = d_units.size();
        if (numUnits == 0)
            return false;
        
        for (int unit = 0; unit < numUnits-1; ++unit) {
            try {
            if(!d_units[unit]->fit(i_inp, i_iterations[unit]))
                return false;
            i_inp = d_units[unit]->predict(i_inp);
            } catch (std::exception& e) {
                std::cout << "IN UNIT " << unit << "happend : ";
                std::cout << e.what() << std::endl;
                throw;
            }
        }

        return true;
    }

    bool    Conveyor::learn (Data_t i_inp, const Data_t& i_out, int i_iterations) {
        std::cout << "learn stage :\n";
        int     numUnits = d_units.size();
        if (numUnits == 0)
            return false;
        
        for (int unit = 0; unit < numUnits-1; ++unit) 
            i_inp = d_units[unit]->predict(i_inp);

        return d_units[numUnits-1]->fit(i_inp, i_out, i_iterations);
    }

    Data_t  Conveyor::predict(Data_t i_inp) {
        std::cout << "predict stage :\n";
        for (const auto& unit : d_units) 
            i_inp = unit->predict(i_inp);
        return i_inp;
    }

    bool    Conveyor::test (const DataSet& i_dataset, const std::vector<int>& i_settings, std::ostream& io_os) {
        
        Timer timer;
        bool fitResult = fit(std::get<0>(i_dataset), i_settings);
        std::cout << "fit result : " << (fitResult ? "success" : "fail") << '\n';

        bool learnResult = learn(std::get<1>(i_dataset), std::get<2>(i_dataset), i_settings[i_settings.size()-1]);
        std::cout << "learn result : " << (learnResult ? "success" : "fail") << '\n';

        Data_t  out = predict(std::get<3>(i_dataset));
        bool predictResult = !out.empty();
        std::cout << "predict result : " << (predictResult ? "success" : "fail") << '\n';

        auto    errors = globMSRE (out, std::get<4>(i_dataset));

        io_os << std::get<0>(errors) << " \t" << std::get<1>(errors) << " \t" << std::get<2>(errors) << " \t" << timer.stop() << '\n';
        std::cout << "Errors :  glob = " 
                << std::get<0>(errors) 
                << ", \tmin = " << std::get<1>(errors) 
                << ", \t max = " << std::get<2>(errors) 
                << '\n';

        for (int i = 0; i < 10; ++i)
            std::cout << "out[" << i << "] : " << out[i][0] << '\t' << std::get<4>(i_dataset)[i][0] << '\n';

        return fitResult && learnResult && predictResult;
    }
}