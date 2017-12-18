using System;
using System.Collections.Generic;
using System.Reflection;

namespace delegate_with_named_parameters
{
    class Program
    {
        public delegate int VariableArgsFunction(params dynamic[] arguments);
        public static int call(params dynamic[] args)
        {
            for (int i = 0; i < args.Length; i++)
            {
                dynamic arg = args[i];
                Type t = arg.GetType();
                string type = t.ToString();
                Console.Write("type={0}\n", type);
                PropertyInfo[] pi = t.GetProperties();
                foreach (PropertyInfo p in pi)
                {
                    //Get the name of the prperty
                    Console.WriteLine("Name={0}, Value={1}", p.Name, p.GetValue(arg));
                }
            }
            return -1;
        }
        static void Main(string[] args)
        {
            VariableArgsFunction vf = call;
            // use an anonymous type in stead of a named argument
            Console.Write("f(5)={0}\n", vf(5, new { axis = 0 }));
        }
    }
}
