/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golMyFunctions.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace gol {

GolStructure::GolStructure() {
    row_gol = 10;
    column_gol = 10;
    cells_gol = 0;
}

//-----------------------------------------------------------------------------
GolStructure::GolStructure(const int& rows, const int& columns) {
    // One of the constructors when the inputs are row and column numbers

    if (rows <= 1 || columns <= 1) {
        throw std::invalid_argument("Input should be larger than 1");
    }

    if (typeid(rows) != typeid(int) || typeid(columns) != typeid(int)) {
        throw std::invalid_argument("Input should be integers");
    }

    row_gol = rows;
    column_gol = columns;
    cells_gol = rand() % (rows * columns);
}

//-----------------------------------------------------------------------------
GolStructure::GolStructure(const int& rows, const int& columns, const int& cells) {
    // One of the constructors when the inputs are row and column numbers

    if (rows <= 1 || columns <= 1 || cells < 0) {
        throw std::invalid_argument("Rows and Columns should be larger than 1, number of cells should be larger than 0");
    }

    if (typeid(rows) != typeid(int) || typeid(columns) != typeid(int) || typeid(cells) != typeid(int)) {
        throw std::invalid_argument("Input shoule be integers");
    }
    row_gol = rows;
    column_gol = columns;
    cells_gol = cells;
}

//-----------------------------------------------------------------------------
GolStructure::GolStructure(std::string& path) {
    std::ifstream infile(path);
    std::vector<std::vector<char>> result;
    if (infile) {
        std::string line;
        while (getline(infile, line, '\n')) {
            std::vector<char> tempvec;
            std::stringstream ss(line);
            char word;
            while (ss >> word) {
                tempvec.push_back(word);
            }
            result.emplace_back(tempvec);
        }
        if (result.empty()) {
            throw std::invalid_argument("file is empty");
        }
    }

    else {
        throw std::invalid_argument("file cannot be opened");
    }

    row_gol = result.size();
    column_gol = result[0].size();
    vec_GolStructure = result;
}

//-----------------------------------------------------------------------------
GolStructure::~GolStructure() {}

//-----------------------------------------------------------------------------
void GolStructure::SetGolStructure() {
    std::vector<std::vector<char>> vec_balnk(row_gol, std::vector<char>(column_gol, '-'));
    vec_GolStructure = vec_balnk;
}

//-----------------------------------------------------------------------------
void GolStructure::StartRandomly() {
    // Randomly set the cells

    for (int i = 0; i < cells_gol; i++) {
        int rand_row = rand() % (row_gol);
        int rand_col = rand() % (column_gol);

        // check if the selected cell is alive

        if (vec_GolStructure[rand_row][rand_col] == 'o') {
            i--;
            continue;
        }
        else {
            vec_GolStructure[rand_row][rand_col] = 'o';
        }
    }
}

//-----------------------------------------------------------------------------
void GolStructure::ChangeGolstructure(std::vector<std::vector<char>> vec) {
    vec_GolStructure = vec;
}

//-----------------------------------------------------------------------------
int GolStructure::CountAliveCell(int row, int col) {
    // Return the number of alive neighbours
    if (row < 0 || col < 0) {
        throw std::invalid_argument("Input should be larger than 1");
    }

    if (typeid(row) != typeid(int) || typeid(col) != typeid(int)) {
        throw std::invalid_argument("Input should be integers");
    }

    if (row >= row_gol || col >= column_gol) {
        throw std::invalid_argument("Input should be smaller than the size of GolStructure");
    }

    int num = 0;

    // check the number of live neighbours

    // check the upper neighbours
    if (row > 0 && vec_GolStructure[row - 1][col] == 'o') {
        ++num;
    }

    // check the lower neighbours
    if (row < row_gol - 1 && vec_GolStructure[row + 1][col] == 'o') {
        ++num;
    }

    // check the left neighbours
    if (col > 0 && vec_GolStructure[row][col - 1] == 'o') {
        ++num;
    }

    // check the right neighbours
    if (col < column_gol - 1 && vec_GolStructure[row][col + 1] == 'o') {
        ++num;
    }

    // check the upper left neighbours
    if (row > 0 && col > 0 && vec_GolStructure[row - 1][col - 1] == 'o') {
        ++num;
    }

    // check the upper right neighbours
    if (row > 0 && col < column_gol - 1 && vec_GolStructure[row - 1][col + 1] == 'o') {
        ++num;
    }
    // check the lower left neighbours
    if (row < row_gol - 1 && col > 0 && vec_GolStructure[row + 1][col - 1] == 'o') {
        ++num;
    }

    // check the lower right neighbours
    if (row < row_gol - 1 && col < column_gol - 1 && vec_GolStructure[row + 1][col + 1] == 'o') {
        ++num;
    }
    return num;
}
//-----------------------------------------------------------------------------
void GolStructure::PrintGolStructure() {
    // display the grid

    for (int i = 0; i < row_gol; i++) {
        for (int j = 0; j < column_gol; j++) {
            std::cout << vec_GolStructure[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//-----------------------------------------------------------------------------
char GolStructure::GetCell(int row, int col) {
    // Get the status of the input coordinate
    if (row < 0 || col < 0) {
        throw std::invalid_argument("Input should be larger than 1");
    }

    if (typeid(row) != typeid(int) || typeid(col) != typeid(int)) {
        throw std::invalid_argument("Input shoule be integers");
    }

    if (row >= row_gol || col >= column_gol) {
        throw std::invalid_argument("Input should be smaller than the size of GolStructure");
    }

    if (vec_GolStructure[row][col] == 'o') {
        return 'o';
    }
    else {
        return '-';
    }
}

//-----------------------------------------------------------------------------
void GolStructure::SetCell(int row, int col, char cell) {
    if (row < 0 || col < 0) {
        throw std::invalid_argument("Input should be larger than 1");
    }

    if (typeid(row) != typeid(int) || typeid(col) != typeid(int)) {
        throw std::invalid_argument("Input shoule be integers");
    }

    if (row >= row_gol || col >= column_gol) {
        throw std::invalid_argument("Input should be smaller than the size of GolStructure");
    }

    if (cell == 'o' && vec_GolStructure[row][col] == '-') {
        vec_GolStructure[row][col] = 'o';
    }
    if (cell == '-' && vec_GolStructure[row][col] == 'o') {
        vec_GolStructure[row][col] = '-';
    }
}

//-----------------------------------------------------------------------------
std::vector<std::vector<char>> GolStructure::GetVec() {
    return vec_GolStructure;
}

//-----------------------------------------------------------------------------
int GolStructure::GetRow() {
    return row_gol;
}

//-----------------------------------------------------------------------------
int GolStructure::GetCol() {
    return column_gol;
}

//-----------------------------------------------------------------------------
int GolStructure::GetNumberCells() {
    return cells_gol;
}

}  // namespace gol