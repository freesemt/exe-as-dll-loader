#include <stdio.h>
#include <embed-python.h>
#include "test-4.h"

int test_4()
{
	printf("test_4\n");
	EpC_Module module = EpC_Import("hello");
	EpC_Function hello = EpC_GetMethod(module, "hello");
	EpC_Object name = EpC_CoString("Keiko-san");
	EpC_Print(name, 0);
	EpC_Object s_arg[1] = { name };
	EpC_CallN(hello, 1, s_arg);

	return 0;
}