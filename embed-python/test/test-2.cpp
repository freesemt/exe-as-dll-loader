#include <iostream>
#include <embed-python.h>
#include "test-2.h"
using std::cout;

int test_2()
{
	cout << "test-2\n";

	Ep_Function add = Ep_FromImport( "arithmetic", "add" );
	Ep_Object one( 1 );
	Ep_Object two( 2 );

	Ep_Object result = add(one, two);
	cout << result << "\n";

	return 0;
}