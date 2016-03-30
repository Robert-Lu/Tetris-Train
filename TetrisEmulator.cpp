//
// Created by luwuy on 2016/2/21 0021.
//

#include "TetrisEmulator.h"
#include <iostream> // TEST

#define NEG_INF -9E99
#define ASSERT(x, v, c) if((x)!=(v)) exit(c);

TetrominoType TetrisEmulator::randType()
{
	std::uniform_int_distribution<int> distribution(0, 6);
    return (TetrominoType) (distribution(generator));
}

void TetrisEmulator::init_board(TetrisBoard board)
{
    for (int i = 0; i < T_WIDTH; ++i)
    {
        for (int j = 0; j < T_HEIGHT; ++j)
        {
            board[i][j] = false;
        }
    }
}

int TetrisEmulator::getMaxHeight(TetrisBoard b)
{
    for (int y = 0; y < T_HEIGHT; ++y)
    {
        for (int x = 0; x < T_WIDTH; ++x)
        {
            if (b[x][y])
            {
                lastMaxHeight = T_HEIGHT - y;
                return lastMaxHeight;
            }
        }
    }
    lastMaxHeight = 0;
    return 0;
}

void TetrisEmulator::cloneBoard(TetrisBoard d, TetrisBoard s)
{
    for (int i = 0; i < T_WIDTH; ++i)
    {
        for (int j = 0; j < T_HEIGHT; ++j)
        {
            d[i][j] = s[i][j];
        }
    }
}

TetrisResult TetrisEmulator::emulate(int step_limit)
{
    step = 0;
    lastMaxHeight = 0;
    init_board(board);
    while (!fail())
    {
        TetrominoType type = randType();
        // For each rotation of the certain type.
        int bestRotation = -1;
        int bestX = T_WIDTH / 2;
        double bestValue = NEG_INF;
        for (int rotation = 0; rotation < TetrominoRotationCount[type]; ++rotation)
        {
            // for each possible drop position of the certain type and rotation.
            for (int x = TetrominoLeftBound[type][rotation];
                 x < T_WIDTH - TetrominoRightBound[type][rotation]; ++x)    // right bound is positive offset.
            {
                cloneBoard(board_temp, board); // TODO : potential efficiency enhancement point.
                if ((lastClearLines = drop(board_temp, type, rotation, x)) < 0)
                {
                    continue;
                }
                TetrisValue value = getValue(board_temp);
                if (value > bestValue)
                {
                    bestValue = value;
                    bestRotation = rotation;
                    bestX = x;
                }
            }
        }
        if (bestRotation == -1 || step >= step_limit)
        {
            break;
        }
		//if (_DEBUG) // debug-time only.
		//{
		//	printBoard(board);
		//	std::cout << getHoleDepth(board);
		//}
        drop(board, type, bestRotation, bestX);
        getValue(board);
        step++;
//		printBoard(board);
    }
    return step;
}


void TetrisEmulator::log()
{
    return; // TODO
}

bool TetrisEmulator::fail()
{
    return getMaxHeight(board) > T_HEIGHT;
}

#define WITHIN(m, x, M) (((x) >= (m)) && ((x) < (M)))

bool check(TetrisBoard b, Shape s, int x, int y)
{
    for (int i = 0; i < 4; ++i)
    {
        int xi = x + s[i][0];
        int yi = y + s[i][1];
        if (!WITHIN(0, xi, T_WIDTH) || !WITHIN(0, yi, T_HEIGHT))
        {
            return false;
        }
        if (b[xi][yi])
        {
            return false;
        }
    }
    return true;
}

int TetrisEmulator::drop(TetrisBoard b, TetrominoType type, int r, int x)
{
    Shape s = TetrominoShape[type][r];
    int y = TetrominoUpperBound[type][r];
    bool suc_flag = false;
    while (true)
    {
        if (check(b, s, x, y))
        {
            suc_flag = true;
            y++;
        }
        else
        {
            if (suc_flag)
            {
                y--;
                break;
            }
            else
            {
                return -1;
            }
        }
    }
	lastLandingHeight = (T_HEIGHT - 1 - y) - TetrominoLowerBound[type][r]
                        + TetrominoHeight[type][r] * 1.0 / 2;
    for (int i = 0; i < 4; ++i)
    {
        ASSERT(b[x + s[i][0]][y + s[i][1]], false, 127);
        b[x + s[i][0]][y + s[i][1]] = true;
    }
    int clear = 0;
    for (int yi = T_HEIGHT - 1; yi >= 0; --yi)
    {
        while (isFullLine(b, yi))
        {
            downLinesFrom(b, yi);
            clear++;
        }
    }
    return clear;
}


void TetrisEmulator::printBoard(TetrisBoard board)
{
    for (int i = 0; i < T_HEIGHT; ++i)
    {
        for (int j = 0; j < T_WIDTH; ++j)
        {
            std::cout << ((board[j][i]) ? "[]" : "  ");
        }
        std::cout << "." << std::endl;
    }
    std::cout << "_____________________" << std::endl;
}

