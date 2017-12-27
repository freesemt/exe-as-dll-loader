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

	int dims[] = { 2, 1 };
	EpC_Object nd_array_copy = EpC_CoDoubleNumpyArray( 2, dims, darray);
	EpC_Print(nd_array_copy, 0);

	const double another_data[] = { 0, 1, 1, 0 };
	int dims2[] = { 2, 2 };
	EpC_Object another_nd_array = EpC_CoDoubleNumpyArray( 2, dims2, another_data );
	EpC_Print(another_nd_array, 0);
	return 0;
}