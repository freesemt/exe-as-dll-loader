#include <stdio.h>
#include <embed-python.h>
#include "test-3.h"

int test_3_C_InterfaceStopper()
{
	printf("test_3_C_InterfaceStopper\n");
	EpC_Function hello = EpC_FromImport("hello", "hello");

	EpC_Object name = EpC_CoString("Keiko-san");
	EpC_Print( name, 0 );
	EpC_CallS( hello, name, 0);

	EpC_Function add = EpC_FromImport( "arithmetic", "add" );
	EpC_Object one = EpC_CoInt( 1 );
	EpC_Object two = EpC_CoInt( 2 );

	EpC_Object int_result = EpC_CallS(add, one, two, 0);
	EpC_Print(int_result, 0);

	EpC_Object pi = EpC_CoFloat(3.14);
	EpC_Object e = EpC_CoFloat(2.72);

	EpC_Object float_result = EpC_CallS(add, pi, e, 0);
	EpC_Print(float_result, 0);
	return 0;
}

int test_3_C_InterfaceNumArgs()
{
	printf("test_3_C_InterfaceNumArgs\n");
	EpC_Function hello = EpC_FromImport("hello", "hello");
	EpC_Object name = EpC_CoString("Keiko-san");
	EpC_Print(name, 0);
	EpC_Object s_arg[1] = { name };
	EpC_CallN( hello, 1, s_arg);

	EpC_Function add = EpC_FromImport("arithmetic", "add");
	EpC_Object one = EpC_CoInt(1);
	EpC_Object two = EpC_CoInt(2);
	EpC_Object i_args[2] = { one, two };

	EpC_Object int_result = EpC_CallN( add, 2, i_args );
	EpC_Print(int_result, 0);

	EpC_Object pi = EpC_CoFloat(3.14);
	EpC_Object e = EpC_CoFloat(2.72);
	EpC_Object f_args[2] = { pi, e };

	EpC_Object float_result = EpC_CallN( add, 2, f_args );
	EpC_Print(float_result, 0);

	return 0;
}