#ifndef     TYPES_H
#define     TYPES_H


#include    <armadillo>
using   Matrix = arma::mat;
using   Column = arma::vec;
using   Row    = arma::rowvec;
using   SpMat  = arma::sp_mat;

#include    <vector>
using       Data = std::vector<Column>;


using   Activation = void (*)(double &x);

#include    <utility>
using   DataSet = std::tuple<Data, Data, Data, Data, Data>;


#endif