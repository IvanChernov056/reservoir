#include    "ssa.h"

Ssa::Ssa(const Data& i_inp) : d_data(i_inp)
{
    fit(d_data);
}

bool    Ssa::fit(const Data& i_inp) {
    if (i_inp.empty()) {
        std::cout <<"data list is empty\n";
        return false;
    }
    
    d_newX = *(i_inp.end()-1);
    formQStat();

    return formVStats(i_inp);
}

bool    Ssa::formVStats (const Data& i_inp) {
    try {
        if (i_inp.empty()) throw std::runtime_error("empty data list");
        if (i_inp[0].empty()) throw std::runtime_error("data size is null");
        int       dataSize = i_inp[0].n_elem;

        Matrix    covMat = fn::getCovMat(i_inp);
        double    criterion = arma::trace(covMat) / covMat.n_elem;
        
        Matrix v = fn::pcaReduce(covMat, criterion);
        d_vStar = v.rows(0, dataSize-2);
        d_vTau  = v.row(dataSize-1);
    } catch (std::exception& e) {
        std::cout << "IN FORM V::" << e.what() << std::endl;
        return false;
    }
    return true;   
}

Column  Ssa::oneStepPredict () {
    auto   numerator = (d_vTau*d_vStar.t()*d_q);
    double denumerator = 1 - arma::dot(d_vTau, d_vTau);

    Column  colNextValue = numerator / denumerator;
    double dNextValue = colNextValue[0];
    d_data.push_back(formNewX(dNextValue));

    return colNextValue;
}

Column& Ssa::formQStat() {
    d_q = d_newX.rows(1, d_newX.n_elem-1);
    return d_q;
}

Column& Ssa::formNewX(double i_value) {
    for (int i = 0; i < d_newX.n_elem -1; ++i)
        d_newX[i] = d_newX[i+1];
    d_newX[d_newX.n_elem -1] = i_value;
    formQStat();
    return  d_newX;
}

Data Ssa::predict(int i_horizon, int i_refit) {
    Data    output;

    for (int n = 1; n <= i_horizon; ++n) {
       
        output.push_back(std::move(oneStepPredict()));
        if (n % i_refit == 0 && i_refit > 1) {
             std::cout << "call\n";
            if (!fit(d_data))
                throw std::runtime_error("cannot refit");
        }
    }
    return output;
}