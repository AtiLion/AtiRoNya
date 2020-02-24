using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;

using AtiRoNyaSDK;

using Mono.Cecil;

namespace RuntimeDumper.Modules
{
    internal class GameClass
    {
        #region IL2CPP Functions
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_class_get_name(IntPtr klass);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_class_get_namespace(IntPtr klass);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static int il2cpp_class_get_flags(IntPtr klass);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_class_get_interfaces(IntPtr klass, ref IntPtr iter);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_class_get_image(IntPtr klass);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_class_get_declaring_type(IntPtr klass);
        #endregion

        #region Class Properties
        public IntPtr Pointer { get; private set; }

        public string Name { get; private set; }
        public string Namespace { get; private set; }
        public uint Token { get; private set; }

        public IntPtr Assembly { get; private set; }
        public IntPtr Parent { get; private set; }
        public TypeAttributes Flags { get; private set; }
        #endregion

        public GameClass(IntPtr klass)
        {
            // Setup properties
            Pointer = klass;

            Name = Marshal.PtrToStringAnsi(il2cpp_class_get_name(klass));
            Namespace = Marshal.PtrToStringAnsi(il2cpp_class_get_namespace(klass));
            Token = NativeSDK.il2cpp_class_get_type_token(klass);

            Assembly = il2cpp_class_get_image(klass);
            Parent = il2cpp_class_get_declaring_type(klass);
            Flags = (TypeAttributes)il2cpp_class_get_flags(klass);
        }

        #region GameClass Functions
        public void IterateInterfaces(Action<GameClass> iterator)
        {
            IntPtr iter = IntPtr.Zero;
            IntPtr klass = IntPtr.Zero;
            while ((klass = il2cpp_class_get_interfaces(Pointer, ref iter)) != IntPtr.Zero)
                iterator(new GameClass(klass));
        }
        #endregion
    }

    internal class ClassDump : IModule<GameClass>
    {
        #region ClassDump Data
        private GameAssembly _assembly;
        #endregion

        #region Native Class Data
        private uint _count;
        private uint _index;
        #endregion

        public ClassDump(GameAssembly assembly)
        {
            // Set variables
            _assembly = assembly;

            // Setup variables
            _index = 0;
            _count = NativeSDK.il2cpp_image_get_class_count(assembly.Pointer);
        }

        #region IModule Variables
        private Dictionary<IntPtr, object> _stack = new Dictionary<IntPtr, object>();
        #endregion
        #region IModule Functions
        public void PushToStack(GameClass klass, object value)
        {
            if (!IsOnStack(klass))
                _stack.Add(klass.Pointer, value);
        }
        public bool IsOnStack(GameClass klass) => _stack.ContainsKey(klass.Pointer);
        public object GrabFromStack(GameClass klass)
        {
            if (IsOnStack(klass))
                return _stack[klass.Pointer];
            return null;
        }

        public bool HasNext()
        {
            return _index < _count;
        }
        public GameClass Next()
        {
            IntPtr output = NativeSDK.il2cpp_image_get_class(_assembly.Pointer, _index);
            if (output == IntPtr.Zero) return null;

            _index++;
            if (_stack.ContainsKey(output)) return null;
            return new GameClass(output);
        }
        #endregion
    }
}
