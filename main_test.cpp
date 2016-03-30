#include <iostream>
#include "TetrisCEA.h"
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    TetrisEmulator tetrisEmulator;
    string dsv = "test_untitled";
    if (argc > 1)
    {
        dsv = argv[1];
    }
    TetrisCEA cea(dsv, tetrisEmulator);

	cea.train([](int i) {
		if (i > 30)
			return 0.0;
		return 0.33 * (30.0 - i) / 30.0; 
	});

    return 0;
}
