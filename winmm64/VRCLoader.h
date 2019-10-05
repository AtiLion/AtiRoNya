#pragma once

#include "InternalHelpers.hpp"
#include "HookTypes.h"
#include "il2cpp.h"
#include "CLRHost.h"

void Init_Loader();
void Destroy_Loader();

class VRCLoader {
public:
	static HMODULE hGameAssembly;
	static MonoDomain* mdIL2CPPDomain;

	static void Setup();

	static bool InjectCPPAssembly(const wchar_t* file);
	static bool InjectNETAssembly(const wchar_t* file);
};

class Hooking {
private:
	static LoadLibraryW_t fnLoadLibraryW;
	static HMODULE __stdcall _LoadLibraryW(LPCWSTR lpLibFileName);

	static il2cpp_init_t fnil2cpp_init;
	static MonoDomain* _il2cpp_init(const char* name);
public:
	static bool HookLoadLibrary();
	static bool UnHookLoadLibrary();

	static bool HookIL2CPP(HMODULE hGameAssembly);
};