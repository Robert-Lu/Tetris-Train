//
// Created by luwuy on 2016/2/21 0021.
//

#ifndef TETRIS_EMULATOR_TETRISEMULATOR_H
#define TETRIS_EMULATOR_TETRISEMULATOR_H

#include "Tetromino.h"
#include <string>
#include <random>
#include <vector>
#include <ctime>

#define T_HEIGHT 20
#define T_WIDTH  10
#define FEATURE_COUNT 21
#define NO_LIMIT 2147483647

typedef int TetrisResult;
typedef double TetrisValue;
typedef double TetrisWeight[FEATURE_COUNT];
typedef bool TetrisBoard[T_WIDTH][T_HEIGHT];

class TetrisEmulator
{
public:
    TetrisEmulator()
    {
        //srandom((unsigned)time(NULL));
    }

    void updateWight(std::vector<double> w)
    {
        for (int i = 0; i < FEATURE_COUNT; ++i)
        {
            weight[i] = w[i];
        }
    }

    TetrisResult next()
    {
        return emulate(NO_LIMIT);
    }

    TetrisResult next(int step_limit)
    {
        return emulate(step_limit);
    }

private:
    TetrisWeight weight;
    TetrisBoard board;
    TetrisBoard board_temp;
    int lastMaxHeight;
    double lastLandingHeight;
    int step;
    int lastClearLines;
	std::default_random_engine generator;

    void init_board(TetrisBoard board);

    void log();

    bool fail();

    int getMaxHeight(TetrisBoard);

    void cloneBoard(TetrisBoard, TetrisBoard);

    int drop(TetrisBoard, TetrominoType, int r, int x);

    void printBoard(TetrisBoard); // TEST ONLY
    void showFeatures(TetrisBoard); // TEST ONLY

    TetrisResult emulate(int step_limit);

    TetrisValue getValue(TetrisBoard b);

	void getFeature(double *, TetrisBoard b);

    bool isFullLine(TetrisBoard b, int y);

    void downLinesFrom(TetrisBoard b, int y);

    int getRowTransition(TetrisBoard);

    int getColTransition(TetrisBoard);

    int getHoleDepth(TetrisBoard);

	int getHoleCount(TetrisBoard b);

    int getCumulativeWells(TetrisBoard);

	TetrominoType randType();
};


#endif //TETRIS_EMULATOR_TETRISEMULATOR_H
