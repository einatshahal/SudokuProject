#include "general_functions.h"


void check_allocation(void* ptr, char* msg)
{
	if (!ptr)
	{
		fprintf(stderr, "Allocation failure:%s\n", msg);
		exit(-1);
	}
}

//player list functions
ListNodePlayer* createNewListNode(Player data, ListNodePlayer* next, ListNodePlayer* prev)
{
	ListNodePlayer* node = (ListNodePlayer*)malloc(sizeof(ListNodePlayer));
	check_allocation(node, "Check Allocation failure!!");
	
	node->data = data;
	node->next = next;
	node->prev = prev;

	return node;
}

void makeEmptyListPlayer(ListPlayer* lst)
{

	lst->head = lst->tail = NULL;

}

bool isEmptyList(ListPlayer lst)
{

	return (lst.head == NULL);

}

void insertNodeToEndList(ListPlayer* lst, ListNodePlayer* newTail)
{
	if (isEmptyList(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		newTail->prev = lst->tail;
		newTail->next = NULL;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void insertDataToEndList(ListPlayer* lst, Player data)
{
	ListNodePlayer* newTail;
	newTail = createNewListNode(data, NULL, NULL);
	insertNodeToEndList(lst, newTail);
}

void freeList(ListPlayer lst)
{

	freeListRec(lst.head);

}

void freeListRec(ListNodePlayer* head)
{

	if (head == NULL)
		return;
	else
	{
		freeListRec(head->next);
		free(head);
	}

}

void removeNode(ListNodePlayer* node)
{
	ListNodePlayer* prev = node->prev;
	ListNodePlayer* next = node->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
}

/*tree*/



void printWinnersRec(ListNodePlayer* head)
{
	if (head == NULL)
		return;

	else
	{
		printf("Name Winner: %s\n", head->data.name);
		sudokoPrintBoard(head->data.board);
		printf("\n");
		printWinnersRec(head->next);
	}

}