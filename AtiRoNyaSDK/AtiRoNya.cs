using System;
using System.IO;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;

namespace AtiRoNyaSDK
{
    public static class AtiRoNya
    {
        #region Cache
        private static Dictionary<string, IntPtr> _Assemblies = new Dictionary<string, IntPtr>();
        private static Dictionary<IntPtr, Dictionary<uint, IntPtr>> _Types = new Dictionary<IntPtr, Dictionary<uint, IntPtr>>();
        private static Dictionary<IntPtr, Dictionary<uint, IntPtr>> _NestedTypes = new Dictionary<IntPtr, Dictionary<uint, IntPtr>>();
        private static Dictionary<IntPtr, Dictionary<uint, IntPtr>> _Methods = new Dictionary<IntPtr, Dictionary<uint, IntPtr>>();
        private static Dictionary<IntPtr, Dictionary<uint, IntPtr>> _Fields = new Dictionary<IntPtr, Dictionary<uint, IntPtr>>();

        private static Dictionary<IntPtr, CachedInvoker> _Invokers = new Dictionary<IntPtr, CachedInvoker>();

        private static Dictionary<Type, FieldInfo> _TypeFields = new Dictionary<Type, FieldInfo>();
        private static Dictionary<Type, FieldInfo> _InstanceFields = new Dictionary<Type, FieldInfo>();
        #endregion
        #region Cache Classes
        private class CachedInvoker
        {
            public NativeSDK.IL2CPPInvoker Invoker { get; private set; }
            public IL2CPPMethod Method { get; private set; }

            public CachedInvoker(NativeSDK.IL2CPPInvoker invoker, IL2CPPMethod method)
            {
                Invoker = invoker;
                Method = method;
            }
        }
        #endregion

