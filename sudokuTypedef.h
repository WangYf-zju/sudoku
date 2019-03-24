#pragma once
#ifndef __SUDOKUTYPEDEF_H__
#define __SUDOKUTYPEDEF_H__
#include "sudokuConstant.h"

typedef unsigned short int sudokuVar;
// Record number in sudoku.
typedef sudokuVar sudoku[Raw][Column];
// An assisted array, to mark which numbers can be filled in each block.
// In this array, each bit stands for a number.
// 0 stands for the number cannot be filled in the current block,
// 1 stands for the number can be filled in the current block.
typedef sudokuVar sudokuMark[Raw][Column];

#endif