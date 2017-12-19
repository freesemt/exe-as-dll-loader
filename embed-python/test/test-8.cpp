#include <stdio.h>
#include <embed-python.h>
#include "test-5.h"
#include "test-8.h"

int test_8()
{
	printf("test_8\n");
	EpC_NumpyInitialize();

	EpC_Object nd_array = CreateNdArray();
	// EpC_Print(nd_array, 0);
	printf("type of nd_array is %s\n", EpC_TypeAsChar(nd_array));
	const double* darray = EpC_NumpyArrayAsDoubleArray(nd_array, 1);
	for ( int i=0; i < 2; ++i)
	{
		printf("darray[%d]=%g\n", i, darray[i]);
	}
	return 0;
}