using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;

using AtiRoNyaSDK;

using Mono.Cecil;

namespace RuntimeDumper.Modules
{
    internal class GameMethod
    {
        #region IL2CPP Functions
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_method_get_name(IntPtr method);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_method_get_return_type(IntPtr method);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static uint il2cpp_method_get_token(IntPtr method);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static uint il2cpp_method_get_param_count(IntPtr method);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_method_get_param(IntPtr method, uint index);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr il2cpp_method_get_param_name(IntPtr method, uint index);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static uint il2cpp_method_get_flags(IntPtr method, ref uint iflags);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static bool il2cpp_type_is_byref(IntPtr type);
        #endregion

        #region Method Properties
        public IntPtr Pointer { get; private set; }

        public string Name { get; private set; }
        public uint Token { get; private set; }
        public IntPtr Return { get; private set; }

        public MethodImplAttributes IFlags { get; private set; }
        public MethodAttributes Flags { get; private set; }
        #endregion

        public GameMethod(IntPtr method)
        {
            // Setup properties
            Pointer = method;

            Name = Marshal.PtrToStringAnsi(il2cpp_method_get_name(method));
            Token = il2cpp_method_get_token(method);
            Return = il2cpp_method_get_return_type(method);

            uint iflags = 0;
            Flags = (MethodAttributes)il2cpp_method_get_flags(method, ref iflags);
            IFlags = (MethodImplAttributes)iflags;
        }

        #region GameMethod Functions
        public void IterateParameters(Action<IntPtr, string> iterator)
        {
            uint length = il2cpp_method_get_param_count(Pointer);
            for (uint i = 0; i < length; i++)
                iterator(il2cpp_method_get_param(Pointer, i), Marshal.PtrToStringAnsi(il2cpp_method_get_param_name(Pointer, i)));
        }
        #endregion
    }

    internal class MethodDump : IModule<GameMethod>
    {
        #region MethodDump Data
        private GameClass _class;
        #endregion

        #region Native Method Data
        private IntPtr _iter;
        private IntPtr _next;
        #endregion

        public MethodDump(GameClass klass)
        {
            // Set variables
            _class = klass;

            // Setup variables
            _iter = IntPtr.Zero;
            _next = NativeSDK.il2cpp_class_get_methods(klass.Pointer, ref _iter);
        }

        #region IModule Variables
        private Dictionary<IntPtr, object> _stack = new Dictionary<IntPtr, object>();
        #endregion
        #region IModule Functions
        public void PushToStack(GameMethod method, object value)
        {
            if (!IsOnStack(method))
                _stack.Add(method.Pointer, value);
        }
        public bool IsOnStack(GameMethod method) => _stack.ContainsKey(method.Pointer);
        public object GrabFromStack(GameMethod method)
        {
            if (IsOnStack(method))
                return _stack[method.Pointer];
            return null;
        }

        public bool HasNext() => _next != IntPtr.Zero;
        public GameMethod Next()
        {
            IntPtr output = _next;
            if (output == IntPtr.Zero) return null;

            _next = NativeSDK.il2cpp_class_get_methods(_class.Pointer, ref _iter);
            if (_stack.ContainsKey(output)) return null;
            return new GameMethod(output);
        }
        #endregion
    }
}
