#pragma once
#ifndef _SOURCE1_
#define _SOURCE1_

#include "general_functions.h"

Array*** PossibleDigits(short sudokuBoard[][9]);
Array* buildArr(short sudokuBoard[][9], int r, int c);

//cell list functions
ListNodeCell* createNewListNodeCell(Cor data, ListNodeCell* next);
void makeEmptyListCell(ListCell* lst);
bool isEmptyListCell(ListCell lst);
void insertDataToEndListCell(ListCell* lst, Cor data);
void insertNodeToEndListCell(ListCell* lst, ListNodeCell* newTail);
void freeListCell(ListCell lst);
void freeListRecCell(ListNodeCell* head);
void removeNodeCell(ListNodeCell* after);

//game functions
ListPlayer* makeActivePlayersList(int* x);
int getNumOfPlayers();
Player createPlayer();
void createRandBoard(Player* plr);
ListCell* create81List();// creates the 81 num list for possible cells.
ListNodeCell* findK(ListCell* lst, int k);
void insertNumToBoard(int row, int col, short board[ROW][COL], Array*** possibilities);

#endif /* !_SOURCE1_*/