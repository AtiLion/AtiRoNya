using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;

using AtiRoNyaSDK;

namespace RuntimeDumper.Modules
{
    internal class GameAssembly
    {
        #region IL2CPP Functions
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_image_get_name(IntPtr image);
        #endregion

        #region Assembly Properties
        public IntPtr Pointer { get; private set; }
        public string Name { get; private set; }
        #endregion

        public GameAssembly(IntPtr image)
        {
            // Setup properties
            Pointer = image;
            Name = Path.GetFileNameWithoutExtension(Marshal.PtrToStringAnsi(il2cpp_image_get_name(image)));
        }
    }

    internal class AssemblyDump : IModule<GameAssembly>
    {
        #region IL2CPP Functions
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_domain_get_assemblies(IntPtr domain, ref uint size);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_assembly_get_image(IntPtr assembly);
        #endregion

        #region Native Assembly Data
        private uint _index;
        private IntPtr[] _assemblies;
        #endregion

        public AssemblyDump()
        {
            // Initialize local variables
            uint size = 0;

            // Setup variables
            _index = 0;
            _assemblies = NativeSDK.PtrToArry<IntPtr>(il2cpp_domain_get_assemblies(NativeSDK.atironya_get_il2cpp_domain(), ref size), size);
        }

        #region IModule Variables
        private Dictionary<IntPtr, object> _stack = new Dictionary<IntPtr, object>();
        #endregion
        #region IModule Functions
        public void PushToStack(GameAssembly assembly, object value)
        {
            if (!IsOnStack(assembly))
                _stack.Add(assembly.Pointer, value);
        }
        public bool IsOnStack(GameAssembly assembly) => _stack.ContainsKey(assembly.Pointer);
        public object GrabFromStack(GameAssembly assembly)
        {
            if (IsOnStack(assembly))
                return _stack[assembly.Pointer];
            return null;
        }

        public bool HasNext() => _index < _assemblies.Length;
        public GameAssembly Next()
        {
            IntPtr output = _assemblies[_index];
            if (output == IntPtr.Zero) return null;

            output = il2cpp_assembly_get_image(output);
            if (output == IntPtr.Zero) return null;

            _index++;
            if (_stack.ContainsKey(output)) return null;
            return new GameAssembly(output);
        }
        #endregion
    }
}
