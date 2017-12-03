using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Python.Runtime;

namespace pythonnet_test_cs
{
    class Program
    {
        static void TestReadmeOldStyle()
        {
            PythonEngine.Initialize();
            dynamic np;
            try
            {
                np = Py.Import("numpy");
            }
            catch (PythonException)
            {
                Console.WriteLine("Numpy or dependency not installed");
                return;
            }

            Console.WriteLine(np.cos(np.pi * 2).ToString());

            dynamic sin = np.sin;
            Console.WriteLine(sin(5).ToString());

            double c = np.cos(5) + sin(5);
            // Console.WriteLine(c);

            dynamic a = np.array(new List<float> { 1, 2, 3 });
            Console.WriteLine(a.dtype.ToString());

            // dynamic b = np.array(new List<float> { 6, 5, 4 }, Py.kw("dtype", np.int32));
            dynamic b = np.array(new List<float> { 6, 5, 4 });
            Console.WriteLine(b.dtype.ToString());

            Console.WriteLine((a * b).ToString());
            PythonEngine.Shutdown();
        }
        static void TestReadmeNewStyle()
        {
            using (Py.GIL())
            {
                dynamic np = Py.Import("numpy");
                Console.WriteLine(np.cos(np.pi * 2));

                dynamic sin = np.sin;
                Console.WriteLine(sin(5));

                double c = np.cos(5) + sin(5);
                Console.WriteLine(c);

                dynamic a = np.array(new List<float> { 1, 2, 3 });
                Console.WriteLine(a.dtype);

                // dynamic b = np.array(new List<float> { 6, 5, 4 }, dtype: np.int32);
                dynamic b = np.array(new List<float> { 6, 5, 4 });
                Console.WriteLine(b.dtype);

                Console.WriteLine(a * b);
            }
        }
        static void Main(string[] args)
        {
            // TestReadmeOldStyle();
            TestReadmeNewStyle();
        }
    }
}
