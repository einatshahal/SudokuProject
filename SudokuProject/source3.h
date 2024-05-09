#pragma once
#ifndef _SOURCE3_
#define _SOURCE3_

#include "general_functions.h"

Tree BuildTreeFromArray(ListNodePlayer** arr, int  size);
double mylog(double x, double base);
ListNodePlayer** newArr(ListNodePlayer** arr, int* size);
TreeNode* recursiveTree(ListNodePlayer** arr, int size);
TreeNode* createNewTreeNode(ListNodePlayer* data, TreeNode* left, TreeNode* right);
void printTreeInorder(Tree tr);
void printNodes(TreeNode* root);
void freeTree(Tree tr);
void freeNodes(TreeNode* root);

#endif /* !_SOURCE3_*/