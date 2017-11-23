#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <Python.h>
#include <embed-python.h>

using std::cout;
using std::cerr;
using std::string;
using std::stringstream;

EMBEDPYTHONLIB_API void Ep_Initialize(void)
{
	cout << "Ep_Initialize\n";
	Py_Initialize();
}

EMBEDPYTHONLIB_API int Ep_Finalize(void)
{
	cout << "Ep_Finalize\n";
	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}

EMBEDPYTHONLIB_API void Ep_AddSysPath(const char* path)
{
	cout << "Ep_AddPath\n";
	stringstream pycode;
	pycode
		<< "import sys\n"
		<< "import os\n"
		<< "sys.path.append('" << path << "')\n";

	cout << "pycode=\n" << pycode.str();

	PyRun_SimpleString( pycode.str().c_str() );
}

Ep_Object::Ep_Object()
{
	value = 0;
}

Ep_Object::Ep_Object(PyObject* v)
{
	value = v;
}

Ep_Object::Ep_Object(const char* cstr)
{
	value = PyUnicode_FromString(cstr);
}

PyObject* Ep_Object::get()
{
	return value;
}

Ep_Function::Ep_Function()
{
	function = 0;
}

Ep_Function::Ep_Function( PyObject* f )
{
	function = f;
}


Ep_Object Ep_Function::call()
{
	PyObject* pargs = PyTuple_New(0);
	PyObject* ret_value = PyObject_CallObject(function, pargs);
	return Ep_Object(ret_value);
}

Ep_Object Ep_Function::call(Ep_Object& arg1, ...)
{
	PyObject* pargs = PyTuple_New(1);
	PyObject* parg1 = arg1.get();
	if (!parg1) {
		Py_DECREF(parg1);
		// Py_DECREF(pModule);
		cerr << "Cannot convert argument\n";
		return Ep_Object();
	}

	PyTuple_SetItem(pargs, 0, parg1);
	PyObject* ret_value = PyObject_CallObject(function, pargs);

	return Ep_Object(ret_value);
}

Ep_Object Ep_Function::operator()()
{
	return Ep_Function::call();
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1)
{
	return Ep_Function::call( arg1, 0 );
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2)
{
	return Ep_Function::call(arg1, arg2, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3)
{
	return Ep_Function::call(arg1, arg2, arg3, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, arg5, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, arg5, arg6, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8, Ep_Object& arg9)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8, Ep_Object& arg9, Ep_Object& arg10)
{
	return Ep_Function::call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, 0);
}


EMBEDPYTHONLIB_API Ep_Function Ep_FromImport(const char* c_pname, const char* c_funcname)
{
	PyObject* pname = PyUnicode_DecodeFSDefault(c_pname);
	PyObject* package = PyImport_Import(pname);
	Py_DECREF(pname);

	if (package == NULL)
	{
		PyErr_Print();
		cerr << "Failed to load '" << c_pname << "'\n";
		return Ep_Function();
	}

	PyObject* function = PyObject_GetAttrString(package, c_funcname);
	if (function == 0 || !PyCallable_Check(function)) 
	{
		if (PyErr_Occurred())
		{
			PyErr_Print();
		}
		cerr << "Cannot find function '" << c_funcname << "'\n";
	}
	Py_XDECREF(function);
	Py_DECREF(package);

	return Ep_Function(function);
}