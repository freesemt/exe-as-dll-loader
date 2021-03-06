﻿using System;
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

        static void TestKwArgs()
        {
            dynamic increment = Ep.FromImport("kwargs_test", "increment");
            dynamic ret_val_1 = increment( 2 );
            Console.Write("ret_val_1={0}\n", ret_val_1.ToString());
            dynamic ret_val_2 = increment(2, new { inc = 10 } );
            Console.Write("ret_val_2={0}\n", ret_val_2.ToString());
        }

        static void TestNumpy()
        {
            Console.Write("TestNumpy\n");
            dynamic np = Ep.Import("numpy");
            dynamic a = np.array(new List<double>{ 1, 2, 3 });
            dynamic b = np.array(new List<double>{ 4, 5, 6 });
            Console.WriteLine(a.ToString());
            Console.WriteLine(b.ToString());
            dynamic s = np.sum(a);
            Console.WriteLine(s.ToString());
            dynamic p = np.prod(new List<dynamic> { a, b }, new { axis = 0 });
            Console.WriteLine(p.ToString());
            Console.WriteLine(p.shape.ToString());
            Console.WriteLine((a*b).ToString());
        }

        static void TestFabio()
        {
            Console.Write("TestFabio\n");
            dynamic fabio = Ep.Import("fabio");
            dynamic image = fabio.open("..\\..\\..\\..\\..\\data\\min_data.tif");
            Console.WriteLine(image.data.shape.ToString());
            dynamic plt = Ep.Import("matplotlib.pyplot");
            plt.imshow(image.data);
            plt.show();
            Ep.Image image_ = new Ep.Image(image.data);
            Console.WriteLine(image_.shape().ToString());
            Console.WriteLine(image_.ToString());
            image_[0, 0] = 0;
            image_[0, 1] = 1;
            image_[1, 0] = 1;
            image_[1, 1] = 0;
            Console.WriteLine(image_.ToString());
            dynamic new_ndarray = image_.makeNdArray();
            Console.WriteLine(new_ndarray.ToString());
            image.data = new_ndarray;
            plt.imshow(image.data);
            plt.show();
        }

        static void Main(string[] args)
        {
            Ep.Initialize();
            Ep.AddSysPath("..\\..\\..\\..\\..\\scripts");

            TestBasicsFromImport();
            TestBasicsGenericImport();
            TestKwArgs();
            TestNumpy();
            TestFabio();

            Ep.Finalize();
        }
    }
}