        #region Mapping
        public static IntPtr MapAssembly(string name)
        {
            // Check cache
            if (_Assemblies.TryGetValue(name, out IntPtr cache)) return cache;

            // Get assembly
            IntPtr assembly = NativeSDK.il2cpp_domain_assembly_open(NativeSDK.atironya_get_il2cpp_domain(), name);
            if (assembly == IntPtr.Zero) return IntPtr.Zero;

            // Get image
            IntPtr image = NativeSDK.il2cpp_assembly_get_image(assembly);
            if (image == IntPtr.Zero) return IntPtr.Zero;

            // Load type cache
            if (!_Types.ContainsKey(image)) _Types.Add(image, new Dictionary<uint, IntPtr>());

            // Return image
            return image;
        }
        public static IntPtr MapType(IntPtr assembly, uint token)
        {
            // Check assembly
            if (assembly == IntPtr.Zero) return IntPtr.Zero;

            // Check cache
            if(_Types.TryGetValue(assembly, out var assemblyTypes))
                if (assemblyTypes.TryGetValue(token, out IntPtr cache)) return cache;

            // Check if assemblyTypes exist
            if (assemblyTypes == null) return IntPtr.Zero;

            // Search types
            uint count = NativeSDK.il2cpp_image_get_class_count(assembly);
            for(uint i = 0; i < count; i++)
            {
                // Get the type
                IntPtr type = NativeSDK.il2cpp_image_get_class(assembly, i);
                if (type == IntPtr.Zero) continue;

                // Get the token
                uint typeToken = NativeSDK.il2cpp_class_get_type_token(type);
                if (typeToken == 0) continue;

                // Load method cache
                if (!_Methods.ContainsKey(type)) _Methods.Add(type, new Dictionary<uint, IntPtr>());

                // Load nested type cache
                if (!_NestedTypes.ContainsKey(type)) _NestedTypes.Add(type, new Dictionary<uint, IntPtr>());

                // Cache and return
                assemblyTypes.Add(typeToken, type);
                if (typeToken == token) return type;
            }
            return IntPtr.Zero;
        }
        public static IntPtr MapMethod(IntPtr type, uint token)
        {
            // Check type
            if (type == IntPtr.Zero) return IntPtr.Zero;

            // Check cache
            if (_Methods.TryGetValue(type, out var typeMethods))
                if (typeMethods.TryGetValue(token, out IntPtr cache)) return cache;

            // Check if typeMethods exist
            if (typeMethods == null) return IntPtr.Zero;

            // Search methods
            IntPtr iter = IntPtr.Zero;
            IntPtr method = IntPtr.Zero;
            while((method = NativeSDK.il2cpp_class_get_methods(type, ref iter)) != IntPtr.Zero)
            {
                // Check method
                if (method == IntPtr.Zero) continue;

                // Get the token
                uint methodToken = NativeSDK.il2cpp_method_get_token(method);
                if (methodToken == 0) continue;

                // Cache and return
                typeMethods.Add(methodToken, method);
                if (methodToken == token) return method;
            }
            return IntPtr.Zero;
        }
        public static IntPtr MapNestedType(IntPtr type, uint token)
        {
            // Check type
            if (type == IntPtr.Zero) return IntPtr.Zero;

            // Check cache
            if (_NestedTypes.TryGetValue(type, out var typeNests))
                if (typeNests.TryGetValue(token, out IntPtr cache)) return cache;

            // Check if typeNests exist
            if (typeNests == null) return IntPtr.Zero;

            // Search nested types
            IntPtr iter = IntPtr.Zero;
            IntPtr nest = IntPtr.Zero;
            while((nest = NativeSDK.il2cpp_class_get_nested_types(type, ref iter)) != IntPtr.Zero)
            {
                // Check nested type
                if (nest == IntPtr.Zero) continue;

                // Get the token
                uint typeToken = NativeSDK.il2cpp_class_get_type_token(nest);
                if (typeToken == 0) continue;

                // Cache and return
                typeNests.Add(typeToken, nest);
                if (typeToken == token) return nest;
            }
            return IntPtr.Zero;
        }
        public static IntPtr MapField(IntPtr type, uint token)
        {
            // Check type
            if (type == IntPtr.Zero) return IntPtr.Zero;

            // Check cache
            if (_Fields.TryGetValue(type, out var typeFields))
                if (typeFields.TryGetValue(token, out IntPtr cache)) return cache;

            // Check if typeFields exist
            if (typeFields == null) return IntPtr.Zero;

            // Search fields
            IntPtr iter = IntPtr.Zero;
            IntPtr field = IntPtr.Zero;
            while ((field = NativeSDK.il2cpp_class_get_fields(type, ref iter)) != IntPtr.Zero)
            {
                // Check field
                if (field == IntPtr.Zero) continue;

                // Get the token
                uint fieldToken = NativeSDK.il2cpp_field_get_offset(field);
                if (fieldToken == 0) continue;

                // Cache and return
                typeFields.Add(fieldToken, field);
                if (fieldToken == token) return field;
            }
            return IntPtr.Zero;
        }
        #endregion

