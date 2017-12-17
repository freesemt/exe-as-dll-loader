#include <embed-python.h>
#include "test-1.h"
#include "test-2.h"
#include "test-3.h"
#include "test-4.h"
#include "test-5.h"
#include "test-6.h"
#include "test-7.h"

int main()
{
	EpC_Initialize();

	// note that cwd is 'embed-python-test'
	EpC_AddSysPath("..\\..\\..\\scripts");

	test_1();
	test_2();
	test_3_C_InterfaceStopper();
	test_3_C_InterfaceNumArgs();
	test_4();
	test_5();
	test_6();
	test_7();

	EpC_Finalize();
	return 0;
}