#pragma once

#include "InternalHelpers.hpp"
#include "HookTypes.h"
#include "il2cpp.h"
#include "CLRHost.h"
#include "detours/detours.h"

void Init_Loader();
void Destroy_Loader();

class VRCLoader {
public:
	static HMODULE hGameAssembly;
	static IL2CPPDomain* mdIL2CPPDomain;

	static bool bLoadedMods;

	static std::queue<std::function<void()>> qOnGameLoad;

	static void Setup();
	static void LoadAssemblies();

	static void LoadCPPAssembly(const wchar_t* file);
	static void LoadNETAssembly(const char* file);
	static void RunNETAssembly(const char* file);
};

class Hooking {
public:
	static LoadLibraryW_t fnLoadLibraryW;
	static HMODULE __stdcall _LoadLibraryW(LPCWSTR lpLibFileName);

	static il2cpp_init_t fnil2cpp_init;
	static IL2CPPDomain* _il2cpp_init(const char* name);
};