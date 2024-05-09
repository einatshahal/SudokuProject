#pragma once
#ifndef _SOURCE4_
#define _SOURCE4_

#include "general_functions.h"

ListPlayer* scanPlayersInOrder(Tree tree, int sizeArr, ListPlayer* active);
void scanPlayerInOrderRec(TreeNode* root, ListPlayer* winners, int* sizeWinners, ListPlayer* active);
void FillBoard(TreeNode* player, ListPlayer* winners, int* sizeWinners, ListPlayer* active);
int OneStage(short board[][9], Array*** possibilities, int* x, int* y);
void checkmincor(short board[][9], Array*** possibilities, int* x, int* y);
void UpdatePossibleDigits(Array*** possibilities, int row, int col, int num);
Array* changeArr(Array*** possibilities, int row, int col, int num);
bool noPossibilities(Array*** possibilities, short board[][9]);
void sudokoPrintBoard(short sudokuBoard[][9]);
bool isOptionValid(int num, Array* arr);

#endif /* !_SOURCE4_*/