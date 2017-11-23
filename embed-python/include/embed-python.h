#include <iostream>
#pragma once
#ifdef EMBEDPYTHONLIB_EXPORTS
#define EMBEDPYTHONLIB_API __declspec(dllexport)
#else
#define EMBEDPYTHONLIB_API __declspec(dllimport)
struct PyObject;
#endif

EMBEDPYTHONLIB_API void Ep_Initialize(void);
EMBEDPYTHONLIB_API int Ep_Finalize(void);

EMBEDPYTHONLIB_API void Ep_AddSysPath(const char* path);

class EMBEDPYTHONLIB_API Ep_Object
{
private:
	PyObject* value;
public:
	Ep_Object();
	Ep_Object(PyObject* v);
	Ep_Object(const char* cstr);
	Ep_Object(const int int_value);
	PyObject* get();
};

EMBEDPYTHONLIB_API std::ostream& operator<<(std::ostream& os, Ep_Object ep_obj);

class EMBEDPYTHONLIB_API Ep_Function
{
private:
	PyObject* function;
	Ep_Object call();
	Ep_Object call(Ep_Object* arg1, ...);
public:
	Ep_Function();
	Ep_Function(PyObject* f);
	Ep_Object operator()();
	Ep_Object operator()(Ep_Object& arg1);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
		Ep_Object& arg6);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
		Ep_Object& arg6, Ep_Object& arg7);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
		Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
		Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8, Ep_Object& arg9);
	Ep_Object operator()(Ep_Object& arg1, Ep_Object& arg2, Ep_Object& arg3, Ep_Object& arg4, Ep_Object& arg5,
		Ep_Object& arg6, Ep_Object& arg7, Ep_Object& arg8, Ep_Object& arg9, Ep_Object& arg10);
};

EMBEDPYTHONLIB_API Ep_Function Ep_FromImport(const char* package, const char* function);