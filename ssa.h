#ifndef     SSA_H
#define     SSA_H


#include    "types.h"
#include    "global_functions.h"


class Ssa {
    private:

        Matrix  d_vStar;
        Row     d_vTau;
        Column  d_q;
        Column  d_newX;
        Data    d_data;
        
        int     d_delay{1};
        int     d_length{1};

    public:

        Ssa(const Data& i_inp = {});

        bool                    fit (const Data& i_inp);
        std::vector<Column>     predict(int i_horizon, int i_refit);

    private:

        bool    formVStats (const Data& i_inp);
        Column  oneStepPredict ();
        Column& formQStat();
        Column& formNewX(double i_value);
        Matrix  formDelayMatrix (const std::vector<double>& i_inp, int i_startPoint = 0);
};

#endif