#include <iostream>
#include <embed-python.h>
#include "test-1.h"
using std::cout;

int test_1()
{
	cout << "test-1\n";
	Ep_Function hello = Ep_FromImport( "hello", "hello" );
	Ep_Object name( "Keiko-san" );

	hello(name);

	return 0;
}