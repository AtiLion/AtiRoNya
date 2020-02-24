#include "Metadata.h"

#pragma region Domain
void BridgeDomain::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeDomain::hIL2CPP = hIL2CPP;
	BridgeDomain::hMono = hMono;

	// Set functions
	mono_domain_assembly_open = (mono_domain_assembly_open_t)GetProcAddress(hMono, "mono_domain_assembly_open");
	il2cpp_domain_assembly_open = (il2cpp_domain_assembly_open_t)GetProcAddress(hIL2CPP, "il2cpp_domain_assembly_open");
}

mono_domain_assembly_open_t BridgeDomain::mono_domain_assembly_open = NULL;
il2cpp_domain_assembly_open_t BridgeDomain::il2cpp_domain_assembly_open = NULL;

HMODULE BridgeDomain::hIL2CPP = NULL;
HMODULE BridgeDomain::hMono = NULL;
#pragma endregion

#pragma region Mono
void BridgeMono::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeMono::hIL2CPP = hIL2CPP;
	BridgeMono::hMono = hMono;

	// Set functions
	mono_set_dirs = (mono_set_dirs_t)GetProcAddress(hMono, "mono_set_dirs");
	mono_set_assemblies_path = (mono_set_assemblies_path_t)GetProcAddress(hMono, "mono_set_assemblies_path");
	mono_set_config_dir = (mono_set_config_dir_t)GetProcAddress(hMono, "mono_set_config_dir");

	il2cpp_init = (il2cpp_init_t)GetProcAddress(hIL2CPP, "il2cpp_init");
	mono_jit_init = (mono_jit_init_t)GetProcAddress(hMono, "mono_jit_init");

	mono_add_internal_call = (mono_add_internal_call_t)GetProcAddress(hMono, "mono_add_internal_call");
}

mono_set_dirs_t BridgeMono::mono_set_dirs = NULL;
mono_set_assemblies_path_t BridgeMono::mono_set_assemblies_path = NULL;
mono_set_config_dir_t BridgeMono::mono_set_config_dir = NULL;

il2cpp_init_t BridgeMono::il2cpp_init = NULL;
mono_jit_init_t BridgeMono::mono_jit_init = NULL;

mono_add_internal_call_t BridgeMono::mono_add_internal_call = NULL;

HMODULE BridgeMono::hIL2CPP = NULL;
HMODULE BridgeMono::hMono = NULL;
#pragma endregion