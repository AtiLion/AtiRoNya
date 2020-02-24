using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RuntimeDumper
{
    internal static class Logger
    {
        public static void Log(object log) =>
            Console.WriteLine("[RuntimeDumper] " + log.ToString());
    }
}
