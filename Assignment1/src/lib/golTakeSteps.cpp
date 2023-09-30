#include "golTakeSteps.h"

#include <stdio.h>
#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "golMyFunctions.h"

namespace gol {
GolTakeSteps::GolTakeSteps() {
    row_gol = 10;
    column_gol = 10;
    cells_gol = 0;
}

//-----------------------------------------------------------------------------
GolTakeSteps::~GolTakeSteps() {}

//-----------------------------------------------------------------------------
GolTakeSteps::GolTakeSteps(std::shared_ptr<GolStructure> const& grid) {
    gol_ptr = grid;
}

//-----------------------------------------------------------------------------
void GolTakeSteps::StartFromFile() {
    row_gol = gol_ptr->GetRow();
    column_gol = gol_ptr->GetCol();
    //cells_gol = gol_ptr->GetNumberCells();
    vec_original = gol_ptr->GetVec();
    vec_now = gol_ptr->GetVec();
}

//-----------------------------------------------------------------------------
void GolTakeSteps::Start() {
    row_gol = gol_ptr->GetRow();
    column_gol = gol_ptr->GetCol();
    cells_gol = gol_ptr->GetNumberCells();
    gol_ptr->SetGolStructure();
    gol_ptr->StartRandomly();
    vec_original = gol_ptr->GetVec();
    vec_now = gol_ptr->GetVec();
}

//-----------------------------------------------------------------------------

void GolTakeSteps::TakeStep() {
    // Generate the new grip after steps

    gol_ptr->ChangeGolstructure(vec_now);
    std::vector<std::vector<char>> vec_temp = gol_ptr->GetVec();

    for (int i = 0; i < row_gol; i++) {
        for (int j = 0; j < column_gol; j++) {
            int number = gol_ptr->CountAliveCell(i, j);
            char cur_cell = gol_ptr->GetCell(i, j);

            if (cur_cell == 'o' && (number == 2 || number == 3)) {
                vec_temp[i][j] = 'o';
            }
            else if (cur_cell == '-' && number == 3) {
                vec_temp[i][j] = 'o';
            }
            else {
                vec_temp[i][j] = '-';
            }
        }
    }

    vec_now = vec_temp;
}

//-----------------------------------------------------------------------------
void GolTakeSteps::PrintGrid() {
    for (int i = 0; i < row_gol; i++) {
        for (int j = 0; j < column_gol; j++) {
            std::cout << vec_now[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//-----------------------------------------------------------------------------
void GolTakeSteps::PrintOriginal() {
    for (int i = 0; i < row_gol; i++) {
        for (int j = 0; j < column_gol; j++) {
            std::cout << vec_original[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//-----------------------------------------------------------------------------
std::vector<std::vector<char>> GolTakeSteps::ReturnVec() {
    return vec_now;
}

//-----------------------------------------------------------------------------
int GolTakeSteps::GetRow() {
    return row_gol;
}

//-----------------------------------------------------------------------------
int GolTakeSteps::GetCol() {
    return column_gol;
}

//-----------------------------------------------------------------------------
int GolTakeSteps::GetCell() {
    return cells_gol;
}
}  // namespace gol