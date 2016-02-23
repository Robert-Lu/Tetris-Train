cmake_minimum_required(VERSION 3.3)
project(Tetris_Emulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main_test.cpp TetrisEmulator.cpp TetrisEmulator.h Tetromino.h Tetromino.cpp TetrisCEA.cpp TetrisCEA.h)
add_executable(Tetris_Emulator ${SOURCE_FILES})