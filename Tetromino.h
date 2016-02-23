//
// Created by luwuy on 2016/2/21 0021.
//

#ifndef TETRIS_EMULATOR_TETROMINO_H
#define TETRIS_EMULATOR_TETROMINO_H

#define TetrominoTypeCount      7

enum TetrominoType
{
    I, J, L, S, Z, O, T
};

extern int TetrominoRotationCount[TetrominoTypeCount];

typedef short (*Shape)[2];

extern short TetrominoShape[TetrominoTypeCount][4][4][2];

extern int TetrominoLeftBound[TetrominoTypeCount][4];
extern int TetrominoRightBound[TetrominoTypeCount][4];
extern int TetrominoUpperBound[TetrominoTypeCount][4];
extern int TetrominoLowerBound[TetrominoTypeCount][4];
extern int TetrominoHeight[TetrominoTypeCount][4];

#endif //TETRIS_EMULATOR_TETROMINO_H
