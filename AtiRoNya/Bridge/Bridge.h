#pragma once

#include "../AtiRoNya.h"

#define DO_API(r, n, p) typedef r n p;
#define DO_API_NO_RETURN(r, n, p) typedef r n p;

typedef void* (*InvokerMethod)(void*, void*, void*, void**); // method pointer, method, instance, params

#pragma region Image
struct MonoImage;
struct IL2CPPImage;
#pragma endregion

#pragma region Assembly
struct MonoAssembly;
struct IL2CPPAssembly;
#pragma endregion

#pragma region Domain
struct MonoDomain;
struct IL2CPPDomain;
#pragma endregion

#pragma region Class
struct MonoClass;
struct IL2CPPClass;
#pragma endregion

#pragma region Method
struct MonoMethod;
struct IL2CPPMethod {
	void* methodPointer;
	InvokerMethod invoker;
};
#pragma endregion

#pragma region VTable
struct MonoVTable {
public:
    MonoClass* klass;
};
#pragma endregion

#pragma region Object
struct MonoObject {
public:
    MonoVTable* vtable;
    void* sync;
};
struct IL2CPPObject {
public:
    union
    {
        IL2CPPClass* klass;
        void* vtable;
    };
    void* monitor;
};
#pragma endregion

#pragma region String
struct MonoString;
#pragma endregion

#pragma region Array
struct MonoArray;
#pragma endregion