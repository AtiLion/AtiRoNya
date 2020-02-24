#pragma once

#include "../Bridge.h"

#pragma region Domain
DO_API(MonoAssembly*, (*mono_domain_assembly_open_t), (MonoDomain* domain, const char* file));
DO_API(IL2CPPAssembly*, (*il2cpp_domain_assembly_open_t), (IL2CPPDomain* domain, const char* name));

class BridgeDomain {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_domain_assembly_open_t mono_domain_assembly_open;
	static il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion

#pragma region Mono
DO_API(void, (*mono_set_dirs_t), (const char* lib, const char* etc));
DO_API(void, (*mono_set_assemblies_path_t), (const char* path));
DO_API(void, (*mono_set_config_dir_t), (const char* path));

DO_API(IL2CPPDomain*, (*il2cpp_init_t), (const char* domain_name));
DO_API(MonoDomain*, (*mono_jit_init_t), (const char* domain_name));

DO_API(void, (*mono_add_internal_call_t), (const char* name, void* func));

class BridgeMono {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_set_dirs_t mono_set_dirs;
	static mono_set_assemblies_path_t mono_set_assemblies_path;
	static mono_set_config_dir_t mono_set_config_dir;

	static il2cpp_init_t il2cpp_init;
	static mono_jit_init_t mono_jit_init;

	static mono_add_internal_call_t mono_add_internal_call;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion