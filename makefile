TetrisTrain : main_test.o TetrisEmulator.o Tetromino.o TetrisCEA.o
	g++ -o TetrisTrain main_test.o TetrisEmulator.o Tetromino.o TetrisCEA.o -std=c++11

main_test.o : main_test.cpp TetrisCEA.h
	g++ -c main_test.cpp -std=c++11

TetrisEmulator.o : TetrisEmulator.cpp TetrisEmulator.h
	g++ -c TetrisEmulator.cpp -std=c++11

Tetromino.o : Tetromino.cpp Tetromino.h
	g++ -c Tetromino.cpp -std=c++11

TetrisCEA.o : TetrisCEA.cpp TetrisCEA.h
	g++ -c TetrisCEA.cpp -std=c++11

clean :
	rm main_test.o TetrisEmulator.o Tetromino.o TetrisCEA.o
