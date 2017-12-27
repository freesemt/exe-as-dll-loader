using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Dynamic;
using System.Reflection;
using System.IO;
using System.Text.RegularExpressions;
using System.Runtime.ExceptionServices;
using System.Security;

namespace EmbPython
{
    public class Ep
    {
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Initialize@@YAXXZ")]
        private extern static void EpC_Initialize();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_NumpyInitialize@@YA?BHXZ")]
        private extern static int EpC_NumpyInitialize();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Finalize@@YAHXZ")]
        private extern static int EpC_Finalize();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_AddSysPath@@YAXPEBD@Z")]
        private extern static void EpC_AddSysPath(char[] path);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_FromImport@@YAPEAU_object@@PEBD0@Z")]
        private extern static IntPtr EpC_FromImport(char[] package, char[] function);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Import@@YAPEAU_object@@PEBD@Z")]
        private extern static IntPtr EpC_Import(char[] package);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_GetMethod@@YAPEAU_object@@PEAU1@PEBD@Z")]
        private extern static IntPtr EpC_GetMethod(IntPtr module, char[] method);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_GetAttrString@@YAPEAU_object@@PEAU1@PEBD@Z")]
        private extern static IntPtr EpC_GetAttrString(IntPtr pyobj, char[] name);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_SetAttrString@@YAHPEAU_object@@PEBD0@Z")]
        private extern static int EpC_SetAttrString(IntPtr pyobj, char[] name, IntPtr value);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_DECREF@@YAXPEAU_object@@@Z")]
        private extern static void EpC_DECREF(IntPtr pyobj);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoString@@YAPEAU_object@@PEBD@Z")]
        private extern static IntPtr EpC_CoString(char[] path);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoInt@@YAPEAU_object@@H@Z")]
        private extern static IntPtr EpC_CoInt(int int_value);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoFloat@@YAPEAU_object@@N@Z")]
        private extern static IntPtr EpC_CoFloat(double double_value);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoNone@@YAPEAU_object@@XZ")]
        private extern static IntPtr EpC_CoNone();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoList@@YAPEAU_object@@H@Z")]
        private extern static IntPtr EpC_CoList(int num_items);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_List_SetItem@@YAHPEAU_object@@H0@Z")]
        private extern static int EpC_List_SetItem(IntPtr list,int index, IntPtr item);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_List_GetItem@@YAPEAU_object@@PEAU1@H@Z")]
        private extern static IntPtr EpC_List_GetItem(IntPtr list, int index);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoTuple@@YAPEAU_object@@H@Z")]
        private extern static IntPtr EpC_CoTuple(int num_items);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Tuple_SetItem@@YAHPEAU_object@@H0@Z")]
        private extern static int EpC_Tuple_SetItem(IntPtr list, int index, IntPtr item);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Tuple_GetItem@@YAPEAU_object@@PEAU1@H@Z")]
        private extern static IntPtr EpC_Tuple_GetItem(IntPtr list, int index);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoDict@@YAPEAU_object@@XZ")]
        private extern static IntPtr EpC_CoDict();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Dict_SetItemString@@YAHPEAU_object@@PEBD0@Z")]
        private extern static IntPtr EpC_Dict_SetItemString(IntPtr dict, char[] key, IntPtr val);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CallN@@YAPEAU_object@@PEAU1@HPEAPEAU1@@Z")]
        private extern static IntPtr EpC_CallN(IntPtr function, int n, IntPtr[] args);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CallK@@YAPEAU_object@@PEAU1@HPEAPEAU1@0@Z")]
        private extern static IntPtr EpC_CallK(IntPtr function, int n, IntPtr[] args, IntPtr kwargs);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_AsChar@@YAPEBDPEAU_object@@@Z")]
        private extern static IntPtr EpC_AsChar(IntPtr pyobj);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_AsInt@@YAHPEAU_object@@@Z")]
        private extern static int EpC_AsInt(IntPtr pyobj);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_NumpyArrayAsDoubleArray@@YAPEBNPEAU_object@@H@Z")]
        private extern static IntPtr EpC_NumpyArrayAsDoubleArray(IntPtr ndarray, int depth);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoDoubleNumpyArray@@YAPEAU_object@@HPEAHPEBN@Z")]
        private extern static IntPtr EpC_CoDoubleNumpyArray(int nd, IntPtr dims,IntPtr data);

        const bool DEBUG = false;
        private static bool EpC_isOpen = false;

        public static void Initialize()
        {
            EpC_Initialize();
            EpC_NumpyInitialize();
            EpC_isOpen = true;
        }

        public static int Finalize()
        {
            int ret = EpC_Finalize();
            EpC_isOpen = false;
            return ret;
        }

        public static void AddSysPath(String path)
        {
            EpC_AddSysPath(path.ToCharArray());
        }

