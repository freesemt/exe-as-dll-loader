#include <embed-python.h>
#include "test-1.h"
#include "test-2.h"

int main()
{
	Ep_Initialize();

	// note that cwd is 'embed-python-test'
	Ep_AddSysPath("..\\..\\..\\scripts");

	test_1();
	test_2();

	Ep_Finalize();
	return 0;
}