//
// Created by luwuy on 2016/2/21 0021.
//

#include "Tetromino.h"

#define ERROR_CODE -128

int TetrominoRotationCount[TetrominoTypeCount] = {2, 4, 4, 2, 2, 1, 4};

short TetrominoShape[TetrominoTypeCount][4][4][2] =
        {
                {
                        {{ 0, -1}, { 0,  0}, { 0,  1}, { 0,  2}},
                        {{-1,  0}, { 0,  0}, { 1,  0}, { 2,  0}},
                },     // I
                {
                        {{ 0, -1}, { 0,  0}, { 0,  1}, {-1,  1}},
                        {{-1, -1}, {-1,  0}, { 0,  0}, { 1,  0}},
                        {{ 0, -1}, { 1, -1}, { 0,  0}, { 0,  1}},
                        {{-1,  0}, { 0,  0}, { 1,  0}, { 1,  1}}
                },     // J
                {
                        {{ 0, -1}, { 0,  0}, { 0,  1}, { 1,  1}},
                        {{-1,  0}, { 0,  0}, { 1,  0}, {-1,  1}},
                        {{-1, -1}, { 0, -1}, { 0,  0}, { 0,  1}},
                        {{ 1, -1}, {-1,  0}, { 0,  0}, { 1,  0}}
                },     // L
                {
                        {{ 0, -1}, { 1, -1}, {-1,  0}, { 0,  0}},
                        {{ 0, -1}, { 0,  0}, { 1,  0}, { 1,  1}},
                },     // S
                {
                        {{-1, -1}, { 0, -1}, { 0,  0}, { 1,  0}},
                        {{ 1, -1}, { 0,  0}, { 1,  0}, { 0,  1}},
                },     // Z
                {
                        {{-1, -1}, { 0, -1}, {-1,  0}, { 0,  0}},
                },     // O
                {
                        {{ 0, -1}, {-1,  0}, { 0,  0}, { 1,  0}},
                        {{ 0, -1}, { 0,  1}, { 0,  0}, { 1,  0}},
                        {{ 0,  1}, {-1,  0}, { 0,  0}, { 1,  0}},
                        {{ 0, -1}, {-1,  0}, { 0,  0}, { 0,  1}},
                },     // T
        };

int TetrominoLeftBound[TetrominoTypeCount][4] =
        {
                {0, 1, ERROR_CODE, ERROR_CODE},
                {1, 1, 0, 1},
                {0, 1, 1, 1},
                {1, 0, ERROR_CODE, ERROR_CODE},
                {1, 0, ERROR_CODE, ERROR_CODE},
                {1, ERROR_CODE, ERROR_CODE, ERROR_CODE},
                {1, 0, 1, 1},
        };

int TetrominoRightBound[TetrominoTypeCount][4] =
        {
                {0, 2, ERROR_CODE, ERROR_CODE},
                {0, 1, 1, 1},
                {1, 1, 0, 1},
                {1, 1, ERROR_CODE, ERROR_CODE},
                {1, 1, ERROR_CODE, ERROR_CODE},
                {0, ERROR_CODE, ERROR_CODE, ERROR_CODE},
                {1, 1, 1, 0},
        };

int TetrominoUpperBound[TetrominoTypeCount][4] =
        {
                {1, 0, ERROR_CODE, ERROR_CODE},
                {1, 1, 1, 0},
                {1, 0, 1, 1},
                {1, 1, ERROR_CODE, ERROR_CODE},
                {1, 1, ERROR_CODE, ERROR_CODE},
                {1, ERROR_CODE, ERROR_CODE, ERROR_CODE},
                {1, 1, 0, 1},
        };

int TetrominoLowerBound[TetrominoTypeCount][4] =
        {
                {2, 0, ERROR_CODE, ERROR_CODE},
                {1, 0, 1, 1},
                {1, 1, 1, 0},
                {0, 1, ERROR_CODE, ERROR_CODE},
                {0, 1, ERROR_CODE, ERROR_CODE},
                {0, ERROR_CODE, ERROR_CODE, ERROR_CODE},
                {0, 1, 1, 1},
        };

int TetrominoHeight[TetrominoTypeCount][4] =
        {
                {4, 1, ERROR_CODE, ERROR_CODE},
                {3, 2, 3, 2},
                {3, 2, 3, 2},
                {2, 3, ERROR_CODE, ERROR_CODE},
                {2, 3, ERROR_CODE, ERROR_CODE},
                {2, ERROR_CODE, ERROR_CODE, ERROR_CODE},
                {2, 3, 2, 3},
        };