        public static int dynamicToEpObject( dynamic arg, out IntPtr ret_value )
        {
            Type type_ = arg.GetType();
            string type = type_.ToString();
            int ref_flag = 0;
            if (DEBUG) { Console.Write("type={0}\n", type); }

            if (type == "System.Double")
            {
                // Console.Write("EpC_CoFloat\n");
                ret_value = EpC_CoFloat(Convert.ToDouble(arg));
            }
            else if (type == "System.Int32")
            {
                // Console.Write("EpC_CoInt\n");
                ret_value = EpC_CoInt(Convert.ToInt32(arg));
            }
            else if (type == "System.String")
            {
                // Console.Write("EpC_CoString\n");
                ret_value = EpC_CoString(arg.ToCharArray());
            }
            else if (type == "EmbPython.Ep+Object")
            {
                ret_value = arg.getPyObject(); ;
            }
            else if (type.IndexOf("<>f__AnonymousType") == 0)
            {
                // (type == "<>f__AnonymousType0`1[System.Int32]" || type == "<>f__AnonymousType1`1[System.Int32]")
                IntPtr dict = EpC_CoDict();
                PropertyInfo[] pi = type_.GetProperties();
                foreach (PropertyInfo p in pi)
                {
                    //Get the name of the prperty
                    string pname = p.Name;
                    dynamic pvalue = p.GetValue(arg);
                    // Console.WriteLine("Name={0}, Value={1}", pname, pvalue);
                    IntPtr pobj;
                    dynamicToEpObject(pvalue, out pobj);
                    EpC_Dict_SetItemString(dict, p.Name.ToCharArray(), pobj);
                }
                ret_value = dict;
                ref_flag = 1;
            }
            else if (type == "System.Collections.Generic.Dictionary`2[System.String,System.Object]")
            {
                IntPtr dict = EpC_CoDict();
                foreach (KeyValuePair<string, dynamic> pair in arg)
                {
                    //  Console.WriteLine(string.Format("Key : {0} / Value : {1}", pair.Key, pair.Value));
                    IntPtr dict_val;
                    dynamicToEpObject(pair.Value, out dict_val);
                    EpC_Dict_SetItemString(dict, pair.Key.ToCharArray(), dict_val);
                }
                ret_value = dict;
                ref_flag = 1;
            }
            else if (type == "System.Collections.Generic.List`1[System.Object]")
            {
                // Console.Write("List.Count={0}\n", arg.Count);
                IntPtr list_ = EpC_CoList(arg.Count);
                for (int j = 0; j < arg.Count; ++j)
                {
                    IntPtr pobj;
                    dynamicToEpObject(arg[j], out pobj);
                    EpC_List_SetItem(list_, j, pobj);
                }
                ret_value = list_;
                //Console.Write("List.ret_value={0}\n", new Object(list_).ToString());
            }
            else if (type == "System.Collections.Generic.List`1[System.Double]")
            {
                // Console.Write("List.Count={0}\n", arg.Count);
                IntPtr list_ = EpC_CoList(arg.Count);
                for (int j = 0; j < arg.Count; ++j)
                {
                    IntPtr f = EpC_CoFloat(Convert.ToDouble(arg[j]));
                    EpC_List_SetItem(list_, j, f);
                }
                ret_value = list_;
            }
            else
            {
                Console.Write("Unsupported type: {0}\n", type);
                ret_value = EpC_CoNone();
            }
            if (DEBUG)
            {
                Console.Write("dynamicToEpObject: ret_value_ptr={0}\n", ret_value );
                Console.Write("dynamicToEpObject: ret_value={0}\n", new Object(ret_value).ToString());
            }

            return ref_flag;
        }

        [HandleProcessCorruptedStateExceptions]
        [SecurityCritical]
        private static int Try_DECREF( IntPtr pyobj )
        {
            try
            {
                EpC_DECREF(pyobj); 
            }
            catch (Exception e)
            {
                System.Console.WriteLine(e.Message);
                return 1;
            }

            return 0;
        }

        public class Object : DynamicObject
        {
            private static dynamic np = new Module();
            private IntPtr pyobject;
  
            public Object( IntPtr object_ptr )
            {
                this.pyobject = object_ptr;
            }
            ~Object()
            {
                if (EpC_isOpen)
                {
                    // we can't catch an exception here because this call causes an error later in Finalize()
                    // Try_DECREF(pyobject);    
                }
            }
            public override String ToString()
            {
                return Marshal.PtrToStringAnsi(EpC_AsChar(pyobject));
            }
            public IntPtr getPyObject()
            {
                return pyobject;
            }
            public static Object operator *(Object lhs, Object rhs)
            {
                if (!np.isOk())
                {
                    np = Import("numpy");
                }
                return np.prod( new List<dynamic> {  lhs, rhs }, new { axis=0 } );
            }
            public override bool TryGetMember(
                  GetMemberBinder binder, out object result)
            {
                IntPtr attr_ptr = EpC_GetAttrString(pyobject, binder.Name.ToCharArray());
                result = new Object(attr_ptr);
                return true;
            }
            public override bool TrySetMember(
                SetMemberBinder binder, object value)
            {
                dynamic value_ = value;
                EpC_SetAttrString( this.pyobject, binder.Name.ToCharArray(), value_.getPyObject() );
                return true;
            }
        }

