#include    "global_functions.h"
#include    <algorithm>

namespace fn {

    Column  avaragner (const Data& i_x) {
        if (i_x.empty()) throw std::runtime_error("avaranger func : list is empty");
        Column avrg = i_x[0];
        for (auto v = i_x.begin()+1; v != i_x.end(); ++v)
            avrg += *v;
        return avrg / i_x.size();
    }

    double  avaragner (const std::vector<double>& i_x) {
        if (i_x.empty()) throw std::runtime_error("avaranger func : list is empty");
        double avrg = i_x[0];
        for (auto v = i_x.begin()+1; v != i_x.end(); ++v)
            avrg += *v;
        return avrg / i_x.size();
    }

    double  squaredNorm (const Column& i_x){
        double sqNorm = 0.0;
        i_x.for_each([&sqNorm](double x){
            sqNorm += x*x;
        });
        return sqNorm;
    }


    double  nrmse (const Data& i_predict, const Data& i_exact) {
    
        Column  exAvrg = avaragner(i_exact);
    
        std::vector<double> numeratorData(i_predict.size());
        std::transform(i_predict.begin(), 
                    i_predict.end(), 
                    i_exact.begin(), 
                    numeratorData.begin(), 
                    [](const Column& u, const Column& v)
                    {
                        return squaredNorm(u - v);
                    });
    
        std::vector<double> denumeratorData(i_predict.size());
        std::transform(i_predict.begin(), 
                    i_predict.end(), 
                    denumeratorData.begin(), 
                    [&exAvrg](const Column& u)
                    {
                        return squaredNorm(u - exAvrg);
                    }); 
    
        double  numerator = avaragner(numeratorData);
    
        double  denumerator = avaragner(denumeratorData);
    
        if (denumerator <= 0) throw std::runtime_error("nrmse :: denumenator less then 0");
    
        return sqrt (numerator/ denumerator);
    }



    double  locRelfMSRE (const Column& i_inp1, const Column& i_inp2) {
        double  n1 = arma::norm(i_inp1);
        double  n2 = arma::norm(i_inp2);
        double  err = arma::norm(i_inp1 - i_inp2);
        return err / n1 > n2 ? n1 : n2;
    }

    double locMSE (const Column& i_inp1, const Column& i_inp2) {
        Column e = i_inp2 - i_inp1;
        double  err = 0;
        e.for_each([&err](double x){err += x*x;});
        return err/e.n_elem;
    }

    double locMSRE (const Column& i_inp1, const Column& i_inp2) {
        return sqrt(locMSE(i_inp1, i_inp2));
    }

    std::tuple<double, double, double> globMSRE (const Data& i_inp1, const Data& i_inp2) {
        int T = i_inp1.size();
        if (T != i_inp2.size()) throw std::runtime_error("data lengthes are different");

        double  err = locMSRE(i_inp2[0], i_inp1[0]);
        double  min = err, max = err;
        for (int t = 1; t < T; ++t) {
            double tmp = locMSRE(i_inp2[t], i_inp1[t]); 
            err += tmp; 
            if (tmp < min) min = tmp;
            if (tmp > max) max = tmp;
        }
        return std::make_tuple(err / T, min, max);
    }

    std::vector<double> getErrorsVector (const Data& i_inp1, const Data& i_inp2, double (*i_localError)(const Column&, const Column&)) {
        std::vector<double> errorsVector;
        auto iter1 = i_inp1.begin(); 
        auto iter2 = i_inp2.begin();
        for (; iter1 != i_inp1.end() && iter2 != i_inp2.end(); ++iter1, ++iter2) {
            double  locError = i_localError(*iter1, *iter2);
            errorsVector.push_back(locError);
        }
        return errorsVector;
    }

    Matrix    formMatrix (const Data& i_inp, bool i_withOnes) {
            int T = i_inp.size();
            int N = i_inp[0].n_elem;

            Matrix    S(N, T);
            for (int t = 0; t < T; t++) 
                S.col(t) = i_inp[t];
            
            if (i_withOnes) {
                Row   ones = arma::ones<Row>(T);
                return  arma::join_cols (S, ones);
            } 
            return S;
        }
    Matrix  getCovMat(const Data& i_inp) {
        Matrix    X = formMatrix(i_inp);
        Column    mean(X.n_rows, arma::fill::zeros);
        // X.each_col([&mean](const auto& v){mean += v;});
        // mean /= (double)X.n_cols;
        // X.each_col([&mean](Column& v){v -= mean;});
        Matrix    covMat = X*X.t() / (double)X.n_cols;

        return covMat;
    }

    Matrix  pcaReduce (const Matrix& i_covMat, double i_criterion) {
        Matrix    eigVec;
        Column    eigVal;
        arma::eig_sym(eigVal, eigVec, i_covMat);

        Data      condidates;
        for (int i = 0; i < eigVal.n_elem; ++i) {
            if(eigVal[i] > i_criterion)
                condidates.push_back((Column)eigVec.col(i));
        }

        if (condidates.size() <= 0) throw std::runtime_error("reduced to null, choose another criterion");
        return fn::formMatrix(condidates);
    }
}