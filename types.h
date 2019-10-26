#ifndef     TYPES_H
#define     TYPES_H


#include    <armadillo>
using   Matrix_t = arma::mat;
using   Column_t = arma::vec;
using   Row_t    = arma::rowvec;
using   SpMat_t  = arma::sp_mat;

#include    <vector>
using       Data_t = std::vector<Column_t>;

#endif