#ifndef     DATA_LOADER_H
#define     DATA_LOADER_H


#include    "types.h"

#include    <utility>
#include    <string>

namespace nn {

    enum    Mode {
        NON,
        TABLE,
        DELAY
    };

    class DataLoader {

        private:
            int                     d_ptr{0};
            int                     d_mode{NON}; 
            int                     d_dataSize{1};
            std::vector<double>     d_data;
            std::vector<DataSet>    d_sets;


        public:

            DataLoader (const std::string& i_fileName, int i_maxSize = static_cast<int>(1e6));
            void    formTableSet(int i_fitLen, int i_learnLen, int i_testLen, int i_dataSize);
            void    formTableSet(int i_fitLen, int i_learnLen, int i_testLen);
            void    formDelaySet(int i_inpSize, int i_fitLen, int i_learnLen, int i_testLen);

            DataSet& get(int i_num = 0);
        private:

            Column  makeColumn(int i_size, int i_bias);
    };
}


#endif