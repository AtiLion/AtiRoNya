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

	static void Setup();
	static void LoadAssemblies();

	static bool InjectCPPAssembly(const wchar_t* file);
	static bool InjectNETAssembly(const wchar_t* file);
};

class Hooking {
private:
	static LoadLibraryW_t fnLoadLibraryW;
	static HMODULE __stdcall _LoadLibraryW(LPCWSTR lpLibFileName);

	static il2cpp_init_t fnil2cpp_init;
	static IL2CPPDomain* _il2cpp_init(const char* name);
public:
	static bool HookLoadLibrary();
	static bool UnHookLoadLibrary();

	static bool HookIL2CPP(HMODULE hGameAssembly);
	static bool UnHookIL2CPP();
};