#pragma once
#ifndef _SOURCE2_
#define _SOURCE2_

#include "general_functions.h"

ListNodePlayer** sortArr(ListPlayer* lst, int sizeLst);
ListNodePlayer** mergeSortList(ListNodePlayer** arr, int size);
ListNodePlayer** merge(ListNodePlayer** arr1, int size1, ListNodePlayer** arr2, int size2);

#endif /* !_SOURCE2_*/