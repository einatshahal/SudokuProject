#include "general_functions.h"
#include "source2.h"

ListNodePlayer** sortArr(ListPlayer* lst, int sizeLst)
{
	int i = 0;
	int size;
	ListNodePlayer* temp = lst->head;
	ListNodePlayer** arr = (ListNodePlayer**)malloc(sizeLst * sizeof(ListNodePlayer*));
	check_allocation(arr, "Check Allocation failure!!");

	while (temp != NULL)
	{
		arr[i] = temp;
		temp = temp->next;
		i++;
	}


	arr = mergeSortList(arr, sizeLst);

	return arr;
}

ListNodePlayer** mergeSortList(ListNodePlayer** arr, int size)
{

	if (size < 2)
		return arr;

	mergeSortList(arr, size / 2);
	mergeSortList(arr + (size / 2), size - size / 2);
	arr = merge(arr, size / 2, arr + (size / 2), size - size / 2);

	return arr;
}

ListNodePlayer** merge(ListNodePlayer** arr1, int size1, ListNodePlayer** arr2, int size2)
{
	int ind1, ind2, resInd;
	ind1 = ind2 = resInd = 0;
	int num;
	ListNodePlayer** newArr = (ListNodePlayer**)malloc((size1 + size2) * sizeof(ListNodePlayer*));
	check_allocation(newArr, "Check Allocation failure!!");

	while ((ind1 < size1) && (ind2 < size2))
	{
		if (arr1[ind1]->data.n < arr2[ind2]->data.n)
		{
			newArr[resInd] = arr1[ind1];
			ind1++;
		}
		else if (arr1[ind1]->data.n == arr2[ind2]->data.n)
		{
			num = strcmp(arr1[ind1]->data.name, arr1[ind2]->data.name);
			if (num > 0)
			{
				newArr[resInd] = arr1[ind1];
				ind1++;
			}
			else
			{
				newArr[resInd] = arr2[ind2];
				ind2++;
			}
		}
		else
		{
			newArr[resInd] = arr2[ind2];
			ind2++;
		}
		resInd++;
	}

	while (ind1 < size1)
	{
		newArr[resInd] = arr1[ind1];
		ind1++;
		resInd++;
	}

	while (ind2 < size2)
	{
		newArr[resInd] = arr2[ind2];
		ind2++;
		resInd++;
	}

	return newArr;
}
