#pragma once
#ifndef _GENERAL_FUNCTIONS_
#define _GENERAL_FUNCTIONS_
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define SPACE ' '
#define ROW 9
#define COL 9
#define FINISH_SUCCESS -2
#define NOT_FINISH -3
#define FINISH_FAILURE -4
#define FAIL -1
#define FILLED -6

typedef struct _Array
{
	short* arr;
	unsigned short size;
} Array;


typedef struct _cor
{
	short x;
	short y;
}Cor;

typedef struct _player
{
	int n;
	char name[100];
	short board[ROW][COL];
	Array*** possibilities;
}Player;

typedef struct _listNodePlayer
{
	Player data;
	struct listNodePlayer* next;
	struct listNodePlayer* prev;

}ListNodePlayer;

typedef struct _listPlayer
{
	ListNodePlayer* head;
	ListNodePlayer* tail;

}ListPlayer;

typedef struct _TreeNode
{
	ListNodePlayer* data;
	struct treeNode* left;
	struct treeNode* right;
}TreeNode;

typedef struct _tree
{
	TreeNode* root;
}Tree;

typedef struct _listNodeCell
{
	Cor data;
	struct listNodeCell* next;

}ListNodeCell;

typedef struct _listCell
{
	ListNodeCell* head;
	ListNodeCell* tail;
}ListCell;


void check_allocation(void* ptr, char* msg);

//player list functions
ListNodePlayer* createNewListNode(Player data, ListNodePlayer* next, ListNodePlayer* prev);
void makeEmptyListPlayer(ListPlayer* lst);
bool isEmptyList(ListPlayer lst);
void insertDataToEndList(ListPlayer* lst, Player data);
void insertNodeToEndList(ListPlayer* lst, ListNodePlayer* newTail);
void freeList(ListPlayer lst);
void freeListRec(ListNodePlayer* head);
void removeNode(ListNodePlayer* after);
void printTreeInorder(Tree tr);


void printWinnersRec(ListNodePlayer* head);

#endif