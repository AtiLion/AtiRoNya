#pragma once

#include "InternalHelpers.hpp"

#pragma region Redifinitions
typedef uintptr_t il2cpp_array_size_t;

struct IL2CPPAssembly;
struct IL2CPPDomain;
struct IL2CPPImage;
struct IL2CPPClass;
struct IL2CPPMethod;
struct IL2CPPObject;
struct IL2CPPString;
struct IL2CPPArray;
#pragma endregion

#pragma region Mono Enum Definitions
typedef enum
{
	IL2CPP_SECURITY_MODE_NONE,
	IL2CPP_SECURITY_MODE_CORE_CLR,
	IL2CPP_SECURITY_MODE_CAS,
	IL2CPP_SECURITY_MODE_SMCS_HACK
} MonoSecurityMode;
#pragma endregion

#pragma region Mono Function Definitions
typedef IL2CPPDomain* (*il2cpp_init_t)(const char* name);
typedef void(*il2cpp_thread_attach_t)(IL2CPPDomain* domain);

typedef IL2CPPAssembly* (*il2cpp_domain_assembly_open_t)(IL2CPPDomain* domain, const char* name);
typedef IL2CPPImage* (*il2cpp_assembly_get_image_t)(IL2CPPAssembly* assembly);
typedef IL2CPPClass* (*il2cpp_class_from_name_t)(IL2CPPImage* image, const char* name_space, const char* name);
typedef IL2CPPMethod* (*il2cpp_class_get_method_from_name_t)(IL2CPPClass* _class, const char* name, int param_count);
typedef IL2CPPObject* (*il2cpp_runtime_invoke_t)(IL2CPPMethod* method, void* obj, void** params, IL2CPPObject** exc);

typedef IL2CPPString* (*il2cpp_string_new_t)(const char* text);

typedef void* (*il2cpp_object_unbox_t)(IL2CPPObject* obj);

typedef uint32_t* (*il2cpp_array_length_t)(IL2CPPArray* arr);
typedef IL2CPPArray* (*il2cpp_array_new_t)(IL2CPPClass* arrayType, il2cpp_array_size_t length);
#pragma endregion

#pragma region Mono Functions
extern il2cpp_init_t il2cpp_init;
extern il2cpp_thread_attach_t il2cpp_thread_attach;

extern il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open;
extern il2cpp_assembly_get_image_t il2cpp_assembly_get_image;
extern il2cpp_class_from_name_t il2cpp_class_from_name;
extern il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;
extern il2cpp_runtime_invoke_t il2cpp_runtime_invoke;

extern il2cpp_string_new_t il2cpp_string_new;

extern il2cpp_object_unbox_t il2cpp_object_unbox;

extern il2cpp_array_length_t il2cpp_array_length;
extern il2cpp_array_new_t il2cpp_array_new;
#pragma endregion

void Build_IL2CPP(HMODULE hMono);