using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;

namespace NativeHandler
{
    [ComImport, Guid("F20A83EB-FB00-454B-9D88-132F7EC693D7"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface INetDomain
    {
        void LoadAssembly([MarshalAs(UnmanagedType.LPStr)] string assembly);
        void LoadAssemblyAndExecute([MarshalAs(UnmanagedType.LPStr)] string assembly);
        void LoadMods([MarshalAs(UnmanagedType.LPStr)] string path);
    }
}
