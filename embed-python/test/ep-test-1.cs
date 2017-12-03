using System;
using System.Collections.Generic;
using EmbPython;

namespace embpython_test
{
    class Program
    {
        static void TestBasics()
        {
            Console.Write("TestBasics\n");
            dynamic hello = Ep.FromImport("hello", "hello");
            hello("Keiko-san");

            dynamic add = Ep.FromImport("arithmetic", "add");
            dynamic int_value = add(1, 2);
            Console.Write("int_value={0}\n", int_value.ToString());

            dynamic float_value = add(3.14, 2.72);
            Console.Write("float_value={0}\n", float_value.ToString());
        }

        static void TestNumpy()
        {
            Console.Write("TestNumpy\n");
            // Numpy
            /*
            dynamic np = Ep.Import("numpy");
            dynamic a = np.array(new List<double>{ 1, 2, 3 });      
            Console.WriteLine(a.ToString());
            */

        }
        static void Main(string[] args)
        {
            Ep.Initialize();
            Ep.AddSysPath("..\\..\\..\\..\\..\\scripts");

            TestBasics();
            TestNumpy();

            Ep.Finalize();
        }
    }
}
