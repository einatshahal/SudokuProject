#include "general_functions.h"
#include "main.h"
#include "source1.h"
#include "source2.h"
#include "source3.h"
#include "source4.h"

/*____________________________________________________________________________
							 Sudoku Project

  information: The program is sudoku game.
			   In the end of the game a list of the winners will be print.

			   **The board is currently formatted to 9 * 9

______________________________________________________________________________
				Names : Tal Rozenblat |  Einat Shahal
				ID :    316131895   |  315839431
______________________________________________________________________________*/

void main()
{
	printf(" ____  ____  ____  ____  ____  ____  ________  ____  ____  ____  ____  ____ ____ ____ ___\n ");
	printf("||S ||||u ||||d ||||o ||||k ||||u ||||       ||||p ||||r ||||o ||||j ||||e ||||c ||||t ||\n");
	printf("||__||||__||||__||||__||||__||||__||||_______||||__||||__||||__||||__||||__||||__||||__||\n");
	printf("|/__/||/__/||/__/||/__/||/__/||/__/||/_______/||/__/||/__/||/__/||/__/||/__/||/__/||/__/|\n");
	printf("\n");
	printf("\n");

	int sizeLst;
	srand(12345);

	ListPlayer* listActivePlayers = makeActivePlayersList(&sizeLst); /*make a list of players and build boards*/

	ListNodePlayer** arr = sortArr(listActivePlayers, sizeLst);

	arr = newArr(arr, &sizeLst);

	Tree tr = BuildTreeFromArray(arr, sizeLst);
	
	ListPlayer* listWinnersPlayers = scanPlayersInOrder(tr, sizeLst, listActivePlayers);

	printWinnersRec(listWinnersPlayers->head);


	freeTree(tr);
	free(arr);
	freeList(*listActivePlayers);
	free(listActivePlayers);
	freeList(*listWinnersPlayers);
	free(listWinnersPlayers);
}