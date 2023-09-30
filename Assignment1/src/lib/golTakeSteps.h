/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include <memory>
#include <string>
#include <vector>

#include "golMyFunctions.h"
#ifndef golTakeSteps_h
#define golTakeSteps_h

/**
 * \file golMyFunctions.h
 * \brief Various Utilities.
 * \ingroup utilities
 */
namespace gol {

class GolTakeSteps {
public:
    GolTakeSteps();
    ~GolTakeSteps();
    GolTakeSteps(std::shared_ptr<GolStructure> const& grid);
    void StartFromFile();
    void Start();
    void TakeStep();
    void PrintGrid();
    void PrintOriginal();
    std::vector<std::vector<char>> ReturnVec();
    int GetRow();
    int GetCol();
    int GetCell();

private:
    int row_gol;
    int column_gol;
    int cells_gol;
    std::vector<std::vector<char>> vec_now;
    std::vector<std::vector<char>> vec_original;
    std::shared_ptr<GolStructure> gol_ptr;
};

}  // namespace gol

#endif
