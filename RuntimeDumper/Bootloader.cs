using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Mono.Cecil;
using Mono.Cecil.Cil;

using RuntimeDumper;
using RuntimeDumper.Modules;

using AtiRoNyaSDK;

public class Bootloader
{
    static AssemblyDump assemblyDumper;

    public static void Main()
    {
        Logger.Log("Starting RuntimeDumper...");

        // Initialize assembly dumper
        assemblyDumper = new AssemblyDump();

        // Loop assemblies
        while(assemblyDumper.HasNext())
        {
            // Get runtime assembly
            GameAssembly runtimeAssembly = assemblyDumper.Next();
            if (runtimeAssembly == null) continue;

            // Dump
            DumpAssembly(runtimeAssembly);
        }
    }

    #region Dumpers
    private static AssemblyDefinition DumpAssembly(GameAssembly runtimeAssembly)
    {
        // Check stack
        if (assemblyDumper.IsOnStack(runtimeAssembly)) return (AssemblyDefinition)assemblyDumper.GrabFromStack(runtimeAssembly);

        // Generate assembly file
        AssemblyDefinition assembly = AssemblyDefinition.CreateAssembly(new AssemblyNameDefinition(runtimeAssembly.Name, new Version(3, 7, 1, 6)), runtimeAssembly.Name, ModuleKind.Dll);
        ModuleDefinition mainModule = assembly.MainModule;

        // Add to stack
        assemblyDumper.PushToStack(runtimeAssembly, assembly);

        // Store dumped classes
        Dictionary<GameClass, TypeDefinition> dumpedClasses = new Dictionary<GameClass, TypeDefinition>();

        // Get classes
        ClassDump classDumper = new ClassDump(runtimeAssembly);
        while(classDumper.HasNext())
        {
            // Get runtime class
            GameClass runtimeClass = classDumper.Next();
            if (runtimeClass == null) continue;

            // Dump
            dumpedClasses.Add(runtimeClass, DumpClass(classDumper, mainModule, runtimeClass));
        }

        // Populate classes
        foreach(GameClass runtimeClass in dumpedClasses.Keys)
        {
            // Dump methods
            MethodDump methodDumper = new MethodDump(runtimeClass);
            while (methodDumper.HasNext())
            {
                // Get method
                GameMethod runtimeMethod = methodDumper.Next();
                if (runtimeMethod == null) continue;

                // Dump
                DumpMethod(methodDumper, dumpedClasses[runtimeClass], runtimeMethod);
            }
        }

        // End
        Logger.Log("Dumped assembly: " + runtimeAssembly.Name);
        assembly.Write("AtiRoNya\\Dumps\\" + runtimeAssembly.Name + ".dll");
        return assembly;
    }
    private static TypeDefinition DumpClass(ClassDump dumper, ModuleDefinition target, GameClass runtimeClass)
    {
        // Check stack
        if (dumper.IsOnStack(runtimeClass)) return (TypeDefinition)dumper.GrabFromStack(runtimeClass);

        // Create type definition
        TypeDefinition type = new TypeDefinition(runtimeClass.Namespace, runtimeClass.Name, runtimeClass.Flags);
        type.MetadataToken = new MetadataToken(runtimeClass.Token);

        // Add to stack
        dumper.PushToStack(runtimeClass, type);

        // Add type to assembly
        if (runtimeClass.Parent != IntPtr.Zero)
        {
            GameClass parent = new GameClass(runtimeClass.Parent);
            TypeDefinition parentType = DumpClass(dumper, target, parent);

            if (parentType == null) target.Types.Add(type);
            else parentType.NestedTypes.Add(type);
        }
        else target.Types.Add(type);

        // End
        return type;
    }
    private static MethodDefinition DumpMethod(MethodDump dumper, TypeDefinition type, GameMethod runtimeMethod)
    {
        // Check stack
        if (dumper.IsOnStack(runtimeMethod)) return (MethodDefinition)dumper.GrabFromStack(runtimeMethod);

        // Create method definition
        MethodDefinition method = new MethodDefinition(runtimeMethod.Name, runtimeMethod.Flags, type.Module.ImportReference(typeof(void)));
        method.ImplAttributes = runtimeMethod.IFlags;
        method.MetadataToken = new MetadataToken(runtimeMethod.Token);
        type.Methods.Add(method);

        // Add to stack
        dumper.PushToStack(runtimeMethod, method);

        // Setup return type
        TypeReference returnType = GetTypeReferenceWithByRef(method, runtimeMethod.Return);
        if (returnType != null) method.ReturnType = returnType;
        else Logger.Log("Failed to find type for " + runtimeMethod.Name);

        // Setup body
        if(method.HasBody && type.BaseType?.FullName != "System.MulticastDelegate")
        {
            // TODO: Make it run what I need
            ILProcessor il = method.Body.GetILProcessor();
            il.Append(Instruction.Create(OpCodes.Nop));
        }

        // Setup parameters
        /*runtimeMethod.IterateParameters((IntPtr ptrParamType, string name) =>
        {
            IL2CPPType paramType = (IL2CPPType)Marshal.PtrToStructure(ptrParamType, typeof(IL2CPPType));
            TypeReference paramRef = GetTypeReferenceWithByRef(method, ptrParamType);
            if (paramRef == null) return;

            ParameterDefinition parameterDefinition = new ParameterDefinition(name, (ParameterAttributes)paramType.attrs, paramRef);
            method.Parameters.Add(parameterDefinition);
        });*/

        // End
        return method;
    }
    #endregion

