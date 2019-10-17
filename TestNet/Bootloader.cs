using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Bootloader
{
    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall)]
    public extern static IntPtr atironya_get_domain();
    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
    public extern static IntPtr atironya_get_assembly(string name);
    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
    public extern static IntPtr atironya_get_class(string name_space, string name, IntPtr assembly);
    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
    public extern static IntPtr atironya_get_method(string name, IntPtr klass, int paramcount);
    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall)]
    public extern unsafe static IntPtr atironya_execute(IntPtr method, IntPtr obj, void** param);

    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
    public extern static IntPtr atironya_tostring(string text);
    [DllImport("AtiRoNya", CallingConvention = CallingConvention.StdCall)]
    public extern static IntPtr atironya_from_mono(IntPtr obj);

    public static int Main(string args)
    {
        Console.WriteLine("Hello from .NET");
        Console.Title = "Yeeter";

        // ------------- UnityEngine ------------------ //
        IntPtr UnityEngine = atironya_get_assembly("UnityEngine");
        IntPtr Debug = atironya_get_class("UnityEngine", "Debug", UnityEngine);
        IntPtr Log = atironya_get_method("Log", Debug, 1);
        IntPtr Text = atironya_tostring("This shit works cunt");

        Console.WriteLine("UnityEngine: " + UnityEngine.ToInt64());
        Console.WriteLine("Debug: " + Debug.ToInt64());
        Console.WriteLine("Log: " + Log.ToInt64());
        Console.WriteLine("String: " + Text.ToInt64());
        Exec(Log, new IntPtr[] { Text });

        // --------------- Assembly-CSharp ---------------------- //
        IntPtr AssemblyCSharp = atironya_get_assembly("Assembly-CSharp");
        IntPtr VRCTrackingManager = atironya_get_class("", "VRCTrackingManager", AssemblyCSharp);
        IntPtr IsInitialized = atironya_get_method("IsInitialized", VRCTrackingManager, 0);

        Console.WriteLine("Assembly-CSharp: " + AssemblyCSharp.ToInt64());
        Console.WriteLine("VRCTrackingManager: " + VRCTrackingManager.ToInt64());
        Console.WriteLine("IsInitialized: " + IsInitialized.ToInt64());
        Console.WriteLine("Result: " + ConvertToBool(Exec(IsInitialized, new IntPtr[0])));

        return 0;
    }

    unsafe static IntPtr Exec(IntPtr func, IntPtr[] param)
    {
        IntPtr array = Marshal.AllocHGlobal(param.Length * sizeof(void*));
        IntPtr ret = IntPtr.Zero;

        try
        {
            void** ptrArray = (void**)array.ToPointer();

            for(int i = 0; i < param.Length; i++)
                ptrArray[i] = param[i].ToPointer();
            ret = atironya_execute(func, IntPtr.Zero, ptrArray);
        }
        finally
        {
            Marshal.FreeHGlobal(array);
        }
        return ret;
    }
    unsafe static bool ConvertToBool(IntPtr obj)
    {
        return *(bool*)atironya_from_mono(obj).ToPointer();
    }
}
