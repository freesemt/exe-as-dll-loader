#include <embed-python.h>
#include "test-1.h"
#include "test-2.h"
#include "test-3.h"

int main()
{
	EpC_Initialize();

	// note that cwd is 'embed-python-test'
	EpC_AddSysPath("..\\..\\..\\scripts");

	test_1();
	test_2();
	test_3_C_InterfaceStopper();
	test_3_C_InterfaceNumArgs();

	EpC_Finalize();
	return 0;
}