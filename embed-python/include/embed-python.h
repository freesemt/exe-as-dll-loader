#include <iostream>

#ifdef EMBEDPYTHONLIB_EXPORTS
#define EMBEDPYTHONLIB_API __declspec(dllexport)
#else
#define EMBEDPYTHONLIB_API __declspec(dllimport)
#endif

#include <Python.h>

/*
 *	C interface
 */
typedef PyObject* EpC_Object;
typedef PyObject* EpC_Module;
typedef PyObject* EpC_Function;

EMBEDPYTHONLIB_API void EpC_Initialize(void);
EMBEDPYTHONLIB_API int EpC_Finalize(void);
EMBEDPYTHONLIB_API void EpC_AddSysPath(const char* path);
EMBEDPYTHONLIB_API EpC_Function EpC_FromImport(const char* package, const char* function);
EMBEDPYTHONLIB_API EpC_Module EpC_Import(const char* package);
EMBEDPYTHONLIB_API EpC_Function EpC_GetMethod(EpC_Module module, const char* name);
EMBEDPYTHONLIB_API EpC_Object EpC_GetAttrString(EpC_Object object, const char* name);
EMBEDPYTHONLIB_API int EpC_SetAttrString(EpC_Object object, const char* name, EpC_Object value);

EMBEDPYTHONLIB_API void EpC_DECREF(EpC_Object object);

EMBEDPYTHONLIB_API EpC_Object EpC_CoString(const char* cstr);
EMBEDPYTHONLIB_API EpC_Object EpC_CoInt(const int int_value);
EMBEDPYTHONLIB_API EpC_Object EpC_CoFloat(const double float_value);
EMBEDPYTHONLIB_API EpC_Object EpC_CoNone();
EMBEDPYTHONLIB_API EpC_Object EpC_CoList(const int num_items);
EMBEDPYTHONLIB_API int EpC_List_SetItem(EpC_Object list, int index, EpC_Object item);
EMBEDPYTHONLIB_API EpC_Object EpC_List_GetItem(EpC_Object list, int index);
EMBEDPYTHONLIB_API EpC_Object EpC_CoTuple(const int num_items);
EMBEDPYTHONLIB_API int EpC_Tuple_SetItem(EpC_Object tuple, int index, EpC_Object item);
EMBEDPYTHONLIB_API EpC_Object EpC_Tuple_GetItem(EpC_Object tuple, int index);
EMBEDPYTHONLIB_API EpC_Object EpC_CoDict();
EMBEDPYTHONLIB_API int EpC_Dict_SetItemString(EpC_Object dict, const char* key, EpC_Object value);

EMBEDPYTHONLIB_API const char* EpC_AsChar(EpC_Object object);
EMBEDPYTHONLIB_API int EpC_AsInt(EpC_Object object);
EMBEDPYTHONLIB_API double EpC_AsDouble(EpC_Object object);

EMBEDPYTHONLIB_API EpC_Object EpC_CallS(EpC_Function func, EpC_Object arg1, ...);
EMBEDPYTHONLIB_API EpC_Object EpC_CallN(EpC_Function func, const int n, EpC_Object* args);
EMBEDPYTHONLIB_API EpC_Object EpC_CallK(EpC_Function func, const int n, EpC_Object* args, EpC_Object kwargs);
EMBEDPYTHONLIB_API void EpC_Print(EpC_Object arg1, ...);

EMBEDPYTHONLIB_API const char* EpC_TypeAsChar(EpC_Object object);

EMBEDPYTHONLIB_API const int EpC_NumpyInitialize();
EMBEDPYTHONLIB_API const double* EpC_NumpyArrayAsDoubleArray(EpC_Object object, int depth);
EMBEDPYTHONLIB_API EpC_Object EpC_CoDoubleNumpyArray(int nd, int* dims, const double* data);

/*
 *	C++ interface
 */
EMBEDPYTHONLIB_API void Ep_Initialize(void);
EMBEDPYTHONLIB_API int Ep_Finalize(void);
EMBEDPYTHONLIB_API void Ep_AddSysPath(const char* path);

class EMBEDPYTHONLIB_API Ep_Object
{
private:
	PyObject* object;
public:
	Ep_Object();
	Ep_Object(PyObject* v);
	Ep_Object(const char* cstr);
	Ep_Object(const int int_value);
	Ep_Object(const double float_value);
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
