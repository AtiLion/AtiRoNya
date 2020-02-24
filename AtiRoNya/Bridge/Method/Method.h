#pragma once

#include "../Bridge.h"

#pragma region Method
DO_API(MonoObject*, (*mono_runtime_invoke_t), (MonoMethod* method, void* obj, void** params, MonoObject** exec));

DO_API(uint32_t, (*il2cpp_method_get_token_t), (IL2CPPMethod* method));
DO_API(uint32_t, (*mono_method_get_token_t), (MonoMethod* method));

DO_API(void*, (*mono_method_get_unmanaged_thunk_t), (MonoMethod* method));

class BridgeMethod {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_runtime_invoke_t mono_runtime_invoke;

	static il2cpp_method_get_token_t il2cpp_method_get_token;
	static mono_method_get_token_t mono_method_get_token;

	static mono_method_get_unmanaged_thunk_t mono_method_get_unmanaged_thunk;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion