//
// Created by luwuy on 2016/2/22 0022.
//

#ifndef TETRIS_EMULATOR_TETRISCEA_H
#define TETRIS_EMULATOR_TETRISCEA_H

#define TEST_CNT_PER_CASE 3
#define TEST_CNT_AFTER_ITER 10

#include <fstream>
#include "TetrisEmulator.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using std::vector;
using std::ofstream;
using std::ifstream;
using std::ios_base;

class TetrisCEA
{
public:
    TetrisCEA(std::string dsp, TetrisEmulator te):
            data_save_space(dsp), tetrisEmulator(te) {  }

    typedef vector<double> WeightTestCase;

    void train(double (*noise)(int) = nullptr, // noise return noise_rate, normally from 0.5 to 0;
               int iteration_limit = 50, int total_sample_cnt = 100, int best_sample_cnt = 10
               );

private:
    int last_best_practice = 0;
    TetrisEmulator tetrisEmulator;
    std::default_random_engine generator;
    std::string data_save_space;
    WeightTestCase mu, sigma;

    double normalDistribution(double mean, double stdd);

    void save(int);
    int load();
};


#endif //TETRIS_EMULATOR_TETRISCEA_H
