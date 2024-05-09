#include "general_functions.h"
#include "source1.h"


//cell cor list functions
void makeEmptyListCell(ListCell* lst)
{

	lst->head = lst->tail = NULL;

}

bool isEmptyListCell(ListCell lst)
{

	return (lst.head == NULL);

}

void insertDataToEndListCell(ListCell* lst, Cor data)
{

	ListNodeCell* newTail;
	newTail = createNewListNodeCell(data, NULL);
	insertNodeToEndListCell(lst, newTail);

}

ListNodeCell* createNewListNodeCell(Cor data, ListNodeCell* next)
{
	ListNodeCell* node = (ListNodeCell*)malloc(sizeof(ListNodeCell));
	check_allocation(node, "Check Allocation failure!!");

	node->data = data;
	node->next = next;

	return node;
}

void insertNodeToEndListCell(ListCell* lst, ListNodeCell* newTail)
{
	if (isEmptyListCell(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}

}

void freeListCell(ListCell lst)
{

	freeListRecCell(lst.head);

}

void freeListRecCell(ListNodeCell* head)
{

	if (head == NULL)
		return;
	else
	{
		freeListRecCell(head->next);
		free(head);
	}

}

void removeNodeCell(ListNodeCell* after)
{//deletes the node after the one sent

	ListNodeCell* toDelete;

	toDelete = after->next;
	after->next = toDelete->next;
	free(toDelete);


}


//game functions
ListPlayer* makeActivePlayersList(int* x)
{
	int i;
	ListPlayer* lst = (ListPlayer*)malloc(sizeof(ListPlayer));
	check_allocation(lst, "Check Allocation failure!!");

	Player currPlayer;
	makeEmptyListPlayer(lst);
	*x = getNumOfPlayers();

	for (i = 0; i < *x; i++)
	{
		currPlayer = createPlayer();
		insertDataToEndList(lst, currPlayer);
	}

	return lst;
}

int getNumOfPlayers()
{

	int x = 0;
	printf("Please enter the amount of players:\n");
	scanf("%d", &x);

	if (x >= 0)
	{
		return x;
	}

	else
	{
		printf("Invalid number, please enter a valid number.\n");
		return getNumOfPlayers();
	}
}

Player createPlayer()
{
	Player* plr = (Player*)malloc(sizeof(Player));
	check_allocation(plr, "Check Allocation failure!!");

	int i = 0;
	int j;
	char c;

	printf("Please enter name:\n");
	scanf("%s", &(plr->name));

	for (i = 0; i < ROW; i++)
	{//fills board with initial "empty" values.
		for (j = 0; j < COL; j++)
		{
			plr->board[i][j] = -1;
		}
	}
	plr->possibilities = PossibleDigits(plr->board);
	createRandBoard(plr);

	return *plr;
}

void createRandBoard(Player* plr)
{
	int i, j, n, k, listSize = 81;
	ListCell* lst;
	ListNodeCell* curr;

	n = 1 + rand() % 20;//number of random numbers to be put in the board.
	plr->n = n;

	lst = create81List();

	for (i = 0; i < n; i++)
	{
		k = 1 + rand() % (listSize - 1);
		listSize--;
		curr = findK(lst, k);
		insertNumToBoard(curr->data.x, curr->data.y, plr->board, plr->possibilities);

		if (lst->head == curr)
		{
			lst->head = curr->next;
		}
		else
		{
			removeNodeCell(findK(lst, k - 1));
		}

		plr->possibilities = PossibleDigits(plr->board);
	}
}

ListCell* create81List()
{

	int i, j;
	ListCell* lst = (ListCell*)malloc(sizeof(ListCell));
	check_allocation(lst, "Check Allocation failure!!");

	Cor c;
	srand(time(NULL));

	makeEmptyListCell(lst);

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			c.x = i;
			c.y = j;
			insertDataToEndListCell(lst, c);
		}
	}


	return lst;
}

ListNodeCell* findK(ListCell* lst, int k)
{

	int i;
	ListNodeCell* cell;
	cell = lst->head;

	for (i = 1; i < k; i++)
	{
		cell = cell->next;
	}

	return cell;
}

void insertNumToBoard(int row, int col, short board[ROW][COL], Array*** possibilities)
{
	int i;
	int size = possibilities[row][col]->size;


	i = rand() % size;
	board[row][col] = possibilities[row][col]->arr[i];
}

Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** PossibleDigits = (Array***)malloc(ROW * sizeof(Array**));
	check_allocation(PossibleDigits, "Check Allocation failure!!");

	for (int k = 0; k < ROW; k++)
	{
		PossibleDigits[k] = (Array**)malloc(COL * sizeof(Array*));
		check_allocation(PossibleDigits[k], "Check Allocation failure!!");
	}

	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] != -1)
			{
				PossibleDigits[i][j] = NULL;
			}
			else /*SPACE*/
			{
				PossibleDigits[i][j] = buildArr(sudokuBoard, i, j);
			}
		}
	}

	return PossibleDigits;
}

Array* buildArr(short sudokuBoard[][9], int r, int c)
{
	int i, j;
	int row, col;
	int num;
	Array* PossibleArr = (Array*)malloc(sizeof(Array));
	check_allocation(PossibleArr, "Check Allocation failure!!");

	PossibleArr->arr = (short*)malloc(9 * sizeof(short));
	check_allocation(PossibleArr->arr, "Check Allocation failure!!");

	short arrTemp[9] = { 1,2,3,4,5,6,7,8,9 };

	for (j = 0; j < COL; j++) /*check the row*/
	{
		num = sudokuBoard[r][j];
		if (num != -1)
		{
			if (num == arrTemp[num - 1])
			{
				arrTemp[num - 1] = -1;
			}
		}
	}

	for (i = 0; i < ROW; i++) /*check the col*/
	{
		num = sudokuBoard[i][c];
		if (num != -1)
		{
			if (num == arrTemp[num - 1])
			{
				arrTemp[num - 1] = -1;
			}
		}
	}

	row = r / 3;
	col = c / 3;
	row = row * 3;
	col = col * 3;

	for (i = row; i < row + 3; i++) /*check the square*/
	{
		for (j = col; j < col + 3; j++)
		{
			num = sudokuBoard[i][j];
			if (num != -1)
			{
				if (num == arrTemp[num - 1])
				{
					arrTemp[num - 1] = -1;
				}
			}
		}

	}
	//-1 -1 2 3 4 5 6 -1 -1 -1
	/*0 1 2 3 4*/
	/*size = 5*/
	j = 0;
	for (i = 0; i < COL; i++)/* initialize the array*/
	{
		if (arrTemp[i] != -1)
		{
			PossibleArr->arr[j] = arrTemp[i];
			j++;
		}
	}


	PossibleArr->arr = (short*)realloc(PossibleArr->arr, (j * sizeof(short)));
	check_allocation(PossibleArr->arr, "Check Allocation failure!!");

	PossibleArr->size = j;

	return PossibleArr;
}