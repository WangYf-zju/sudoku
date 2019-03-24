#include "sudokuStack.h"
#include <stdlib.h>

int IsStackEmpty(const psudokuStack stck)
{
	if (stck->top == NULL)
		return 1;
	else
		return 0;
}

psudokuStack CreateStack()
{
	psudokuStack stck = (psudokuStack)malloc(sizeof(sudokuStack));
	if (stck==NULL)
		return NULL;
	stck->top = NULL;
	return stck;
}

int StackPush(psudokuStack stck, const sudoku sdk, const sudokuMark sMark)
{
	if (stck==NULL || sdk==NULL || sMark==NULL)
		return 0;
	element* e = (element*)malloc(sizeof(element));
	if (e == NULL)
		return 0;
	e->prev = stck->top;

	for (int i=0; i<Raw; i++)
		for (int j=0; j<Column; j++)
		{
			e->sdk[i][j] = sdk[i][j];
			e->sMark[i][j] = sMark[i][j];
		}
	stck->top = e;
	return 1;
}

void StackPop(psudokuStack stck)
{
	if (stck==NULL || IsStackEmpty(stck))
		return;
	element* temp = stck->top;
	stck->top = stck->top->prev;
	free(temp);
}

void DeleteStack(psudokuStack* stck)
{
	while (IsStackEmpty(*stck))
	{
		StackPop(*stck);
	}
	*stck = NULL;
}