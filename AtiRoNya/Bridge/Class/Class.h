#pragma once

#include "../Bridge.h"

#pragma region Class
DO_API(MonoClass*, (*mono_class_get_t), (MonoImage* image, uint32_t token));

DO_API(MonoClass*, (*mono_class_from_name_t), (MonoImage* image, const char* name_space, const char* name));

DO_API(MonoMethod*, (*mono_class_get_method_from_name_t), (MonoClass* klass, const char* name, int param_count));

DO_API(uint32_t, (*il2cpp_class_get_type_token_t), (IL2CPPClass* klass));

DO_API(IL2CPPMethod*, (*il2cpp_class_get_methods_t), (IL2CPPClass* klass, void** iter));
DO_API(MonoMethod*, (*mono_class_get_methods_t), (MonoClass* klass, void** iter));

class BridgeClass {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_class_get_t mono_class_get;

	static mono_class_from_name_t mono_class_from_name;

	static mono_class_get_method_from_name_t mono_class_get_method_from_name;

	static il2cpp_class_get_type_token_t il2cpp_class_get_type_token;

	static il2cpp_class_get_methods_t il2cpp_class_get_methods;
	static mono_class_get_methods_t mono_class_get_methods;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion