#ifndef     DATA_LOADER_H
#define     DATA_LOADER_H


#include    "types.h"

#include    <utility>
#include    <string>

namespace nn {
    class   DataLoader {
        private:
            using   SettingsSet = std::tuple<int, int, int>;
            int                     d_ptr;
            std::vector<Column>     d_rawData;
            std::vector<DataSet>    d_datasets;

        public:

            explicit DataLoader (const std::string& i_name, int i_maxSize = static_cast<int>(1e6));

            bool        formDataSet (const SettingsSet& i_sset);
            DataSet&    get(int i_setNum);

        private:

            Data  readData (int i_ln, int, int );
    };
}


#endif