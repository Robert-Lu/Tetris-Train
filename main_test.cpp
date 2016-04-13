#include <iostream>
#include "TetrisCEA.h"
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    TetrisEmulator tetrisEmulator;
    string dsv = "test_unti tled";
    if (argc > 1)
    {
        dsv = argv[1];
    }
    TetrisCEA cea(dsv, tetrisEmulator);

	cea.train([](int i) {
		return 0.5;
	});

    return 0;
}
