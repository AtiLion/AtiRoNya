#pragma once

#include "InternalHelpers.hpp"

#pragma region Redifinitions
struct MonoAssembly;
struct MonoDomain;
struct MonoImage;
struct MonoClass;
struct MonoMethod;
struct MonoObject;
struct MonoThread;
struct MonoAssemblyName;
#pragma endregion

#pragma region Mono Enum Definitions
typedef enum
{
	il2cpp_SECURITY_MODE_NONE,
	il2cpp_SECURITY_MODE_CORE_CLR,
	il2cpp_SECURITY_MODE_CAS,
	il2cpp_SECURITY_MODE_SMCS_HACK
} MonoSecurityMode;
#pragma endregion

#pragma region Mono Function Definitions
typedef MonoDomain* (*il2cpp_init_t)(const char* name);
typedef void(*il2cpp_thread_attach_t)(MonoDomain* domain);
typedef MonoAssembly* (*il2cpp_domain_assembly_open_t)(MonoDomain* domain, const char* name);
typedef MonoImage* (*il2cpp_assembly_get_image_t)(MonoAssembly* assembly);
typedef MonoClass* (*il2cpp_class_from_name_t)(MonoImage* image, const char* name_space, const char* name);
typedef MonoMethod* (*il2cpp_class_get_method_from_name_t)(MonoClass* _class, const char* name, int param_count);
typedef MonoObject* (*il2cpp_runtime_invoke_t)(MonoMethod* method, void* obj, void** params, MonoObject** exc);
#pragma endregion

#pragma region Mono Functions
extern il2cpp_init_t il2cpp_init;
extern il2cpp_thread_attach_t il2cpp_thread_attach;
extern il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open;
extern il2cpp_assembly_get_image_t il2cpp_assembly_get_image;
extern il2cpp_class_from_name_t il2cpp_class_from_name;
extern il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;
extern il2cpp_runtime_invoke_t il2cpp_runtime_invoke;
#pragma endregion

void Build_IL2CPP(HMODULE hMono);