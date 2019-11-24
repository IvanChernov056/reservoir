#include    "som_layer.h"


namespace nn {

    namespace {
        double  dist (int i1, int i2, int N) {
            return (i1 - i2 + N) % N;
        }

        Column calc_map (int i_idx, double i_disp, int N) {
            Column map(N);
        // #pragma omp parallel for
            for (int i = 0; i < N; ++i) {
                map[i] = (i != i_idx) ? exp (-dist(i, i_idx, N)/i_disp) : 1;
            }
            return map;
        }
    }


    SomLayer::SomLayer(int i_in, int i_out) : SimpleLayer(i_in, i_out) 
        {}

    SomLayer::SomLayer(int i_neuronsCount) : SimpleLayer(i_neuronsCount)
        {}

    bool  SomLayer::fit (const Data& i_inp, int i_iterations) {
        if (!SimpleLayer::fit(i_inp, i_iterations)) return false;

        double  speed = 0.01;
        double  rd_sp = 0.8;
        double  disp  = 10;
        double  rd_dsp= 0.5;

        for (int iter = 0; iter < i_iterations; ++iter) {
            for (const auto& v : i_inp) {
                Column h = d_w*v;
                int idx_max = h.index_max();

                Column    map = calc_map(idx_max, disp, h.n_elem);

            // #pragma omp parallel for
                for (int i = 0; i < d_w.n_rows; ++i) {
                    d_w.row(i) += speed*map[i]*(v.t() - d_w.row(i));
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