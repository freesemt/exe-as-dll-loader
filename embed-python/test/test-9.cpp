#include <stdio.h>
#include <embed-python.h>
#include "test-9.h"

int test_9()
{
	printf("test_9\n");

	EpC_Object one = EpC_CoInt(1);
	EpC_Object two = EpC_CoInt(2);
	EpC_Print(one, two, 0);

	EpC_Object list = EpC_CoList(2);
	EpC_List_SetItem(list, 0, one);
	EpC_List_SetItem(list, 1, two);

	for (int i = 0; i < 2; ++i)
	{
		EpC_Print(EpC_List_GetItem(list, i), 0);
	}

	EpC_Object tuple = EpC_CoTuple(2);
	EpC_Tuple_SetItem(tuple, 0, one);
	EpC_Tuple_SetItem(tuple, 1, two);

	for (int i = 0; i < 2; ++i)
	{
		EpC_Print(EpC_Tuple_GetItem(tuple, i), 0);
	}

	return 0;
}