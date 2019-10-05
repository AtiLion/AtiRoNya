#include "il2cpp.h"

il2cpp_init_t il2cpp_init = NULL;
il2cpp_thread_attach_t il2cpp_thread_attach = NULL;
il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open = NULL;
il2cpp_assembly_get_image_t il2cpp_assembly_get_image = NULL;
il2cpp_class_from_name_t il2cpp_class_from_name = NULL;
il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name = NULL;
il2cpp_runtime_invoke_t il2cpp_runtime_invoke = NULL;

void Build_IL2CPP(HMODULE hMono) {
	if (!hMono)
		return;

	// Grab Mono functions
	il2cpp_init = (il2cpp_init_t)GetProcAddress(hMono, "il2cpp_init");
	il2cpp_thread_attach = (il2cpp_thread_attach_t)GetProcAddress(hMono, "il2cpp_thread_attach");
	il2cpp_domain_assembly_open = (il2cpp_domain_assembly_open_t)GetProcAddress(hMono, "il2cpp_domain_assembly_open");
	il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)GetProcAddress(hMono, "il2cpp_assembly_get_image");
	il2cpp_class_from_name = (il2cpp_class_from_name_t)GetProcAddress(hMono, "il2cpp_class_from_name");
	il2cpp_class_get_method_from_name = (il2cpp_class_get_method_from_name_t)GetProcAddress(hMono, "il2cpp_class_get_method_from_name");
	il2cpp_runtime_invoke = (il2cpp_runtime_invoke_t)GetProcAddress(hMono, "il2cpp_runtime_invoke");

	// Log
	ConsoleUtils::Log("Built IL2CPP runtime!");
}