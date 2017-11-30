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

	Ep_Object int_result = add(one, two);
	cout << int_result << "\n";

	Ep_Object pi(3.14);
	Ep_Object e(2.72);

	Ep_Object float_result = add(pi, e);
	cout << float_result << "\n";

	return 0;
}