#include "sudoku.h"
#include <stdlib.h>
#include <time.h>

void InitalizeMark(const sudoku sdk, sudokuMark sMark)
{
	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
			sMark[i][j] = SudokuMarkBlank;

	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
			if (sdk[i][j] != SudokuBlank)
				FillMark(sMark, i, j, sdk[i][j]);
}

void FillUniqueSolutionBlocks(sudoku sdk, sudokuMark sMark)
{
	int i, j;

	int isChangedFlag = TRUE;
	while (isChangedFlag)
	{
		isChangedFlag = FALSE;
		for (i=0; i<Raw; i++)
			for (j=0; j<Column; j++)
			{
				// only when esists one "1"bit in the variable, the expression is true
				if (sMark[i][j] && !(sMark[i][j]&(sMark[i][j]-1)))
				{
					sdk[i][j] = sMark[i][j];
					FillMark(sMark, i, j, sMark[i][j]);
					isChangedFlag = TRUE;
				}
			}
	}		
}

void FillMark(sudokuMark sMark, const int x, const int y, const sudokuVar var)
{
	int i, j, k;
	for (i = 0; i < Column; i++)
		DisableValue(sMark, x, i, var);
	for (j = 0; j < Raw; j++)
		DisableValue(sMark, j, y, var);
	// position of the big square which block in
	int squareX = x/3;
	int squareY = y/3;
	for (k = squareX * 3; k < squareX * 3 + 3; k++)
		for (int l = squareY * 3; l < squareY * 3 + 3; l++)
			DisableValue(sMark, k, l, var);
	sMark[x][y] = SudokuMarkFilled;
}

int CheckPracticability(const sudoku sdk, const sudokuMark sMark)
{
	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
			if (sdk[i][j]==SudokuBlank && sMark[i][j]==SudokuMarkFilled)
				return FALSE;
			else
				continue;
	return TRUE;
}

int CheckIsSolved(const sudoku sdk)
{
	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
			if (sdk[i][j] == SudokuBlank)
				return FALSE;
			else
				continue;
	return TRUE;
}


void RecoveryData(sudoku sdk, sudokuMark sMark, psudokuStack stck)
{
	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
		{
			sdk[i][j] = stck->top->sdk[i][j];
			sMark[i][j] = stck->top->sMark[i][j];
		}
	StackPop(stck);
}

void Try(sudoku sdk, sudokuMark sMark, psudokuStack stck)
{
	for (int i = 0; i < Raw; i++)
		for (int j = 0; j < Column; j++)
			if (sdk[i][j] == SudokuBlank)
				for (int k=0; k<NumberCount; k++)
					if (sMark[i][j] & ((sudokuVar)1)<<k)
					{
						DisableValue(sMark, i, j, (((sudokuVar)1)<<k));
						StackPush(stck, sdk, sMark);
						sdk[i][j] = (((sudokuVar)1))<<k;
						FillMark(sMark, i, j, sdk[i][j]);
						return;
					}
}

void DisableValue(sudokuMark sMark, const int x, const int y, const sudokuVar var)
{
	sMark[x][y] &= (~var);
}

int Solve(sudoku sdk)
{
	if (sdk == NULL)
		return ERROR_NULL_POINTER;

	sudokuMark sMark;
	InitalizeMark(sdk, sMark);
	FillUniqueSolutionBlocks(sdk, sMark);
	if (CheckIsSolved(sdk))
		return TRUE;
	if (!CheckPracticability(sdk, sMark))
		return FALSE;

	// Create stack to memorize try
	psudokuStack stck = CreateStack();
	if (sdk == NULL)
		return ERROR_ALLOCATE_MEMORY;

	while (1)
	{
		Try(sdk, sMark, stck);
		FillUniqueSolutionBlocks(sdk, sMark);
		// Sudoku has been finished.
		if (CheckIsSolved(sdk))
		{
			DeleteStack(&stck);
			return TRUE;
		}
		while (!CheckPracticability(sdk, sMark))
		{
			// No solution
			if (IsStackEmpty(stck))
				return FALSE;
			RecoveryData(sdk, sMark, stck);
		}
	}
}

void TransSudokuVarToDec(sudoku sdk)
{
	sudokuVar temp = 0;
	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
		{
			while (sdk[i][j] >>= 1)
				temp++;
			sdk[i][j] = temp + 1;
			temp = 0;
		}
}

void TransDecToSudokuVar(sudoku dec)
{
	sudokuVar temp = 1;
	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
		{
			while (--dec[i][j])
				temp <<= 1;
			dec[i][j] = temp;
			temp = 1;
		}
}

void GenerateSudoku(sudoku sdk)
{
	srand(time(NULL));
	int x = 0, y = 0;
	// Generate a sudoku
	do
	{
		for (int i = 0; i < Raw; i++)
			for (int j = 0; j < Column; j++)
				sdk[i][j] = 0;
		for (int i = 0; i < NumberCount; i++)
		{
			x = rand() % Raw;
			y = rand() % Column;
			sdk[x][y] = (sudokuVar)i;
		}
		TransDecToSudokuVar(sdk);
	} while (!Solve(sdk));
	TransSudokuVarToDec(sdk);
	// Produce some blank blocks
	int blockNum = rand() % 20 + 30;
	for (int i = 0; i < blockNum; i++)
	{
		x = rand() % Raw;
		y = rand() % Column;
		sdk[x][y] = 0;
	}
	sudokuVar change[NumberCount+1] = { 1,2,3,4,5,6,7,8,9 };
	// Change number
	for (int i = 0; i < 10; i++)
	{
		int rnd1 = rand() % NumberCount;
		int rnd2 = rand() % NumberCount;
		sudokuVar temp = change[rnd1];
		change[rnd1] = change[rnd2];
		change[rnd2] = temp;
	}
	change[NumberCount] = change[0];
	for(int i=0;i<Raw;i++)
		for (int j = 0; j < Column; j++)
			for(int k = 0; k < NumberCount; k++)
				if (sdk[i][j] == change[k])
				{
					sdk[i][j] = change[k + 1];
					break;
				}

}