        public class Function : DynamicObject
        {
            private IntPtr pyobject;

            public Function(IntPtr func_ptr)
            {
                pyobject = func_ptr;
            }
            ~Function()
            {
                if (EpC_isOpen)
                {
                    EpC_DECREF(pyobject);
                }
            }
            public Object call(params dynamic[] args)
            {
                // Console.WriteLine("Function.call");
                IntPtr kwargs= EpC_CoDict(); ;
                int kwargs_count = 0;

                IntPtr[] arg_ptr_list = new IntPtr[args.Length];
                for (int i = 0; i < args.Length; i++)
                {
                    dynamic arg = args[i];
                    // Console.Write(arg + "\n");
                    IntPtr ret_value;
                    int ret_flag = dynamicToEpObject( arg, out ret_value );
                    if ( ret_flag == 0 )
                    {
                        arg_ptr_list[i] = ret_value;
                    }
                    else
                    {
                        kwargs = ret_value;
                        kwargs_count++;
                    }
                }

                // IntPtr result = EpC_CallN(pyobject, args.Length, arg_ptr_list);
                IntPtr result = EpC_CallK(pyobject, args.Length- kwargs_count, arg_ptr_list, kwargs);

                return new Object(result);
            }

            public override bool TryInvoke(
                InvokeBinder binder, object[] args, out object result)
            {
                result = call(args);
                return true;
            }
        }

        public delegate Object VariableArgsFunction(params dynamic[] arguments);

        public class Module : DynamicObject
        {
            private IntPtr pyobject;
            public Module()
            {
                pyobject = (IntPtr)0;
            }
            public Module(IntPtr object_ptr)
            {
                pyobject = object_ptr;
            }
            ~Module()
            {
                if (EpC_isOpen && isOk())
                {
                    EpC_DECREF(pyobject);
                }
            }
            public override bool TryGetMember(
                  GetMemberBinder binder, out object result)
            {
                string name = binder.Name;
                // Console.WriteLine("TryGetMember: " + name);

                IntPtr method_ptr = EpC_GetMethod(pyobject, name.ToCharArray());
                Function f = new Function(method_ptr);

                result = f;
                return true;
            }
            public bool isOk()
            {
                return pyobject != (IntPtr)0;
            }
        }

        public static Module Import(String module_name)
        {
            IntPtr module_ptr = EpC_Import(module_name.ToCharArray());
            return new Module(module_ptr);
        }

        public static VariableArgsFunction FromImport(String module_name, String func_name)
        {
            IntPtr func_ptr = EpC_FromImport(module_name.ToCharArray(), func_name.ToCharArray());

            Function f = new Function(func_ptr);

            return f.call;
        }

        public class Image : DynamicObject
        {
            private int width;
            private int height;
            private double[] data;

            public Image()
            {
                width = 0;
                height = 0;
                data = new double[0];
            }
            ~Image()
            {
                //
            }
            public Image(dynamic ndarray)
            {
                IntPtr shape = ndarray.shape.getPyObject();
                width = EpC_AsInt( EpC_Tuple_GetItem(shape, 0) );
                height = EpC_AsInt(EpC_Tuple_GetItem(shape, 1));
                IntPtr pdata = EpC_NumpyArrayAsDoubleArray(ndarray.getPyObject(), 2);
                int size = width * height;
                Console.Write( "Image: size={0}\n", size);
                data = new double[size];
                Marshal.Copy(pdata, data, 0, size);
            }
            public Tuple<int, int> shape()
            {
                return new Tuple<int, int>(width, height);
            }
            public double this[int i, int j]
            {
                set { this.data[i * width + j] = value; }
                get { return this.data[i * width + j]; }
            }
            public override string ToString()
            {
                StringWriter writer = new StringWriter();
                writer.Write("[\n");
                for (int i = 0; i < height; ++i)
                {
                    writer.Write( "  [" );
                    for (int j = 0; j < width; ++j)
                    {
                        if ( j> 0 )
                        {
                            writer.Write(" ");
                        }
                        writer.Write("{0}", data[width*i + j]);
                    }
                    writer.Write("]\n");
                }
                writer.Write("]\n");
                return writer.ToString();
            }
            public Object makeNdArray()
            {
                // copy dims to unmanaged area
                int[] dims = { width, height };
                int dims_size = Marshal.SizeOf(dims[0]) * dims.Length;
                IntPtr dims_ = Marshal.AllocHGlobal(dims_size);
                Marshal.Copy(dims, 0, dims_, dims.Length);

                // copoy data to unmanaged area
                int data_size = Marshal.SizeOf(data[0]) * data.Length;
                IntPtr data_ = Marshal.AllocHGlobal(data_size);
                Marshal.Copy(data, 0, data_, data.Length);
                IntPtr pyobject = EpC_CoDoubleNumpyArray(2, dims_, data_);
                return new Object(pyobject);
            }
        }
    }
}
