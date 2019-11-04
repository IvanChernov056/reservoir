#ifndef     TYPES_H
#define     TYPES_H


#include    <armadillo>
using   Matrix_t = arma::mat;
using   Column_t = arma::vec;
using   Row_t    = arma::rowvec;
using   SpMat_t  = arma::sp_mat;

#include    <vector>
using       Data_t = std::vector<Column_t>;


using   Activation_t = void (*)(double &x);

#include    <utility>
using   DataSet = std::tuple<Data_t, Data_t, Data_t, Data_t, Data_t>;
using   SettingsSet = std::tuple<int, int, int, int, int>;

#endif