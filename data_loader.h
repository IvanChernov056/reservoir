#ifndef     DATA_LOADER_H
#define     DATA_LOADER_H


#include    "types.h"

#include    <utility>
#include    <string>

namespace nn {
    class   DataLoader {
        private:

            int                     d_ptr;
            std::vector<double>     d_rawData;
            std::vector<DataSet>    d_datasets;

        public:

            DataLoader (const std::string& i_name, int i_maxSize = static_cast<int>(1e6));

            bool        formDataSet (const SettingsSet& i_sset);
            DataSet&    get(int i_setNum);

        private:

            Data_t  readData (int i_ds, int i_ln, int);
    };
}


#endif