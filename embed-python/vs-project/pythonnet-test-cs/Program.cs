using System;
using System.Collections.Generic;
using Python.Runtime;

namespace pythonnet_test_cs
{
    class Program
    {
        static void test1()
        {
            using (Py.GIL())
            {
                // PythonEngine.Initialize();
                dynamic np = Py.Import("numpy");
                Console.WriteLine(np.cos(np.pi * 2));

                dynamic sin = np.sin;
                Console.WriteLine(sin(5));

                double c = np.cos(5) + sin(5);
                Console.WriteLine(c);

                dynamic a = np.array(new List<float> { 1, 2, 3 });
                Console.WriteLine(a.dtype);
                Console.WriteLine(a);

                // dynamic b = np.array(new List<float> { 6, 5, 4 }, dtype: np.int32);
                dynamic b = np.array(new List<float> { 6, 5, 4 });
                Console.WriteLine(b.dtype);
                Console.WriteLine(b);

                Console.WriteLine(a * b);
            }
        }

        static void Main(string[] args)
        {
            test1();
        }
    }
}