TetrisValue TetrisEmulator::getValue(TetrisBoard b)
{
    double feature[FEATURE_COUNT] =
            {
                    lastLandingHeight,
                    (double)lastClearLines,
                    (double)getRowTransition(b),
                    (double)getColTransition(b),
                    (double)getHoleDepth(b),
                    (double)getCumulativeWells(b),
            };

    double v = 0;
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
//        std::cout << feature[i] << '\n';
        v += feature[i] * weight[i];
    }
    return v;
}

void TetrisEmulator::showFeatures(TetrisBoard b)
{
    double feature[FEATURE_COUNT] =
            {
                    lastLandingHeight,
                    (double)lastClearLines,
                    (double)getRowTransition(b),
                    (double)getColTransition(b),
                    (double)getHoleCount(b),
                    (double)getHoleDepth(b),
                    (double)getCumulativeWells(b),
            };
    for (int i = 0; i < FEATURE_COUNT; ++i)
    {
        std::cout << feature[i] << '\n';
    }
}

bool TetrisEmulator::isFullLine(TetrisBoard b, int y)
{
    for (int i = 0; i < T_WIDTH; ++i)
    {
        if (!b[i][y])
        {
            return false;
        }
    }
    return true;
}

void TetrisEmulator::downLinesFrom(TetrisBoard b, int y)
{
    bool flag;
    for (int yi = y; yi >= 1; --yi)
    {
        flag = false;
        for (int x = 0; x < T_WIDTH; ++x)
        {
            flag |= b[x][yi] = b[x][yi - 1];
        }
        if (!flag)
        {
            break;
        }
    }
    for (int x = 0; x < T_WIDTH; ++x)
    {
        b[x][0] = false;
    }
}

int TetrisEmulator::getRowTransition(TetrisBoard b)
{
    int trans = 0;
    for (int y = 0; y < T_HEIGHT; ++y)
    {
        bool flag = true;
        for (int x = 0; x < T_WIDTH; ++x)
        {
            if (b[x][y] != flag)
            {
                flag = !flag;
                trans++;
            }
        }
        if (!flag)
        {
            trans++;
        }
    }
    return trans;
}

int TetrisEmulator::getColTransition(TetrisBoard b)
{
    int trans = 0;
    for (int x = 0; x < T_WIDTH; ++x)
    {
        bool flag = false;
        for (int y = 0; y < T_HEIGHT; ++y)
        {
            if (b[x][y] != flag)
            {
                flag = !flag;
                trans++;
            }
        }
        if (!flag)
        {
            trans++;
        }
    }
    return trans;
}

int TetrisEmulator::getHoleDepth(TetrisBoard b)
{
	int cnt = 0;
	for (int x = 0; x < T_WIDTH; ++x)
	{
		bool covered = false;
		int depth = 0;
		for (int y = 0; y < T_HEIGHT; ++y)
		{
			if (!covered && b[x][y])
			{
				covered = true;
			}
			else if (covered)
			{
				depth++;
				if (!b[x][y])
				{
					cnt += depth;
				}
			}
		}
	}
	return cnt;
}
int TetrisEmulator::getHoleCount(TetrisBoard b)
{
	int cnt = 0;
	for (int x = 0; x < T_WIDTH; ++x)
	{
		bool covered = false;
		for (int y = 0; y < T_HEIGHT; ++y)
		{
			if (!covered && b[x][y])
			{
				covered = true;
			}
			else if (covered)
			{
				if (!b[x][y])
				{
					cnt += 1;
				}
			}
		}
	}
	return cnt;
}

int TetrisEmulator::getCumulativeWells(TetrisBoard b)
{
    int rate;
    int sum = 0;
    for (int y = 0; y < T_HEIGHT; ++y)
    {
        if (b[1][y] && !b[0][y])
        {
            rate = 1;
            while(y < T_HEIGHT && !b[0][y++])
            {
                sum += rate;
                rate++;
            }
            break;
        }
    }
    int x0 = T_WIDTH - 1;
    for (int y = 0; y < T_HEIGHT; ++y)
    {
        if (b[x0 - 1][y] && !b[x0][y])
        {
            rate = 1;
            while(y < T_HEIGHT && !b[x0][y++])
            {
                sum += rate;
                rate++;
            }
            break;
        }
    }

    for (int x = 1; x < T_WIDTH - 1; ++x)
    {
        for (int y = 0; y < T_HEIGHT; ++y)
        {
            if (b[x-1][y] && b[x+1][y] && !b[x][y])
            {
                rate = 1;
                while(y < T_HEIGHT && !b[x][y++])
                {
                    sum += rate;
                    rate++;
                }
                continue;
            }
        }
    }
    return sum;
}
