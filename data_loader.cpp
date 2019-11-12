#include        "data_loader.h"
#include        <fstream>
#include        <sstream>

namespace nn {

    DataLoader::DataLoader (const std::string& i_name, int i_maxSize) : d_ptr(0) {
        
    }
    
    bool DataLoader::readAsRow () {
        std::ifstream file (d_fileName);
        d_rawDoubleData.reserve(d_maxSize);

        int i = 0;
        do{
            double  tmp;
            file >> tmp;
            d_rawDoubleData.push_back(tmp);
            ++i;
        }
        while (!file.eof() && i < d_maxSize);
        file.close();
    }

    bool    DataLoader::readAsTable() {
        std::ifstream file (d_fileName);
        d_rawColumnData.reserve(d_maxSize);

        int sampleCounter = 0;
        do{
            std::stringstream   strStream;
            char line[1024];
            file.getline(line, 1024);
            strStream << line;
            std::vector<double> vecData;
            do {
                double tmp;
                strStream >> tmp;
                vecData.push_back(tmp);
            }
            while (!strStream.eof());
            
            Column  vec(vecData.size());
            for (int i = 0; i < vec.n_elem; ++i) 
                vec[i] = vecData[i];
            d_rawColumnData.push_back(vec);
            ++sampleCounter;
        }
        while (!file.eof() && sampleCounter < d_maxSize);
        file.close();
    }

    using   SettingsSet = std::tuple<int, int, int>;
    bool    DataLoader::formDataSet (const SettingsSet& i_sset) {
        int fitLen, learnLen, testLen;
        std::tie (fitLen, learnLen, testLen) = i_sset;

        DataSet     dataset;
        std::get<0>(dataset) = std::move(readData(fitLen, fitLen, 0));
        std::get<1>(dataset) = std::move(readData(learnLen, 0, 0));
        std::get<2>(dataset) = std::move(readData(learnLen, learnLen, 1));
        std::get<3>(dataset) = std::move(readData(testLen, 0, 0));
        std::get<4>(dataset) = std::move(readData(testLen, testLen, 1));

        d_datasets.push_back(dataset);
        return true;
    }

    Data  DataLoader::readData (int i_ln, int i_ptrBias, int i_oneZeroBias) {
        auto firstElemIter = d_rawColumnData.begin() + d_ptr + i_oneZeroBias;
        auto lastElemIter = d_rawColumnData.begin() + i_ln + d_ptr + i_oneZeroBias;
        d_ptr += i_ptrBias;
        return Data(firstElemIter, lastElemIter);
    }


    DataSet&    DataLoader::get(int i_setNum) {
        return d_datasets[i_setNum];
    }
}