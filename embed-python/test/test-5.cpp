#include <stdio.h>
#include <embed-python.h>
#include "test-5.h"

int test_5()
{
	printf("test_5\n");
	EpC_Module module = EpC_Import("numpy");
	EpC_Function array = EpC_GetMethod(module, "array");
	EpC_Object one = EpC_CoInt(1);
	EpC_Object two = EpC_CoInt(2);
    EpC_Object values[2] = { one, two };
	EpC_Print(one, two, 0);
	EpC_Object list = EpC_CoList(2);

    for ( int i = 0; i < 2; ++i )
	{
		EpC_List_SetItem( list, i, values[i] );
	}

    EpC_Object args[1] = { list };
	EpC_Object nd_array = EpC_CallN(array, 1, args);
	EpC_Print( nd_array, 0 );

	return 0;
}