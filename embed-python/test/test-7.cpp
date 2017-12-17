#include <stdio.h>
#include <embed-python.h>
#include "test-7.h"

int test_7()
{
	printf("test_7\n");
    
	EpC_Function increment = EpC_FromImport("kwargs_test", "increment");

	EpC_Object two = EpC_CoInt(2);
	EpC_Object args[1] = { two };

	EpC_Object kwargs = EpC_CoDict();
	EpC_Object ret1 = EpC_CallK(increment, 1, args, kwargs);	// no (or empty) kwargs
	EpC_Print(ret1, 0);

	EpC_Object ten = EpC_CoInt(10);
	EpC_Dict_SetItemString(kwargs, "inc", ten);

	EpC_Object ret2 = EpC_CallK(increment, 1, args, kwargs);	// inc=10
	EpC_Print(ret2, 0);

	return 0;
}