    #region Dump Utilities
    private static TypeReference GetTypeReferenceWithByRef(MemberReference member, IntPtr target)
    {
        if (target == IntPtr.Zero || member == null) return null;
        TypeReference output = GetTypeReference(member, target);

        if (output == null) return null;
        else if (GameMethod.il2cpp_type_is_byref(target)) return new ByReferenceType(output);
        else return output;
    }
    private static TypeReference GetTypeReference(MemberReference member, IntPtr target)
    {
        ModuleDefinition module = member.Module;
        IL2CPPType il2cppType = (IL2CPPType)Marshal.PtrToStructure(target, typeof(IL2CPPType));

        switch ((IL2CPPTypes)il2cppType.type)
        {
            case IL2CPPTypes.IL2CPP_TYPE_OBJECT:
                return module.ImportReference(typeof(object));
            case IL2CPPTypes.IL2CPP_TYPE_VOID:
                return module.ImportReference(typeof(void));
            case IL2CPPTypes.IL2CPP_TYPE_BOOLEAN:
                return module.ImportReference(typeof(bool));
            case IL2CPPTypes.IL2CPP_TYPE_CHAR:
                return module.ImportReference(typeof(char));
            case IL2CPPTypes.IL2CPP_TYPE_I1:
                return module.ImportReference(typeof(sbyte));
            case IL2CPPTypes.IL2CPP_TYPE_U1:
                return module.ImportReference(typeof(byte));
            case IL2CPPTypes.IL2CPP_TYPE_I2:
                return module.ImportReference(typeof(short));
            case IL2CPPTypes.IL2CPP_TYPE_U2:
                return module.ImportReference(typeof(ushort));
            case IL2CPPTypes.IL2CPP_TYPE_I4:
                return module.ImportReference(typeof(int));
            case IL2CPPTypes.IL2CPP_TYPE_U4:
                return module.ImportReference(typeof(uint));
            case IL2CPPTypes.IL2CPP_TYPE_I:
                return module.ImportReference(typeof(IntPtr));
            case IL2CPPTypes.IL2CPP_TYPE_U:
                return module.ImportReference(typeof(UIntPtr));
            case IL2CPPTypes.IL2CPP_TYPE_I8:
                return module.ImportReference(typeof(long));
            case IL2CPPTypes.IL2CPP_TYPE_U8:
                return module.ImportReference(typeof(ulong));
            case IL2CPPTypes.IL2CPP_TYPE_R4:
                return module.ImportReference(typeof(float));
            case IL2CPPTypes.IL2CPP_TYPE_R8:
                return module.ImportReference(typeof(double));
            case IL2CPPTypes.IL2CPP_TYPE_STRING:
                return module.ImportReference(typeof(string));
            case IL2CPPTypes.IL2CPP_TYPE_TYPEDBYREF:
                return module.ImportReference(typeof(TypedReference));
            case IL2CPPTypes.IL2CPP_TYPE_CLASS:
            case IL2CPPTypes.IL2CPP_TYPE_VALUETYPE:
                TypeDefinition type = GetOrDumpType(NativeSDK.il2cpp_class_from_il2cpp_type(target));
                if (type == null) return null;

                return module.ImportReference(type);
            case IL2CPPTypes.IL2CPP_TYPE_ARRAY:
                IL2CPPArrayType arrayType = (IL2CPPArrayType)Marshal.PtrToStructure(il2cppType.value, typeof(IL2CPPArrayType));

                return new ArrayType(GetTypeReference(member, arrayType.type), arrayType.rank);
            case IL2CPPTypes.IL2CPP_TYPE_SZARRAY:
                return new ArrayType(GetTypeReference(member, il2cppType.value));
            case IL2CPPTypes.IL2CPP_TYPE_GENERICINST:
                IL2CPPGenericClass genericClass = (IL2CPPGenericClass)Marshal.PtrToStructure(il2cppType.value, (typeof(IL2CPPGenericClass)));

                TypeDefinition genericType = GetOrDumpType(genericClass.cached_class);
                if (genericType == null) return null;

                GenericInstanceType genericInstanceType = new GenericInstanceType(module.ImportReference(genericType));
                IL2CPPGenericInst genericInst = (IL2CPPGenericInst)Marshal.PtrToStructure(genericClass.context.class_inst, typeof(IL2CPPGenericInst));
                IntPtr[] ptrArray = NativeSDK.PtrToArry<IntPtr>(genericInst.type_argv, genericInst.type_argc);

                foreach(IntPtr ptr in ptrArray)
                    genericInstanceType.GenericArguments.Add(GetTypeReference(member, ptr));
                return genericInstanceType;
            case IL2CPPTypes.IL2CPP_TYPE_PTR:
                return new PointerType(GetTypeReference(member, il2cppType.value));
            default:
                return module.ImportReference(typeof(void));
        }
    }
    private static TypeDefinition GetOrDumpType(IntPtr klass)
    {
        if (klass == IntPtr.Zero) return null;
        GameClass runtimeClass = new GameClass(klass);
        GameAssembly runtimeAssembly = new GameAssembly(runtimeClass.Assembly);
        
        // Run assembly dump
        AssemblyDefinition assembly = DumpAssembly(runtimeAssembly);
        if (assembly == null) return null;

        // Find and return type
        return SearchType(assembly.MainModule.Types, runtimeClass);
    }
    private static TypeDefinition SearchType(IEnumerable<TypeDefinition> types, GameClass target)
    {
        if (types.Count() < 1) return null;
        foreach (TypeDefinition type in types)
        {
            if (type.MetadataToken.ToUInt32() == target.Token)
                return type;
            if(type.HasNestedTypes)
            {
                TypeDefinition returnedType = SearchType(type.NestedTypes, target);
                if (returnedType != null)
                    return returnedType;
            }
        }
        return null;
    }
    #endregion
}
