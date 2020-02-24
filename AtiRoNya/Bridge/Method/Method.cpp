#include "Method.h"

#pragma region Method
void BridgeMethod::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeMethod::hIL2CPP = hIL2CPP;
	BridgeMethod::hMono = hMono;

	// Set functions
	mono_runtime_invoke = (mono_runtime_invoke_t)GetProcAddress(hMono, "mono_runtime_invoke");

	il2cpp_method_get_token = (il2cpp_method_get_token_t)GetProcAddress(hIL2CPP, "il2cpp_method_get_token");
	mono_method_get_token = (mono_method_get_token_t)GetProcAddress(hMono, "mono_method_get_token");

	mono_method_get_unmanaged_thunk = (mono_method_get_unmanaged_thunk_t)GetProcAddress(hMono, "mono_method_get_unmanaged_thunk");
}

mono_runtime_invoke_t BridgeMethod::mono_runtime_invoke = NULL;

il2cpp_method_get_token_t BridgeMethod::il2cpp_method_get_token = NULL;
mono_method_get_token_t BridgeMethod::mono_method_get_token = NULL;

mono_method_get_unmanaged_thunk_t BridgeMethod::mono_method_get_unmanaged_thunk = NULL;

HMODULE BridgeMethod::hIL2CPP = NULL;
HMODULE BridgeMethod::hMono = NULL;
#pragma endregion