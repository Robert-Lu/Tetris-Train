//
// Created by luwuy on 2016/2/22 0022.
//

#ifndef TETRIS_EMULATOR_TETRISCEA_H
#define TETRIS_EMULATOR_TETRISCEA_H

#define TEST_CNT_PER_CASE 1
#define TEST_CNT_AFTER_ITER 3
#define FILE_SEPERATOR "/"

#define DEBUG  0
#define INFO   1
#define RESULT 2
#define ERROR  3

#define LOG_RATE DEBUG

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
            data_save_space(dsp), tetrisEmulator(te), generator(time(NULL))
	{
		logout = ofstream(data_save_space + FILE_SEPERATOR + "log", std::ios_base::out);
		logout << "LOG:\n";
		logout.flush();
	}

    typedef vector<double> WeightTestCase;

    void train(double (*noise)(int) = nullptr, // noise return noise_rate, normally from 0.5 to 0;
               int iteration_limit = 50, int total_sample_cnt = 100, int best_sample_cnt = 10
               );

private:
    int last_best_practice = 0;
    TetrisEmulator tetrisEmulator;
    std::default_random_engine generator;
    std::string data_save_space;
	ofstream logout;
    WeightTestCase mu, sigma;

    double normalDistribution(double mean, double stdd);

    void save(int);
	void save_best(int);
    int load();
	void log(std::string content, int rate);
};


#endif //TETRIS_EMULATOR_TETRISCEA_H
