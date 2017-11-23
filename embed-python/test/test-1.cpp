#include <iostream>
#include <embed-python.h>
using std::cout;

int main()
{
	cout << "test-1\n";
	Ep_Initialize();

	// note that cwd is 'embed-python-test'
	Ep_AddSysPath( "..\\..\\..\\scripts" );
	Ep_Function hello = Ep_FromImport( "hello", "hello" );
	Ep_Object name( "Keiko-san" );

	hello(name);

	Ep_Finalize();
	return 0;
}