#include        "data_loader.h"
#include        <fstream>
#include        <sstream>

namespace nn {

    DataLoader::DataLoader (const std::string& i_name, int i_maxSize) : d_ptr(0) {
        std::ifstream file (i_name);
        d_rawData.reserve(i_maxSize);

        int i = 0;
        do{
            double  tmp;
            file >> tmp;
            d_rawData.push_back(tmp);
            ++i;
        }
        while (!file.eof() && i < i_maxSize);
        file.close();
    }

    bool    DataLoader::formDataSet (const SettingsSet& i_sset) {
        int inpSize, outSize, fitLen, learnLen, testLen;
        std::tie (inpSize, outSize, fitLen, learnLen, testLen) = i_sset;

        DataSet     dataset;
        std::get<0>(dataset) = std::move(readData(inpSize, fitLen, fitLen));
        std::get<1>(dataset) = std::move(readData(inpSize, learnLen, inpSize));
        std::get<2>(dataset) = std::move(readData(outSize, learnLen, learnLen-inpSize));
        std::get<3>(dataset) = std::move(readData(inpSize, testLen, inpSize));
        std::get<4>(dataset) = std::move(readData(outSize, testLen, testLen-inpSize));

        d_datasets.push_back(dataset);
        return true;
    }

    Data_t  DataLoader::readData (int i_ds, int i_ln, int i_wh) {
        Data_t  output;
        Column_t    col(i_ds);
        std::cout << "loader ptr : " << d_ptr;
        if (d_ptr + i_ln*i_ds >= d_rawData.size()) throw std::runtime_error("not enough data");

        for (int t = 0; t < i_ln; ++t) {
            for (int i = 0; i < i_ds; ++i) 
                col[i] = d_rawData[d_ptr + i + t];
            output.push_back(col);
        }

        d_ptr += i_wh;
        std::cout << ",  " << d_ptr << ", ln : " << i_ln << '\n';
        return output;
    }


    DataSet&    DataLoader::get(int i_setNum) {
        return d_datasets[i_setNum];
    }
}