#pragma once

#include "../AtiRoNya.h"
#include "../Bridge/Metadata/Metadata.h"
#include "../Detours/detours.h"

#pragma region Types
typedef HMODULE(__stdcall* LoadLibraryW_t) (LPCWSTR lpLibFileName);
#pragma endregion

class Hooking {
public:
	static LoadLibraryW_t fnLoadLibraryW;
	static void LLW(bool detour);

	static il2cpp_init_t fn_il2cpp_init;
	static void init(bool detour);
private:
	static HMODULE __stdcall _LoadLibraryW(LPCWSTR lpLibFileName);
	static IL2CPPDomain* _il2cpp_init(const char* domain_name);
};