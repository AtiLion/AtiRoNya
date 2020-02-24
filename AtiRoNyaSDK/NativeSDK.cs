using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
using System.Linq;
using System.Text;

namespace AtiRoNyaSDK
{
    internal static class NativeSDK
    {
        #region AtiRoNya
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static IntPtr atironya_get_il2cpp_domain();
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static IntPtr atironya_get_mono_domain();
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static IntPtr atironya_addrof(object obj);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static object atironya_valueof(IntPtr ptr);
        #endregion

        #region Mono
        [DllImport("mono", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr mono_value_box(IntPtr domain, IntPtr klass, IntPtr value);
        [DllImport("mono", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr mono_object_unbox(IntPtr obj);

        [DllImport("mono", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr mono_class_from_mono_type(IntPtr obj);
        #endregion

        #region IL2CPP
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_domain_assembly_open(IntPtr domain, string name);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_assembly_get_image(IntPtr assembly);

        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_string_new(string str);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_string_chars(IntPtr str);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static int il2cpp_string_length(IntPtr str);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_object_unbox(IntPtr obj);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_value_box(IntPtr klass, IntPtr data);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_object_new(IntPtr klass);

        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_class_get_nested_types(IntPtr klass, ref IntPtr iter);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_class_get_methods(IntPtr klass, ref IntPtr iter);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_class_get_fields(IntPtr klass, ref IntPtr iter);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static uint il2cpp_class_get_type_token(IntPtr klass);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static uint il2cpp_image_get_class_count(IntPtr image);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_image_get_class(IntPtr image, uint index);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_class_from_il2cpp_type(IntPtr type);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_class_get_type(IntPtr klass);

        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static uint il2cpp_method_get_token(IntPtr method);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static IntPtr il2cpp_method_get_name(IntPtr method);

        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static uint il2cpp_field_get_offset(IntPtr field);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static void il2cpp_field_get_value(IntPtr obj, IntPtr field, ref IntPtr value);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static void il2cpp_field_set_value(IntPtr obj, IntPtr field, IntPtr value);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static void il2cpp_field_static_get_value(IntPtr field, ref IntPtr value);
        [DllImport("GameAssembly", CallingConvention = CallingConvention.StdCall)]
        public extern static void il2cpp_field_static_set_value(IntPtr field, IntPtr value);
        #endregion
        #region IL2CPP Delegates
        public delegate IntPtr IL2CPPInvoker(IntPtr methodPointer, IntPtr method, IntPtr instance, [MarshalAs(UnmanagedType.LPArray)]IntPtr[] args);
        #endregion

        #region Native - Managed
        public static string PtrToString(IntPtr ptr) => Marshal.PtrToStringUni(ptr);
        public static T[] PtrToArry<T>(IntPtr ptr, uint length)
        {
            IntPtr iter = ptr;
            T[] output = new T[length];

            for(uint i = 0; i < length; i++)
            {
                output[i] = (T)Marshal.PtrToStructure(iter, typeof(T));
                iter += Marshal.SizeOf(typeof(T));
            }
            return output;
        }
        public static IntPtr ConvertToIntPtr(object obj, IntPtr klass)
        {
            if (obj == null)
                return IntPtr.Zero;

            Type objType = obj.GetType();

            if (objType == typeof(string))
                return il2cpp_string_new((string)obj); // Because strings decided to be special and behave differently
            else if (objType.Assembly == typeof(Type).Assembly && klass != IntPtr.Zero)
                return il2cpp_value_box(klass, mono_object_unbox(atironya_addrof(obj)));
            else if (klass != IntPtr.Zero)
                return IntPtr.Zero; // TODO: Implement dynamic type allocation
            return IntPtr.Zero;
        }
        public static T ConvertFromIntPtr<T>(IntPtr ptr)
        {
            if (ptr == IntPtr.Zero)
                return default;

            if (typeof(T).Assembly == typeof(Type).Assembly)
            {
                return (T)atironya_valueof(mono_value_box(atironya_get_mono_domain(), mono_class_from_mono_type(typeof(T).TypeHandle.Value), il2cpp_object_unbox(ptr)));
            }
            /*if (typeof(T) == typeof(string))
                return PtrToString(il2cpp_string_chars(ptr));
            else if (objType.Assembly == typeof(Type).Assembly)
            {
                Console.WriteLine("Caught mscorlib system");
                //return 0;
                return atironya_valueof(mono_value_box(atironya_get_mono_domain(), mono_class_from_mono_type(objType.TypeHandle.Value), il2cpp_object_unbox(ptr)));
            }*/
            Console.WriteLine("Caught external system");
            //return 1;
            return (T)Activator.CreateInstance(typeof(T), ptr);
        }
        /*public static object ConvertFromIntPtr(IntPtr ptr, Type objType)
        {
            if (ptr == IntPtr.Zero)
                return null;

            if (objType == typeof(string))
                return PtrToString(il2cpp_string_chars(ptr));
            else if (objType.Assembly == typeof(Type).Assembly)
            {
                Console.WriteLine("Caught mscorlib system");
                //return 0;
                return atironya_valueof(mono_value_box(atironya_get_mono_domain(), mono_class_from_mono_type(objType.TypeHandle.Value), il2cpp_object_unbox(ptr)));
            }
            Console.WriteLine("Caught external system");
            //return 1;
            return Activator.CreateInstance(objType, ptr);
        }*/
        /*public unsafe static IntPtr ConvertToIntPtr(object obj)
        {
            if (obj == null)
                return IntPtr.Zero;

            Type objType = obj.GetType();
            void* ptr = null;

            #region Unboxed Types
            if (objType == typeof(int))
            {
                int val = (int)obj;
                ptr = &val;
            }
            else if (objType == typeof(long))
            {
                long val = (long)obj;
                ptr = &val;
            }
            else if (objType == typeof(short))
            {
                short val = (short)obj;
                ptr = &val;
            }
            else if (objType == typeof(byte))
            {
                byte val = (byte)obj;
                ptr = &val;
            }
            else if (objType == typeof(char))
            {
                char val = (char)obj;
                ptr = &val;
            }
            else if (objType == typeof(uint))
            {
                uint val = (uint)obj;
                ptr = &val;
            }
            else if (objType == typeof(ulong))
            {
                ulong val = (ulong)obj;
                ptr = &val;
            }
            else if (objType == typeof(ushort))
            {
                ushort val = (ushort)obj;
                ptr = &val;
            }
            #endregion
            else if (objType == typeof(string))
            {
                return il2cpp_string_new((string)obj);
            }
            else if(objType == typeof(Type))
            {
                throw new Exception("AtiRoNya unsupported type passing");
            }
            else
            {
                return atironya_addrof(obj);
            }

            return (IntPtr)ptr;
        }
        public unsafe static object ConvertFromIntPtr(IntPtr ptr, Type objType)
        {
            if (ptr == IntPtr.Zero)
                return null;

            #region Unboxed Types
            if (objType == typeof(int)) return *(int*)ptr;
            else if (objType == typeof(long)) return *(long*)ptr;
            else if (objType == typeof(short)) return *(short*)ptr;
            else if (objType == typeof(byte)) return *(byte*)ptr;
            else if (objType == typeof(char)) return *(char*)ptr;
            else if (objType == typeof(uint)) return *(uint*)ptr;
            else if (objType == typeof(ulong)) return *(ulong*)ptr;
            else if (objType == typeof(ushort)) return *(ushort*)ptr;
            #endregion
            else if (objType == typeof(string)) return il2cpp_string_chars(ptr);
            else
            {
                // TODO: Add system to convert il2cpp to mono
                return null;
            }
        }*/
        #endregion
    }
}
