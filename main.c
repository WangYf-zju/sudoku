#include "sudoku.h"
#include <stdio.h>

void PrintSudoku(const sudoku sdk);

int main(int argc, char* argv[])
{
	// Test Solve()
	sudoku test1 = {
  		{0, 0, 5, 3, 0, 0, 0, 0, 0},
  		{8, 0, 0, 0, 0, 0, 0, 2, 0},
  		{0, 7, 0, 0, 1, 0, 5, 0, 0},
  		{4, 0, 0, 0, 0, 5, 3, 0, 0},
 		{0, 1, 0, 0, 7, 0, 0, 0, 6},
 		{0, 0, 3, 2, 0, 0, 0, 8, 0},
 		{0, 6, 0, 5, 0, 0, 0, 0, 9},
		{0, 0, 4, 0, 0, 0, 0, 3, 0},
		{0, 0, 0, 0, 0, 9, 7, 0, 0}
	};	
	TransDecToSudokuVar(test1);
	if (Solve(test1))
	{
		TransSudokuVarToDec(test1);
		PrintSudoku(test1);		
	}
	printf("\n");
	// Test GenerateSudoku()
	sudoku test2;
	GenerateSudoku(test2);
	PrintSudoku(test2);
	printf("\n");
	TransDecToSudokuVar(test2);
	if (Solve(test2))
	{
		TransSudokuVarToDec(test2);
		PrintSudoku(test2);		
	}
	return 0;
}

void PrintSudoku(const sudoku sdk)
{
	for (int i = 0; i < Raw; i++)
	{
		for (int j = 0; j < Column; j++)
			printf("%2d", sdk[i][j]);
		printf("\n");
	}	
}