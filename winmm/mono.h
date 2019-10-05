#pragma once

#pragma region Redifinitions
typedef void* MonoAssembly;
typedef void* MonoDomain;
typedef void* MonoImage;
typedef void* MonoClass;
typedef void* MonoMethod;
typedef void* MonoObject;
typedef void* MonoThread;
#pragma endregion

#pragma region Mono Enum Definitions
typedef enum
{
	MONO_SECURITY_MODE_NONE,
	MONO_SECURITY_MODE_CORE_CLR,
	MONO_SECURITY_MODE_CAS,
	MONO_SECURITY_MODE_SMCS_HACK
} MonoSecurityMode;
#pragma endregion

#pragma region Mono Function Definitions
typedef MonoAssembly(*mono_domain_assembly_open_t)(MonoDomain domain, const char* name);
typedef MonoDomain(*mono_get_root_domain_t)();
typedef void(*mono_assembly_close_t)(MonoAssembly assembly);
typedef void(*mono_add_internal_call_t)(const char* name, void* method);
typedef void(*mono_thread_attach_t)(MonoDomain domain);
typedef MonoImage(*mono_assembly_get_image_t)(MonoAssembly assembly);
typedef MonoClass(*mono_class_from_name_t)(MonoImage image, const char* name_space, const char* name);
typedef MonoMethod(*mono_class_get_method_from_name_t)(MonoClass _class, const char* name, int param_count);
typedef MonoObject(*mono_runtime_invoke_t)(MonoMethod method, void* obj, void** params, MonoObject* exc);
typedef void(*mono_security_set_mode_t)(MonoSecurityMode mode);
typedef MonoThread(*mono_thread_get_main_t)(void);
#pragma endregion

#pragma region Mono Functions
mono_domain_assembly_open_t mono_domain_assembly_open;
mono_get_root_domain_t mono_get_root_domain;
mono_assembly_close_t mono_assembly_close;
mono_add_internal_call_t mono_add_internal_call;
mono_thread_attach_t mono_thread_attach;
mono_assembly_get_image_t mono_assembly_get_image;
mono_class_from_name_t mono_class_from_name;
mono_class_get_method_from_name_t mono_class_get_method_from_name;
mono_runtime_invoke_t mono_runtime_invoke;
mono_security_set_mode_t mono_security_set_mode;
mono_thread_get_main_t mono_thread_get_main;
#pragma endregion