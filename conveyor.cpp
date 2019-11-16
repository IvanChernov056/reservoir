#include    "conveyor.h"
#include    "global_functions.h"
#include    "timer.h"


namespace nn {
    void Conveyor::addUnit (UnitPtr i_unit) {
        d_units.push_back(std::move(i_unit));
    }

    Column  Conveyor::operator()(const Column& i_inp) {
        Column  input = i_inp;
        try {
            for (auto& unit : d_units)
                input = unit->operator()(input);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            throw;
        }

        return input;
    }

    bool    Conveyor::fit (Data i_inp, int i_iterations) {
        std::cout << "fit stage :\n";
        if (i_inp.empty()) return false;

        for (auto& unit : d_units) {
            try {
                if (!unit->fit(i_inp, i_iterations))
                    return false;
                if(unit != d_units.back())
                    i_inp = unit->predict(i_inp);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                throw;
            }
        }

        return true;
    }

    bool    Conveyor::learn (Data i_inp, const Data& i_out, int i_iterations) {
        std::cout << "learn stage :\n";
        if (i_inp.empty()) return false;

        for (auto& unit : d_units) {
            try {
                if (!unit->learn(i_inp, i_out, i_iterations))
                    return false;
                if(unit != d_units.back())
                    i_inp = unit->predict(i_inp);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                throw;
            }
        }

        return true;
    }

    Data  Conveyor::predict(Data i_inp) {
        std::cout << "predict stage :\n";
        for (const auto& unit : d_units) 
            i_inp = unit->predict(i_inp);
        return i_inp;
    }

    Data    Conveyor::predict(const Column& i_inp, int i_horizon) {
        Data    output;
        Column  out = i_inp;
        for (int t = 0; t < i_horizon; ++t) {
            out = operator()(out);
            output.push_back(out);
        }
        return output;
    }

    bool    Conveyor::testByExact (const DataSet& i_dataset, int i_iterations, std::ostream& io_os) {
        
        Timer timer;
        bool fitResult = fit(std::get<0>(i_dataset), i_iterations);
        std::cout << "fit result : " << (fitResult ? "success" : "fail") << '\n';

        bool learnResult = learn(std::get<1>(i_dataset), std::get<2>(i_dataset), i_iterations);
        std::cout << "learn result : " << (learnResult ? "success" : "fail") << '\n';

        Data  out = predict(std::get<3>(i_dataset));
        bool predictResult = !out.empty();
        std::cout << "predict result : " << (predictResult ? "success" : "fail") << '\n';

        auto    errors = fn::globMSRE (out, std::get<4>(i_dataset));

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

    bool    Conveyor::testBySelf(const DataSet& i_dataset, int i_iterations, std::ostream& io_os) {
        Timer timer;
        bool fitResult = fit(std::get<0>(i_dataset), i_iterations);
        std::cout << "fit result : " << (fitResult ? "success" : "fail") << '\n';

        bool learnResult = learn(std::get<1>(i_dataset), std::get<2>(i_dataset), i_iterations);
        std::cout << "learn result : " << (learnResult ? "success" : "fail") << '\n';

        Data  out = predict(std::get<3>(i_dataset)[0], std::get<3>(i_dataset).size());
        bool predictResult = !out.empty();
        std::cout << "predict result : " << (predictResult ? "success" : "fail") << '\n';

        std::vector<double> errorsVector = fn::getErrorsVector(out, std::get<4>(i_dataset), fn::locMSRE);
        std::cout << "errors :\n";
        int sample = 0;
        do
            std::cout << sample+1 << " : " << errorsVector[sample] << '\n';
        while(errorsVector[sample++] < 1.1 && sample < errorsVector.size());
        return fitResult && learnResult && predictResult;
    }
}