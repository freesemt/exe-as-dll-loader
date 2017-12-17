#include <stdio.h>
#include <embed-python.h>
#include "test-6.h"

int test_6()
{
	printf("test_6\n");
    
	EpC_Object name = EpC_CoString("Kate");
	printf("type of name is %s\n", EpC_TypeAsChar(name));

	EpC_Object one = EpC_CoInt(1);
	printf("type of one is %s\n", EpC_TypeAsChar(one));

	EpC_Object pi = EpC_CoInt(3.14);
	printf("type of pi is %s\n", EpC_TypeAsChar(pi));

	EpC_Module module = EpC_Import("numpy");
	EpC_Function array = EpC_GetMethod(module, "array");

	EpC_Object list = EpC_CoList(0);
	EpC_Object args[1] = { list };
	EpC_Object nd_array = EpC_CallN(array, 1, args);
	printf("type of nd_array is %s\n", EpC_TypeAsChar(nd_array));

	EpC_Object shape = EpC_GetAttrString(nd_array, "shape");
	EpC_Print(shape, 0);

	return 0;
}