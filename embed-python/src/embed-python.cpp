#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdarg.h>
#include <embed-python.h>
#include <numpy/arrayobject.h>

using std::cout;
using std::cerr;
using std::string;
using std::stringstream;
using std::vector;

/*
 *	C interface implementation
 */

EMBEDPYTHONLIB_API void EpC_Initialize(void)
{
	Ep_Initialize();
}

EMBEDPYTHONLIB_API int EpC_Finalize(void)
{
	return Ep_Finalize();
}

EMBEDPYTHONLIB_API void EpC_AddSysPath(const char* path)
{
	Ep_AddSysPath(path);
}

EMBEDPYTHONLIB_API EpC_Function EpC_FromImport(const char* c_pname, const char* c_funcname)
{
	PyObject* pname = PyUnicode_DecodeFSDefault(c_pname);
	PyObject* package = PyImport_Import(pname);
	Py_DECREF(pname);

	if (package == NULL)
	{
		PyErr_Print();
		cerr << "Failed to load '" << c_pname << "'\n";
		return 0;
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
	// Py_XDECREF(function);
	Py_DECREF(package);

	return function;
}

EMBEDPYTHONLIB_API EpC_Module EpC_Import(const char* c_pname)
{
	PyObject* pname = PyUnicode_DecodeFSDefault(c_pname);
	PyObject* package = PyImport_Import(pname);
	Py_DECREF(pname);

	if (package == NULL)
	{
		PyErr_Print();
		cerr << "Failed to load '" << c_pname << "'\n";
		return 0;
	}
	return package;
}

EMBEDPYTHONLIB_API EpC_Function EpC_GetMethod(EpC_Module module, const char* name)
{
	PyObject* method = PyObject_GetAttrString(module, name);
	if (method == 0 || !PyCallable_Check(method))
	{
		if (PyErr_Occurred())
		{
			PyErr_Print();
		}
		cerr << "Cannot find method '" << name << "'\n";
	}
	// Py_XDECREF(method);
	// Py_DECREF(module);

	return method;
}

EMBEDPYTHONLIB_API EpC_Object EpC_GetAttrString(EpC_Object object, const char* name)
{
	PyObject* attr = PyObject_GetAttrString(object, name);
	if (attr == 0)
	{
		if (PyErr_Occurred())
		{
			PyErr_Print();
		}
		cerr << "Cannot find attr '" << name << "'\n";
	}
	// Py_XDECREF(method);
	// Py_DECREF(module);

	return attr;
}

EMBEDPYTHONLIB_API int EpC_SetAttrString(EpC_Object object, const char* name, EpC_Object value)
{
	return PyObject_SetAttrString(object, name, value);
}

EMBEDPYTHONLIB_API void EpC_DECREF(EpC_Object object)
{
	Py_DECREF(object);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoString(const char* cstr)
{
	return  PyUnicode_FromString(cstr);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoInt(const int int_value)
{
	return  PyLong_FromLong(int_value);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoFloat(const double float_value)
{
	return PyFloat_FromDouble(float_value);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoNone()
{
	return Py_None;
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoList(const int num_items)
{
	return PyList_New(num_items);
}

EMBEDPYTHONLIB_API int EpC_List_SetItem(EpC_Object list, int index, EpC_Object item)
{
	return PyList_SetItem( list, index, item);
}

EMBEDPYTHONLIB_API EpC_Object EpC_List_GetItem(EpC_Object list, int index)
{
	return PyList_GetItem(list, index);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoTuple(const int num_items)
{
	return PyTuple_New(num_items);
}

EMBEDPYTHONLIB_API int EpC_Tuple_SetItem(EpC_Object tuple, int index, EpC_Object item)
{
	return PyTuple_SetItem(tuple, index, item);
}

EMBEDPYTHONLIB_API EpC_Object EpC_Tuple_GetItem(EpC_Object tuple, int index)
{
	return PyTuple_GetItem(tuple, index);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoDict()
{
	return PyDict_New();
}

EMBEDPYTHONLIB_API int EpC_Dict_SetItemString(EpC_Object dict, const char* key, EpC_Object val)
{
	return PyDict_SetItemString(dict, key, val);
}

EMBEDPYTHONLIB_API const char* EpC_AsChar(EpC_Object object)
{
	// learned at https://stackoverflow.com/questions/5356773/python-get-string-representation-of-pyobject

	PyObject* str1 = PyObject_Str(object);
	PyObject* str2 = PyUnicode_AsEncodedString(str1, "utf-8", "~E~");
	const char *bytes = PyBytes_AsString(str2);

	Py_XDECREF(str1);
	Py_XDECREF(str2);

	// printf("DEBUG: bytes=%s\n", bytes);
	return bytes;
}

EMBEDPYTHONLIB_API const int EpC_NumpyInitialize()
{
	import_array();
	return 0;
}

EMBEDPYTHONLIB_API const double* EpC_NumpyArrayAsDoubleArray(EpC_Object object, int depth)
{
	// printf("EpC_NumpyArrayAsDoubleArray: depth=%d\n", depth);

	PyArrayObject* in_array = (PyArrayObject *)PyArray_ContiguousFromAny(object, PyArray_DOUBLE, depth, depth);
	// printf("in_array=%p\n", in_array);
	if (in_array == 0)
		return 0;

	NpyIter *in_iter = NpyIter_New(in_array, NPY_ITER_READONLY, NPY_KEEPORDER, NPY_NO_CASTING, NULL);
	double ** in_dataptr = (double **)NpyIter_GetDataPtrArray(in_iter);
	// printf("in_dataptr=%p\n", in_dataptr);
	return *in_dataptr;
}

EMBEDPYTHONLIB_API EpC_Object EpC_CoDoubleNumpyArray(int nd, int* dims, const double* data)
{
	npy_intp dims_[2] = { dims[0], dims[1] };
	PyObject* pyobject = PyArray_SimpleNewFromData(nd, dims_, PyArray_DOUBLE, (void*)data);
	return pyobject;
}

EMBEDPYTHONLIB_API int EpC_AsInt(EpC_Object object)
{
	return PyLong_AsLong(object);
}

EMBEDPYTHONLIB_API double EpC_AsDouble(EpC_Object object)
{
	return PyFloat_AsDouble(object);
}

EMBEDPYTHONLIB_API EpC_Object EpC_CallS(EpC_Function func, EpC_Object arg1, ...)
{
	vector<EpC_Object> arg_list;
	arg_list.push_back(arg1);

	va_list valist;
	va_start(valist, arg1);

	while (1)
	{
		EpC_Object arg_ = va_arg(valist, EpC_Object);
		if (arg_ == 0)
		{
			break;
		}

		arg_list.push_back(arg_);
	}

	va_end(valist);

	int num_args = arg_list.size();
	PyObject* pargs = PyTuple_New(num_args);

	for (int i = 0; i < num_args; ++i)
	{
		PyTuple_SetItem(pargs, i, arg_list[i]);
	}

	PyObject* ret_value = PyObject_CallObject(func, pargs);
	// Py_DECREF(pargs);
	return ret_value;
}

EMBEDPYTHONLIB_API EpC_Object EpC_CallN(EpC_Function func, const int num_args, EpC_Object* args )
{
	// printf( "num_args=%d", num_args);
	PyObject* pargs = PyTuple_New(num_args);

	for (int i = 0; i < num_args; ++i)
	{
		PyTuple_SetItem(pargs, i, args[i]);
	}

	PyObject* ret_value = PyObject_CallObject(func, pargs);
	// Py_DECREF(pargs);
	return ret_value;
}

EMBEDPYTHONLIB_API EpC_Object EpC_CallK(EpC_Function func, const int num_args, EpC_Object* args, EpC_Object kwargs)
{
	PyObject* pargs = PyTuple_New(num_args);

	for (int i = 0; i < num_args; ++i)
	{
		PyTuple_SetItem(pargs, i, args[i]);
	}

	PyObject* ret_value = PyObject_Call(func, pargs, kwargs);
	// Py_DECREF(pargs);
	return ret_value;
}

EMBEDPYTHONLIB_API void EpC_Print(EpC_Object arg1, ...)
{
	printf( "%s", EpC_AsChar(arg1));

	va_list valist;
	va_start(valist, arg1);

	while (1)
	{
		EpC_Object arg_ = va_arg(valist, EpC_Object);
		if (arg_ == 0)
		{
			break;
		}

		printf(" %s", EpC_AsChar(arg_));
	}

	va_end(valist);

	printf("\n");
}

EMBEDPYTHONLIB_API const char* EpC_TypeAsChar(EpC_Object object)
{
	PyTypeObject* ob_type = object->ob_type;
	const char* tp_name = ob_type->tp_name;
	return tp_name;
}

/*
 *	C++ interface implementation
 */

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
	object = 0;
}

Ep_Object::Ep_Object(PyObject* v)
{
	object = v;
}

Ep_Object::Ep_Object(const char* cstr)
{
	object = PyUnicode_FromString(cstr);
}

Ep_Object::Ep_Object(const int int_value)
{
	object = PyLong_FromLong(int_value);
}

Ep_Object::Ep_Object(const double float_value)
{
	object = PyFloat_FromDouble(float_value);
}

PyObject* Ep_Object::get()
{
	return object;
}

EMBEDPYTHONLIB_API std::ostream& operator<<(std::ostream& os, Ep_Object ep_obj)
{
	PyObject* object = ep_obj.get();

	// learned at https://stackoverflow.com/questions/5356773/python-get-string-representation-of-pyobject
	PyObject* repr = PyObject_Repr(object);
	PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
	const char *bytes = PyBytes_AS_STRING(str);

	os << bytes;

	Py_XDECREF(repr);
	Py_XDECREF(str);
	return os;
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

Ep_Object Ep_Function::call(Ep_Object* arg1, ...)
{
	PyObject* parg1 = arg1->get();
	if (!parg1) {
		Py_DECREF(parg1);
		// Py_DECREF(pModule);
		cerr << "Cannot convert argument\n";
		return Ep_Object();
	}

	vector<PyObject*> arg_list;
	arg_list.push_back(parg1);

	va_list valist;
	va_start(valist, arg1);

	while (1)
	{
		Ep_Object* arg_ = va_arg(valist, Ep_Object*);
		if ( arg_ == 0 )
		{
			break;
		}

		PyObject* parg_ = arg_->get();
		arg_list.push_back(parg_);
	}
	
	va_end(valist);

	int num_args = arg_list.size();
	PyObject* pargs = PyTuple_New(num_args);

	for (int i = 0; i < num_args; ++i)
	{
		PyTuple_SetItem(pargs, i, arg_list[i]);
	}

	PyObject* ret_value = PyObject_CallObject(function, pargs);

	return Ep_Object(ret_value);
}

Ep_Object Ep_Function::operator()()
{
	return Ep_Function::call();
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1)
{
	return Ep_Function::call( &arg1, 0 );
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2)
{
	return Ep_Function::call(&arg1, &arg2, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, &arg5, 0);
}

Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, &arg5, &arg6, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, &arg8, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8, Ep_Object& arg9)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, &arg8, &arg9, 0);
}
Ep_Object Ep_Function::operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
	Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8, Ep_Object& arg9, Ep_Object& arg10)
{
	return Ep_Function::call(&arg1, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, &arg8, &arg9, &arg10, 0);
}

EMBEDPYTHONLIB_API Ep_Function Ep_FromImport(const char* c_pname, const char* c_funcname)
{
	PyObject* function = EpC_FromImport(c_pname, c_funcname);
	return Ep_Function(function);
}



