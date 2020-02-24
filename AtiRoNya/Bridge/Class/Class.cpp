#include "Class.h"

#pragma region Class
void BridgeClass::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeClass::hIL2CPP = hIL2CPP;
	BridgeClass::hMono = hMono;

	// Set functions
	mono_class_get = (mono_class_get_t)GetProcAddress(hMono, "mono_class_get");

	mono_class_from_name = (mono_class_from_name_t)GetProcAddress(hMono, "mono_class_from_name");

	mono_class_get_method_from_name = (mono_class_get_method_from_name_t)GetProcAddress(hMono, "mono_class_get_method_from_name");

	il2cpp_class_get_type_token = (il2cpp_class_get_type_token_t)GetProcAddress(hIL2CPP, "il2cpp_class_get_type_token");

	il2cpp_class_get_methods = (il2cpp_class_get_methods_t)GetProcAddress(hIL2CPP, "il2cpp_class_get_methods");
	mono_class_get_methods = (mono_class_get_methods_t)GetProcAddress(hMono, "mono_class_get_methods");
}

mono_class_get_t BridgeClass::mono_class_get = NULL;

mono_class_from_name_t BridgeClass::mono_class_from_name = NULL;

mono_class_get_method_from_name_t BridgeClass::mono_class_get_method_from_name = NULL;

il2cpp_class_get_type_token_t BridgeClass::il2cpp_class_get_type_token = NULL;

il2cpp_class_get_methods_t BridgeClass::il2cpp_class_get_methods = NULL;
mono_class_get_methods_t BridgeClass::mono_class_get_methods = NULL;

HMODULE BridgeClass::hIL2CPP = NULL;
HMODULE BridgeClass::hMono = NULL;
#pragma endregion