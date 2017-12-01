using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace embed_python_test_cs
{
    class test
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
        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_AsChar@@YAPEBDPEAU_object@@@Z")]
        private extern static IntPtr EpC_AsChar(IntPtr pyobj);

        [DllImport("embed-python-lib.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?EpC_CallN@@YAPEAU_object@@PEAU1@HPEAPEAU1@@Z")]
        private extern static IntPtr EpC_CallN(IntPtr function, int n, IntPtr[] args);

        static void Main(string[] args)
        {
            System.Console.WriteLine("Test C#\n");

            EpC_Initialize();
            EpC_AddSysPath("..\\..\\..\\..\\..\\scripts".ToCharArray());

            IntPtr hello = EpC_FromImport( "hello".ToCharArray(), "hello".ToCharArray());
            IntPtr name = EpC_CoString( "Keiko-san".ToCharArray());
            IntPtr[] pyargs1 = { name };
            EpC_CallN(hello, 1, pyargs1);

            IntPtr add = EpC_FromImport("arithmetic".ToCharArray(), "add".ToCharArray());
            IntPtr one = EpC_CoInt(1);
            IntPtr two = EpC_CoInt(2);
            IntPtr[] i_args2 = { one, two };
            IntPtr int_result = EpC_CallN(add, 2, i_args2);
            System.Console.WriteLine(Marshal.PtrToStringAnsi(EpC_AsChar(int_result)));

            IntPtr pi = EpC_CoFloat(3.14);
            IntPtr e = EpC_CoFloat(2.72);
            IntPtr[] f_args2 = { pi, e };
            IntPtr float_result = EpC_CallN(add, 2, f_args2);
            System.Console.WriteLine(Marshal.PtrToStringAnsi(EpC_AsChar(float_result)));

            // TODO: handling of unicode string

            EpC_Finalize();
        }
    }
}
