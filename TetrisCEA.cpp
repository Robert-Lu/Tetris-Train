//
// Created by luwuy on 2016/2/22 0022.
//

#include <iostream>
#include "TetrisCEA.h"

double TetrisCEA::normalDistribution(double mean, double stdd)
{
    std::normal_distribution<double> distribution(mean, stdd);
    return distribution(generator);
}

void TetrisCEA::train(double (*noise)(int), int iteration_limit, int total_sample_cnt, int best_sample_cnt)
{
    mu = WeightTestCase(FEATURE_COUNT, 0.0);
    sigma = WeightTestCase(FEATURE_COUNT, 5.0);

    int iteration;
    if ((iteration = load()) == -1)
    {
        iteration = 0;
    }
    else
    {
        ++iteration;
    }

    while (iteration < iteration_limit)
    {
        // get test cases.
        vector<WeightTestCase> mu_test;
        for (int i = 0; i < total_sample_cnt; ++i)
        {
            WeightTestCase testCase;
            for (int j = 0; j < FEATURE_COUNT; ++j)
            {
                testCase.push_back(normalDistribution(mu[j], sigma[j]));
            }
            mu_test.push_back(testCase);
        }

        // test each case.
        int step_limit = last_best_practice * 3 + 5000;

        typedef std::pair<int, TetrisResult> TestResultPair;
        vector<TestResultPair> test_results;    // vector of pairs of index and result.
                                                // used to sort and get the indices of best cases.
        for (int i = 0; i < total_sample_cnt; ++i)
        {
            TestResultPair pair;
            pair.first = i;
            int sum = 0;
            tetrisEmulator.updateWight(mu_test[i]);
            for (int j = 0; j < TEST_CNT_PER_CASE; ++j)
            {
                sum += tetrisEmulator.next(step_limit);
            }
            pair.second = sum / TEST_CNT_PER_CASE;
            test_results.push_back(pair);
            std::cout << i << "\t" << sum / TEST_CNT_PER_CASE << '\n';///
        }

        std::sort(test_results.begin(), test_results.end(),
                  [](const TestResultPair l, const TestResultPair r){ return l.second > r.second; });

        // update $mu and $sigma
        WeightTestCase next_mu(FEATURE_COUNT, 0), next_sigma(FEATURE_COUNT, 0);
        // $mu: update with mean of all mu in good cases.
        for (int k = 0; k < best_sample_cnt; ++k)
        {
            int index = test_results[k].first;
            for (int i = 0; i < FEATURE_COUNT; ++i)
            {
                next_mu[i] += mu_test[index][i] / best_sample_cnt;
            }
        }

        // evaluate performance
        int sum = 0;
        tetrisEmulator.updateWight(next_mu);
        for (int m = 0; m < TEST_CNT_AFTER_ITER; ++m)
        {
            sum += tetrisEmulator.next();
        }
        last_best_practice = sum / TEST_CNT_AFTER_ITER; // record the best practice.

        // $sigma: standard different of good cases.
        for (int k = 0; k < best_sample_cnt; ++k)
        {
            int index = test_results[k].first;
            for (int i = 0; i < FEATURE_COUNT; ++i)
            {
                next_sigma[i] += pow((mu_test[index][i] - next_mu[i]), 2.0) / best_sample_cnt;
            }
        }
        double noise_rate = 0;
        if (noise != nullptr)
        {
            noise_rate = noise(iteration);
        }
        for (int i = 0; i < FEATURE_COUNT; ++i)
        {
            next_sigma[i] = sqrt(next_sigma[i]) + noise_rate * next_mu[i];
        }
        mu = next_mu;
        sigma = next_sigma;

        save(iteration);

        // print information
        std::cout << "\nperformace:\t" << last_best_practice << "\n\n";

        iteration++;
    }
}

void TetrisCEA::save(int iteration)
{
    ofstream fout(data_save_space + "\\" + std::to_string(iteration), ios_base::out);
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        fout << mu[i] << '\t';
    }
    fout << '\n';
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        fout << sigma[i] << '\t';
    }
    fout.close();
    ofstream fout_best(data_save_space + "\\best", ios_base::out);
    fout_best << iteration << '\t'
              << last_best_practice << '\n';
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        fout_best << mu[i] << '\t';
    }
    fout_best << '\n';
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        fout_best << sigma[i] << '\t';
    }
    fout_best.close();
}

int TetrisCEA::load()
{
    ifstream fin(data_save_space + "\\best", ios_base::in);
    if (!fin)
    {
        return -1; // file not exist.
    }
    int iteration, best;
    fin >> iteration >> best;
    last_best_practice = best;
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        fin >> mu[i];
    }
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        fin >> sigma[i];
    }
    return iteration;
}
