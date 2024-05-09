#include "general_functions.h"
#include "source4.h"

ListPlayer* scanPlayersInOrder(Tree tree, int sizeArr, ListPlayer* active)
{
	int sizeWinners = 0;
	ListPlayer* winners = (ListPlayer*)malloc(sizeArr * sizeof(ListPlayer));
	check_allocation(winners, "Check Allocation failure!!");

	makeEmptyListPlayer(winners);

	scanPlayerInOrderRec(tree.root, winners, &sizeWinners, active);

	winners = (ListPlayer*)realloc(winners, sizeWinners * sizeof(ListPlayer));
	check_allocation(winners, "Check Allocation failure!!");
	return winners;
}

void scanPlayerInOrderRec(TreeNode* root, ListPlayer* winners, int* sizeWinners, ListPlayer* active)
{
	if (root != NULL)
	{
		scanPlayerInOrderRec(root->left, winners, sizeWinners, active);//scans left

		FillBoard(root, winners, sizeWinners, active);//runs onestage on root

		scanPlayerInOrderRec(root->right, winners, sizeWinners, active);//scans right
	}

	return;
}

void FillBoard(TreeNode* player, ListPlayer* winners, int* sizeWinners, ListPlayer* active)
{
		printf("\n\n\n %s's turn:\n", player->data->data.name);

		int x = -1, y = -1, ans, i;
		Array*** possibilities = player->data->data.possibilities;

		int res = OneStage(player->data->data.board, possibilities, &x, &y);

		while (res == NOT_FINISH)
		{
			sudokoPrintBoard(player->data->data.board);
			printf("\n Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);

			for (i = 0; i < (possibilities[x][y]->size); i++)
			{ // prints options
				printf("%d. %d\n", i + 1, possibilities[x][y]->arr[i]);
			}

			scanf("%d", &ans);//scan the answer

			while (!isOptionValid(ans, possibilities[x][y]))
			{
				printf("\n Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);

				for (i = 0; i < (possibilities[x][y]->size); i++)
				{ // prints options
					printf("%d. %d\n", i + 1, possibilities[x][y]->arr[i]);
				}
				scanf("%d", &ans);//scan the answer
			}

			printf("Updating cell %d with value %d\n\n", (x * 9 + y), ans);

			player->data->data.board[x][y] = ans;// inserts answer to place
			possibilities[x][y] = NULL;
			UpdatePossibleDigits(possibilities, x, y, ans);

			x = -1;
			y = -1;
			res = OneStage(player->data->data.board, possibilities, &x, &y);
		}
		//	if (player->data->data.name[0] == 's')
		//	{
				//printf("stop\n");
			//}

		if (res == FINISH_FAILURE)
		{
			if (active->head == player->data)/*head list*/
			{
				if (active->head->next == NULL)
				{
					active->head = active->tail=NULL;
				}
				else
				{
					ListNodePlayer* newhead = active->head->next;
					newhead->prev = NULL;
					active->head = newhead;
				}
			}
			else if (active->tail == player->data)/*tail*/
			{
				if (active->tail->prev == NULL)
				{
					active->head = active->tail = NULL;
				}
				else
				{
					ListNodePlayer* newtail = active->tail->prev;
					newtail->next = NULL;
					active->tail = newtail;
				}
			}
			else
			{
				removeNode(player->data);
			}
			player->data = NULL;

			printf("User's selections led to duplications.\n");
		}

		if (res == FINISH_SUCCESS)
		{
			insertDataToEndList(winners, player->data->data);

			if (active->head == player->data)/*head list*/
			{	if (active->head->next == NULL)
				{
					active->head = active->tail = NULL;
				}
				else
				{
				ListNodePlayer* newhead = active->head->next;
				newhead->prev = NULL;
				active->head = newhead;
				}
			}
			else if (active->tail == player->data)/*tail*/
			{
				if (active->tail->prev == NULL)
				{
					active->head = active->tail = NULL;
				}
				else
				{
					ListNodePlayer* newtail = active->tail->prev;
					newtail->next = NULL;
					active->tail = newtail;
				}
			}
			else
			{
				removeNode(player->data);
			}
			player->data = NULL;

			printf("Congratulations! You've won!\n");
			(*sizeWinners)++;
		}
	
}

bool isOptionValid(int num, Array* arr)
{
	int i;
	for (i = 0; i < (arr->size); i++)
	{
		if (num == arr->arr[i])
		{
			return true;
		}
	}
	return false;
}

int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
	int row, col;
	int res;
	bool isduplicate;
	for (row = 0; row < ROW; row++)
	{
		for (col = 0; col < COL; col++)
		{
			if (possibilities[row][col] != NULL)
			{
				if (possibilities[row][col]->size == 1)
				{
					board[row][col] = possibilities[row][col]->arr[0];
					possibilities[row][col] = NULL;

					UpdatePossibleDigits(possibilities, row, col, board[row][col]);
					isduplicate = noPossibilities(possibilities, board);
					if (isduplicate == true)
					{
						res = FINISH_FAILURE;
						return res;
					}

					return OneStage(board, possibilities, x, y);/*recursive call*/
				}
			}
		}
	}
	checkmincor(board, possibilities, x, y);

	/*if the board is full so the game is over*/
	if (*x == -1 && *y == -1)
	{
		res = FINISH_SUCCESS;
		return res;
	}
	else/*if the board is not full i need to send cor of x and y*/
	{
		res = NOT_FINISH;
		return res;
	}
}

void checkmincor(short board[][9], Array*** possibilities, int* x, int* y)
{
	int i, j;
	int min = 10;/*there is max 9 option*/
	*y = -1;
	*x = -1;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (possibilities[i][j] != NULL)
			{
				if (min > possibilities[i][j]->size)
				{
					min = possibilities[i][j]->size;
					*x = i;
					*y = j;
				}
			}

		}

	}
}

