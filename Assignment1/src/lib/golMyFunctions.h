/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include <string>
#include <vector>
#ifndef golMyFunctions_h
#define golMyFunctions_h

/**
 * \file golMyFunctions.h
 * \brief Various Utilities.
 * \ingroup utilities
 */
namespace gol {

class GolStructure {
public:
    GolStructure();
    GolStructure(const int& rows, const int& columns);
    GolStructure(const int& rows, const int& columns, const int& cells);
    GolStructure(std::string& path);
    ~GolStructure();
    void StartRandomly();
    void SetGolStructure();
    void ChangeGolstructure(std::vector<std::vector<char>> vec);
    void SetCell(int row, int col, char cell);
    char GetCell(int row, int col);
    void PrintGolStructure();
    int CountAliveCell(int row, int col);
    std::vector<std::vector<char>> GetVec();
    int GetRow();
    int GetCol();
    int GetNumberCells();

private:
    int row_gol;
    int column_gol;
    int cells_gol;
    std::vector<std::vector<char>> vec_GolStructure;
};

}  // namespace gol

#endif
