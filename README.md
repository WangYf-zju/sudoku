# Sudoku
A program to solve sudoku.
## How to Use
* See file [`main.c`](https://github.com/WangYf-zju/sudoku/blob/master/main.c) for source code.</br>

### To Solve sudoku
**1. Include header file** [`sudoku.h`](https://github.com/WangYf-zju/sudoku/blob/master/sudoku.h)**.**
```
#include "sudoku.h"
```
**2. Create a sudoku array (0 stand for blank).**
```
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
```
**3. Call `TransDecToSudokuVar()` to format sudoku data to power of 2 form.**
```
TransDecToSudokuVar(test1);
```
**4. Call `Solve()` to solve sudoku.**
```
Solve(test1);
```
**5. Call `TransSudokuVarToDec()` to restore sudoku data to demical form.**
```
TransSudokuVarToDec(test1);
```
### To Generate random sudoku
**1. Include header file** [`sudoku.h`](https://github.com/WangYf-zju/sudoku/blob/master/sudoku.h)**.**
```
#include "sudoku.h"
```
**2. Create a sudoku array (0 stand for blank).**
```
sudoku test2;
```
**3. Call `GenerateSudoku()` to generate a random sudoku.**
```
GenerateSudoku(test2);
```

* * * * *
## Algorithm Implementation
* See file [`sudokuTypedef.h`](https://github.com/WangYf-zju/sudoku/blob/master/sudokuTypedef.h) for detailed defination.</br>
To understand the algorithm, you should know how `sudoku array` and `assisted array` work.</br>

In `sudoku array`, 0-9 will be saved as follows: </br>

|Number|Save Format(bin)|
|:--:|:--:|
|0(blank)|000000000|
|1|000000001|
|2|000000010|
|3|000000100|
|4|000001000|
|5|000010000|
|6|000100000|
|7|001000000|
|8|010000000|
|9|100000000|

This is the reason why you should call function `TransDecToSudokuVar()` first to format data.

In `assisted array`, data storage is similar to `sudoku array`.</br>
If a bit is set 1, it means the corresponding number can be filled to the block.</br>
For example, data `010101010` means current block can be filled with 2, 4, 6 and 8.</br>
**Notice:** when a block being filled, the corresponding data in assisted array will be set 0.

### Algorithm Flow
* See file [`sudoku.c`](https://github.com/WangYf-zju/sudoku/blob/master/sudoku.c) for source code

**Function <label style="color:red">Solve()</label> run as follows:</br>**

**1. Define an <label style="color:green">assisted array</label> and initalize it.**</br>
After initalization, the array can mark which number can be filled in each block.
```
sudokuMark sMark;
InitalizeMark(sdk, sMark);
```
**2. Search blocks which have only solution and fill them.**
```
FillUniqueSolutionBlocks(sdk, sMark);
```
**3. Check if sudoku has been solved or sudoku has no solution.**
```
if (CheckIsSolved(sdk))
	return TRUE;
if (!CheckPracticability(sdk, sMark))
	return FALSE;
```
**4. Start a loop to try and find the solution.**
* Select a blank block and try to fill a number.
* Search blocks which have only solution and fill them.
* Check if sudoku has been solved.
* Check Practicability of current try.
