#pragma once
#ifndef __SUDOKUSTACK_H__
#define __SUDOKUSTACK_H__
#include "sudokuTypedef.h"

typedef struct sudokuStackElement
{
	sudoku sdk;							// sudoku array
	sudokuMark sMark;					// suduku assisted array
	struct sudokuStackElement* prev;
} element;
typedef struct sudokuStack
{
	element* top;
} sudokuStack;
typedef sudokuStack* psudokuStack;

int IsStackEmpty(const psudokuStack stck);
psudokuStack CreateStack();
void DeleteStack(psudokuStack* stck);

// NOTICE: Function create a copy of array but not quote the array
int StackPush(psudokuStack stck, const sudoku sdk, const sudokuMark sMark);
// NOTICE: Function free the memory of element
void StackPop(psudokuStack stck);

#endif