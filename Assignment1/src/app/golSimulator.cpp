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
#include <time.h>
#include <random>

void help_info() {
    std::cerr << "This is the help information of game of life" << std::endl;
    std::cerr << "You can input the parameters like 1 or 2" << std::endl;
    std::cerr << "1."
              << "rows, columns and steps" << std::endl;
    std::cerr << "2."
              << "rows, columns, number of alive cells and steps" << std::endl;
    std::cerr << "if you want to load a text file (.txt), you can input the parameters like 3" << std::endl;
    std::cerr << "3."
              << "text file (.txt) path and steps" << std::endl;
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
    if (argc == 3) {
        int steps = std::stoi(argv[2]);

        std::string path = argv[1];
        std::shared_ptr<gol::GolStructure> gol_ptr = std::make_shared<gol::GolStructure>(path);
        gol::GolTakeSteps gol_steps(gol_ptr);
        gol_steps.StartFromFile();

        for (int i = 0; i < steps + 1; ++i) {
            std::cout << "This is step " << i << std::endl;
            gol_steps.PrintGrid();
            gol_steps.TakeStep();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    if (argc == 4) {
        int rows = std::stoi(argv[1]);
        int columns = std::stoi(argv[2]);
        int steps = std::stoi(argv[3]);

        std::shared_ptr<gol::GolStructure> gol_ptr = std::make_shared<gol::GolStructure>(rows, columns);
        gol::GolTakeSteps gol_steps(gol_ptr);
        srand((unsigned)time(NULL));
        gol_steps.Start();
        int cells = gol_steps.GetCell();
        std::cout << "randomly " << cells << " alive cells" << std::endl;

        for (int i = 0; i < steps + 1; i++) {
            std::cout << "This is step " << i << std::endl;
            gol_steps.PrintGrid();
            gol_steps.TakeStep();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    if (argc == 5) {
        int rows = std::stoi(argv[1]);
        int columns = std::stoi(argv[2]);
        int cells = std::stoi(argv[3]);
        int steps = std::stoi(argv[4]);

        std::shared_ptr<gol::GolStructure> gol_ptr = std::make_shared<gol::GolStructure>(rows, columns, cells);
        gol::GolTakeSteps gol_steps(gol_ptr);
        srand((unsigned)time(NULL));
        gol_steps.Start();
        for (int i = 0; i < steps + 1; i++) {
            std::cout << "This is step " << i << std::endl;
            gol_steps.PrintGrid();
            gol_steps.TakeStep();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    return 0;
}
