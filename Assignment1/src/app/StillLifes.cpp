/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include <golExceptionMacro.h>
#include <golMyFunctions.h>
#include <golTakeSteps.h>
#include <stdlib.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

void help_info() {
    std::cerr << "This is the help information of finding still life for game of life" << std::endl;
    std::cerr << "You can input the parameters like:" << std::endl;
    std::cerr << "rows, columns, number of alive cells, maximum iterations and number of different initial conditions" << std::endl;
}

int main(int argc, char* argv[]) {
    // check the number of the input and response based on differnet number

    if (argc == 1) {
        help_info();
    }
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        help_info();
        std::cerr << "You can input --help or -h to check the information again" << std::endl;
    }
    if (argc == 6) {
        int rows = std::stoi(argv[1]);
        int columns = std::stoi(argv[2]);
        int cells = std::stoi(argv[3]);
        int iterations = std::stoi(argv[4]);
        int cases = std::stoi(argv[5]);

        srand((unsigned int)time(NULL));
        for (int i = 0; i < cases; i++) {
            std::shared_ptr<gol::GolStructure> gol_ptr = std::make_shared<gol::GolStructure>(rows, columns, cells);
            gol::GolTakeSteps gol_steps(gol_ptr);
            gol_steps.Start();
            std::vector<std::vector<char>> vec_start = gol_steps.ReturnVec();
            std::vector<std::vector<char>> vec_invalid(rows, std::vector<char>(columns, '-'));
            for (int j = 0; j < iterations; j++) {
                std::vector<std::vector<char>> vec_before = gol_steps.ReturnVec();
                gol_steps.TakeStep();
                std::vector<std::vector<char>> vec_after = gol_steps.ReturnVec();


                if (vec_start == vec_invalid) {
                    std::cerr << "This case is invalid because there are no alive cells" << std::endl;
                    std::cerr << "Begin next case" << std::endl;
                    std::cerr << "------------------------------" << std::endl;
                    break;
                }

                if (vec_after == vec_before) {
                    std::cerr << "The game started at case " << i + 1 << ":" << std::endl;
                    gol_steps.PrintOriginal();
                    std::cerr << "" << std::endl;
                    std::cerr << "The game get still unchanged at case " << i + 1 << " at " << j + 1 << " iterations:" << std::endl;
                    gol_steps.PrintGrid();
                    std::cerr << "------------------------------" << std::endl;
                    break;
                }

                if (j == iterations - 1) {
                    std::cerr << "The game started at case " << i + 1 << ":" << std::endl;
                    gol_steps.PrintOriginal();
                    std::cerr << "The game is not stable in case " << i + 1 << std::endl;
                    std::cerr << "The game get still changed at case " << i + 1 << " at maximum iterations:" << std::endl;
                    gol_steps.PrintGrid();
                    std::cerr << "Move to the next case" << std::endl;
                    std::cerr << "------------------------------" << std::endl;
                }
            }
        }
    }
    return 0;
}