void UpdatePossibleDigits(Array*** possibilities, int row, int col, int num)
{
	int i, j, r, c;

	for (j = 0; j < COL; j++) /*check the row*/
	{
		if (possibilities[row][j] != NULL)
		{
			possibilities[row][j] = changeArr(possibilities, row, j, num);
		}

	}

	for (i = 0; i < ROW; i++)/*check the col*/
	{
		if (possibilities[i][col] != NULL)
		{
			possibilities[i][col] = changeArr(possibilities, i, col, num);
		}
	}

	r = (row / 3);
	c = (col / 3);
	r = (r * 3);
	c = (c * 3);

	for (i = r; i < r + 3; i++) /*check the square*/
	{
		for (j = c; j < c + 3; j++)
		{
			if (possibilities[i][j] != NULL)
			{
				possibilities[i][j] = changeArr(possibilities, i, j, num);
			}
		}

	}

}

Array* changeArr(Array*** possibilities, int row, int col, int num)
{
	int i;
	int j = 0;

	short* arr = (short*)malloc(9 * sizeof(short));
	//check allocation

	for (i = 0; i < possibilities[row][col]->size; i++)
	{
		if (possibilities[row][col]->arr[i] != num)
		{
			arr[j] = possibilities[row][col]->arr[i];
			j++;

		}
	}
	if (j == 0)
		return NULL;

	arr = (short*)realloc(arr, j * sizeof(short));
	check_allocation(arr, "Check Allocation failure!!");

	possibilities[row][col]->arr = arr;
	possibilities[row][col]->size = j;

	return possibilities[row][col];
}

bool noPossibilities(Array*** possibilities, short board[][9])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (possibilities[i][j] == NULL && board[i][j] == -1)
			{
				return true;
			}
		}
	}
	return false;
}

void sudokoPrintBoard(short sudokuBoard[][9])
{
	int i, j;
	printf("\n\n");
	printf("  | 0 1 2| 3 4 5| 6 7 8|");
	printf("\n");
	printf("-----------------------|");
	printf("\n");

	for (i = 0; i < 9; i++)
	{
		printf(" %d|", i);

		for (j = 0; j < 9; j++)
		{
			if (j == 2 || j == 5)
			{
				if (sudokuBoard[i][j] == -1)
				{
					printf(" %c|", SPACE);
				}
				else
					printf(" %d|", sudokuBoard[i][j]);
			}
			else if (sudokuBoard[i][j] == -1)
			{
				printf(" %c", SPACE);
			}
			else
				printf(" %d", sudokuBoard[i][j]);
		}
		printf("\n");
		if (i == 2 || i == 5)
		{
			printf("-----------------------");
			printf("\n");
		}
	}
	printf("-----------------------");
	printf("\n\n");
}
