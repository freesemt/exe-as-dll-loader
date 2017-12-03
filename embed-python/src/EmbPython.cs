using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq.Expressions;

namespace EmbPython
{
    public class Ep
    {
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Initialize@@YAXXZ")]
        private extern static void EpC_Initialize();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_Finalize@@YAHXZ")]
        private extern static int EpC_Finalize();
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_AddSysPath@@YAXPEBD@Z")]
        private extern static void EpC_AddSysPath(char[] path);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_FromImport@@YAPEAU_object@@PEBD0@Z")]
        private extern static IntPtr EpC_FromImport(char[] package, char[] function);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoString@@YAPEAU_object@@PEBD@Z")]
        private extern static IntPtr EpC_CoString(char[] path);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoInt@@YAPEAU_object@@H@Z")]
        private extern static IntPtr EpC_CoInt(int int_value);
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CoFloat@@YAPEAU_object@@N@Z")]
        private extern static IntPtr EpC_CoFloat(double double_value);


        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CallN@@YAPEAU_object@@PEAU1@HPEAPEAU1@@Z")]
        private extern static IntPtr EpC_CallN(IntPtr function, int n, IntPtr[] args);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_AsChar@@YAPEBDPEAU_object@@@Z")]
        private extern static IntPtr EpC_AsChar(IntPtr pyobj);

        public class Context : System.IDisposable
        {
            public Context()
            {
                EpC_Initialize();
            }
            ~Context()
            {
                EpC_Finalize();
            }
            public void Dispose()
            {
            }
        }

        public static void Initialize()
        {
            EpC_Initialize();
        }

        public static int Finalize()
        {
            return EpC_Finalize();
        }

        public static void AddSysPath(String path)
        {
            EpC_AddSysPath(path.ToCharArray());
        }

        public class Object
        {
            private IntPtr pyobject;
            public Object()
            {

            }
            public Object( IntPtr object_ptr )
            {
                pyobject = object_ptr;
            }
            public Object(String arg)
            {
            }
            public override String ToString()
            {
                return Marshal.PtrToStringAnsi(EpC_AsChar(pyobject));
            }
        }

        public class Module
        {
            public Object array(List<double> list)
            {
                return new Object();
            }
        }

        public static Module Import(String module_name)
        {
            return new Module();
        }

        public delegate Object VariableArgsFunction(params dynamic[] arguments);

        public class Function
        {
            private IntPtr pyobject;

            public Function(IntPtr func_ptr)
            {
                pyobject = func_ptr;
            }

            public Object call(params dynamic[] args)
            {
                // Console.WriteLine("Function.call");

                IntPtr[] arg_ptr_list = new IntPtr[args.Length];
                for (int i = 0; i < args.Length; i++)
                {
                    dynamic arg = args[i];
                    // Console.Write(arg + "\n");
                    string type = arg.GetType().ToString();
                    // Console.Write(type + "\n");
                    if (type == "System.Double")
                    {
                        // Console.Write("EpC_CoFloat\n");
                        arg_ptr_list[i] = EpC_CoFloat(Convert.ToDouble(arg));
                    }
                    else if (type == "System.Int32")
                    {
                        // Console.Write("EpC_CoInt\n");
                        arg_ptr_list[i] = EpC_CoInt(Convert.ToInt32(arg));
                    }
                    else if (type == "System.String")
                    {
                        // Console.Write("EpC_CoString\n");
                        arg_ptr_list[i] = EpC_CoString(arg.ToCharArray());
                    }
                    else
                    {
                        Console.Write("Unsupported type: {0}\n", type);
                    }
                }

                IntPtr result = EpC_CallN(pyobject, args.Length, arg_ptr_list);

                return new Object(result);
            }
        }

        public static VariableArgsFunction FromImport(String module_name, String func_name)
        {
            IntPtr func_ptr = EpC_FromImport(module_name.ToCharArray(), func_name.ToCharArray());

            Function f = new Function(func_ptr);

            return f.call;
        }
    }
}
