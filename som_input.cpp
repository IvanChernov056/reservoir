#include    "som_input.h"


namespace nn {

    namespace {
        double  dist (int i1, int i2, int N) {
            return (i1 - i2 + N) % N;
        }

        Column_t calc_map (int i_idx, double i_disp, int N) {
            Column_t map(N);
            for (int i = 0; i < N; ++i) 
                map[i] = (i != i_idx) ? exp (-dist(i, i_idx, N)/i_disp) : 1;
            return map;
        }
    }


    SomInp::SomInp(int i_in, int i_d, int i_out) {
        d_w1 = arma::randn<Matrix_t> (i_d, i_in);
        d_w2 = arma::randn<Matrix_t> (i_out, i_d);
    }

    Column_t SomInp::operator()(const Column_t& i_x) {
        Column_t h = d_w1*i_x;
        Column_t y = d_w2*h;
        // std::cout << "operator ok\n";
        return y;
    }

    bool  SomInp::fit (const Data_t& i_inp, int i_iterations) {
        double  speed = 0.01;
        double  rd_sp = 0.8;
        double  disp  = 10;
        double  rd_dsp= 0.5;

        for (int iter = 0; iter < i_iterations; ++iter) {
            for (const auto& v : i_inp) {
                // std::cout << "?>n";
                Column_t h = d_w1*v;
                // std::cout << "?<n";
                int idx_max = h.index_max();

                Column_t    map = calc_map(idx_max, disp, h.n_elem);

                for (int i = 0; i < d_w1.n_rows; ++i) {
                    d_w1.row(i) += speed*map[i]*(v.t() - d_w1.row(i));
                }

            }

            disp *= rd_dsp;
            speed *= rd_sp;
            std::cout << "iter : " << iter +1 << '\n';
        }
    }
}