using System;
using System.Collections.Generic;
using EmbPython;

namespace embpython_test
{
    class Program
    {
        static void TestBasicsFromImport()
        {
            Console.Write("TestBasicsFromImport\n");
            dynamic hello = Ep.FromImport("hello", "hello");
            hello("Keiko-san");

            dynamic add = Ep.FromImport("arithmetic", "add");
            dynamic int_value = add(1, 2);
            Console.Write("int_value={0}\n", int_value.ToString());

            dynamic float_value = add(3.14, 2.72);
            Console.Write("float_value={0}\n", float_value.ToString());
        }

        static void TestBasicsGenericImport()
        {
            Console.Write("TestBasicsGenericImport\n");
            dynamic package = Ep.Import("hello");
            dynamic hello = package.hello;
            hello("Keiko-san");

            dynamic arithmetic = Ep.Import("arithmetic");
            dynamic add = arithmetic.add;
            dynamic int_value = add(1, 2);
            Console.Write("int_value={0}\n", int_value.ToString());

            dynamic float_value = add(3.14, 2.72);
            Console.Write("float_value={0}\n", float_value.ToString());
        }

        static void TestNumpy()
        {
            Console.Write("TestNumpy\n");
            dynamic np = Ep.Import("numpy");
            dynamic a = np.array(new List<double>{ 1, 2, 3 });
            dynamic b = np.array(new List<double>{ 4, 5, 6 });
            Console.WriteLine(a.ToString());
            Console.WriteLine(b.ToString());
            Console.WriteLine(np.sum(a).ToString());
            Console.WriteLine((a*b).ToString());
        }

        static void Main(string[] args)
        {
            Ep.Initialize();
            Ep.AddSysPath("..\\..\\..\\..\\..\\scripts");

            TestBasicsFromImport();
            TestBasicsGenericImport();
            TestNumpy();

            Ep.Finalize();
        }
    }
}
