#include        "data_loader.h"
#include        <fstream>
#include        <sstream>

namespace nn {

    int getDataSize(std::ifstream& io_s, std::vector<double>& o_data) {
        char* line = new char[2048];
        io_s.getline(line, 2048);
        std::stringstream stream;
        stream << line;
        delete line;

        int dataSize = 0;
        do {
            double tmp;
            stream >> tmp;
            if (!stream.fail() && !stream.bad()) {
                ++dataSize;
                o_data.push_back(tmp);
            }
            else break;
        } while (!stream.eof());

        return dataSize;
    }

    DataLoader::DataLoader (const std::string& i_fileName, int i_maxSize) {
        std::ifstream file(i_fileName);
        int counter = 0;
        if (file.is_open()) {
            d_dataSize = getDataSize(file, d_data);
            do {
                double doubleReader;
                file >> doubleReader;
                if (!file.fail() && !file.bad())
                    d_data.push_back(doubleReader);
                else break;
            }while (!file.eof());
        }
        else std::cout << "file \'" << i_fileName << "\' was not opened\n"; 
    }

    void    DataLoader::formTableSet(int i_fitLen, int i_learnLen, int i_testLen, int i_dataSize) {
        if (d_mode != TABLE && d_mode != NON) {
            std::cout << "this reader in another mode now. You can not form table data\n";
            return;
        }

        try {
            DataSet tableSet;

            for (int i= 0; i < i_fitLen; ++i)
                std::get<0>(tableSet).push_back (std::move(makeColumn(i_dataSize, i*i_dataSize)));
            d_ptr += i_fitLen*i_dataSize;

            for (int i= 0; i < i_learnLen; ++i)
                std::get<1>(tableSet).push_back (std::move(makeColumn(i_dataSize, i*i_dataSize)));
            d_ptr += i_dataSize;

            for (int i= 0; i < i_learnLen; ++i)
                std::get<2>(tableSet).push_back (std::move(makeColumn(i_dataSize, i*i_dataSize)));
            d_ptr += i_dataSize*(i_learnLen-1);

            for (int i= 0; i < i_testLen; ++i)
                std::get<3>(tableSet).push_back (std::move(makeColumn(i_dataSize, i*i_dataSize)));
            d_ptr += i_dataSize;

            for (int i= 0; i < i_testLen; ++i)
                std::get<4>(tableSet).push_back (std::move(makeColumn(i_dataSize, i*i_dataSize)));
            d_ptr += i_dataSize*(i_testLen-1);
            
            d_sets.push_back(std::move(tableSet));
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            throw;
        }

        d_mode = TABLE;
    }

    void    DataLoader::formTableSet(int i_fitLen, int i_learnLen, int i_testLen) {
        if (d_dataSize > 0)
            formTableSet(i_fitLen, i_learnLen, i_testLen, d_dataSize);
        else 
            std::cout << "cannot define data size\n";
    }

    void    DataLoader::formDelaySet (int i_inpSize, int i_fitLen, int i_learnLen, int i_testLen) {
        if (d_mode != DELAY && d_mode != NON) {
            std::cout << "this reader in another mode now. You can not form delay data\n";
            return;
        }

        try {
            DataSet delaySet;

            for (int i= 0; i < i_fitLen; ++i)
                std::get<0>(delaySet).push_back (std::move(makeColumn(i_inpSize, i)));
            d_ptr += i_fitLen;

            for (int i= 0; i < i_learnLen; ++i)
                std::get<1>(delaySet).push_back (std::move(makeColumn(i_inpSize, i)));
            

            for (int i= 0; i < i_learnLen; ++i)
                std::get<2>(delaySet).push_back (std::move(makeColumn(1, i+i_inpSize)));
            d_ptr += (i_learnLen-1) + 1;

            for (int i= 0; i < i_testLen; ++i)
                std::get<3>(delaySet).push_back (std::move(makeColumn(i_inpSize, i)));
            

            for (int i= 0; i < i_testLen; ++i)
                std::get<4>(delaySet).push_back (std::move(makeColumn(1, i+i_inpSize)));
            d_ptr += (i_testLen-1) + 1;
            
            d_sets.push_back(std::move(delaySet));
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            throw;
        }

        d_mode = DELAY;
    }
    Column  DataLoader::makeColumn (int i_size, int i_bias) {
        if (i_bias + d_ptr + i_size >= d_data.size())
            throw std::runtime_error("not enough data to form list");
        Column col(i_size);
        for(int i = 0; i < i_size; ++i) 
            col[i] = d_data[d_ptr + i_bias + i];
        
        return col;
    }

    DataSet& DataLoader::get(int i_num) {
        if (i_num < 0 || i_num >= d_sets.size())
            throw std::runtime_error("out of range");
        return d_sets[i_num];
    }
}