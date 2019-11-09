#include    "som_layer.h"


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


    SomLayer::SomLayer(int i_in, int i_d, int i_out) : SimpleLayer(i_d, i_out), d_d(i_d) {
        d_w2 = arma::randn<Matrix_t> (i_d, i_in);
    }

    SomLayer::SomLayer(int i_d, int i_neuronsCount) : 
        SimpleLayer(i_d, i_neuronsCount), d_d(i_d) {}

    Column_t SomLayer::operator()(const Column_t& i_x) {
        Column_t h = d_w2*i_x;
        return SimpleLayer::operator()(h);
    }

    bool  SomLayer::fit (const Data_t& i_inp, int i_iterations) {
        try {
            if (i_inp.empty()) throw std::runtime_error("input data is empty");
            d_w2 = arma::randn<Matrix_t>(d_d, i_inp[0].n_elem);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }

        double  speed = 0.01;
        double  rd_sp = 0.8;
        double  disp  = 10;
        double  rd_dsp= 0.5;

        for (int iter = 0; iter < i_iterations; ++iter) {
            for (const auto& v : i_inp) {
                // std::cout << "?>n";
                Column_t h = d_w2*v;
                // std::cout << "?<n";
                int idx_max = h.index_max();

                Column_t    map = calc_map(idx_max, disp, h.n_elem);

                for (int i = 0; i < d_w2.n_rows; ++i) {
                    d_w2.row(i) += speed*map[i]*(v.t() - d_w2.row(i));
                }

            }

            disp *= rd_dsp;
            speed *= rd_sp;
            if (iter % 100 == 0)
                std::cout << "iter : " << iter+1 << " / " << i_iterations << '\n';
        }
        std::cout << "last iter : " << i_iterations << " / " << i_iterations << '\n';

        return true;
    }
}