#pragma once
#ifndef __SUDOKU_H__
#define __SUDOKU_H__
#include "sudokuStack.h"
#include "sudokuTypedef.h"
#include "sudokuConstant.h"

// To initalize the assisted array
void InitalizeMark(const sudoku sdk, sudokuMark sMark);

// To fill all only-solution blocks
// Function run in loop until no such blocks were found
void FillUniqueSolutionBlocks(sudoku sdk, sudokuMark sMark);

// To update the assisted array
// Call this function when add a number to sudoku array
void FillMark(sudokuMark sMark, const int x, const int y, const sudokuVar var);

// To check if no-solution block exists
// Function return FALSE when current suduko array cannot be solved
int CheckPracticability(const sudoku sdk, const sudokuMark sMark);

// To check if current sudoku array has been solved
// Function return TRUE when solved
// Function return FALSE when not solved
int CheckIsSolved(const sudoku sdk);

// To read data from sudoku stack
// Call function to recovery data to previous state if current try cause no solution
void RecoveryData(sudoku sdk, sudokuMark sMark, psudokuStack stck);

// To select a indefinite-solution block and try filling the block with a number
// Function disable to fill try block with try number
// Then function push current sudoku state to stack
// Then function update sudoku array and assisted array
void Try(sudoku sdk, sudokuMark sMark, psudokuStack stck);

// To disable to fill block [x][y] with value of parameter var
void DisableValue(sudokuMark sMark, const int x, const int y, const sudokuVar var);

// Primary function
// Parameter sdk should be format to 2 exponential form
// Call function TransDecToSudokuVar() to format sudoku variable
// Function return FALSE when no solution found
// Call function TransSudokuVarToDec to format sudoku to decimal form
int Solve(sudoku sdk);

// To transform suduku data from 2 exponential form to decimal form
void TransSudokuVarToDec(sudoku sdk);

// To transform suduku data from decimal form to 2 exponential form
void TransDecToSudokuVar(sudoku dec);

// To generate a sudoku puzzle randomly
void GenerateSudoku(sudoku sdk);
#endif