        #region Execution
        public static void Invoke(IntPtr method, IntPtr instance, object[] args)
        {
            // Check method
            if (method == IntPtr.Zero) return;

            // Get method structure and invoker
            CachedInvoker invoker = null;
            if (!_Invokers.TryGetValue(method, out invoker))
            {
                IL2CPPMethod il2cppMethod = (IL2CPPMethod)Marshal.PtrToStructure(method, typeof(IL2CPPMethod));
                NativeSDK.IL2CPPInvoker il2cppInvoker = (NativeSDK.IL2CPPInvoker)Marshal.GetDelegateForFunctionPointer(il2cppMethod.Invoker, typeof(NativeSDK.IL2CPPInvoker));

                invoker = new CachedInvoker(il2cppInvoker, il2cppMethod);
                _Invokers.Add(method, invoker);
            }

            // Convert parameters
            IntPtr[] argPtrs = new IntPtr[args.Length];
            for (uint i = 0; i < args.Length; i++)
            {
                Type _type = args[i].GetType();
                IntPtr _assembly = MapAssembly(_type.Assembly.GetName().Name);

                argPtrs[i] = NativeSDK.ConvertToIntPtr(args[i], MapType(_assembly, (uint)_type.MetadataToken));
            }

            // Invoke
            invoker.Invoker(invoker.Method.ptr, method, instance, argPtrs);
        }
        public static T Invoke<T>(IntPtr method, IntPtr instance, object[] args)
        {
            // Check method
            if (method == IntPtr.Zero) return default;

            // Get method structure and invoker
            CachedInvoker invoker = null;
            if (!_Invokers.TryGetValue(method, out invoker))
            {
                IL2CPPMethod il2cppMethod = (IL2CPPMethod)Marshal.PtrToStructure(method, typeof(IL2CPPMethod));
                NativeSDK.IL2CPPInvoker il2cppInvoker = (NativeSDK.IL2CPPInvoker)Marshal.GetDelegateForFunctionPointer(il2cppMethod.Invoker, typeof(NativeSDK.IL2CPPInvoker));

                invoker = new CachedInvoker(il2cppInvoker, il2cppMethod);
                _Invokers.Add(method, invoker);
            }

            // Convert parameters
            IntPtr[] argPtrs = new IntPtr[args.Length];
            for (uint i = 0; i < args.Length; i++)
            {
                Type _type = args[i].GetType();
                IntPtr _assembly = MapAssembly(_type.Assembly.GetName().Name);

                argPtrs[i] = NativeSDK.ConvertToIntPtr(args[i], MapType(_assembly, (uint)_type.MetadataToken));
            }

            // Invoke
            IntPtr result = invoker.Invoker(invoker.Method.ptr, method, instance, argPtrs);
            if (result == IntPtr.Zero) return default;
            else return NativeSDK.ConvertFromIntPtr<T>(result);
        }
        public static IntPtr NewObject(IntPtr method, IntPtr klass, object[] args)
        {
            // Check method
            if (method == IntPtr.Zero) return IntPtr.Zero;

            // Get method structure and invoker
            CachedInvoker invoker = null;
            if (!_Invokers.TryGetValue(method, out invoker))
            {
                IL2CPPMethod il2cppMethod = (IL2CPPMethod)Marshal.PtrToStructure(method, typeof(IL2CPPMethod));
                NativeSDK.IL2CPPInvoker il2cppInvoker = (NativeSDK.IL2CPPInvoker)Marshal.GetDelegateForFunctionPointer(il2cppMethod.Invoker, typeof(NativeSDK.IL2CPPInvoker));

                invoker = new CachedInvoker(il2cppInvoker, il2cppMethod);
                _Invokers.Add(method, invoker);
            }

            // Convert parameters
            IntPtr[] argPtrs = new IntPtr[args.Length];
            for (uint i = 0; i < args.Length; i++)
            {
                Type _type = args[i].GetType();
                IntPtr _assembly = MapAssembly(_type.Assembly.GetName().Name);

                argPtrs[i] = NativeSDK.ConvertToIntPtr(args[i], MapType(_assembly, (uint)_type.MetadataToken));
            }

            // Create object
            IntPtr obj = NativeSDK.il2cpp_object_new(klass);
            invoker.Invoker(invoker.Method.ptr, method, obj, argPtrs);
            return obj;
        }
        public static T GetFieldValue<T>(IntPtr field, IntPtr instance)
        {
            // Check field
            if (field == IntPtr.Zero) return default;

            // Setup for getter
            IntPtr result = IntPtr.Zero;

            // Get value
            if (instance == IntPtr.Zero) NativeSDK.il2cpp_field_static_get_value(field, ref result);
            else NativeSDK.il2cpp_field_get_value(instance, field, ref result);

            // Return value
            return NativeSDK.ConvertFromIntPtr<T>(result);
        }
        public static void SetFieldValue(IntPtr field, IntPtr instance, object value)
        {
            // Check field
            if (field == IntPtr.Zero) return;

            // Get conversion data
            Type _type = value.GetType();
            IntPtr _assembly = MapAssembly(_type.Assembly.GetName().Name);

            // Convert value
            IntPtr pValue = NativeSDK.ConvertToIntPtr(value, MapType(_assembly, (uint)_type.MetadataToken));

            // Set value
            if (instance == IntPtr.Zero) NativeSDK.il2cpp_field_static_set_value(field, pValue);
            else NativeSDK.il2cpp_field_set_value(instance, field, pValue);
        }
        #endregion
    }
}
