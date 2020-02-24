#include "Hooks.h"

#include "../InternalHelpers.hpp"

#pragma region LoadLibraryW Hook
LoadLibraryW_t Hooking::fnLoadLibraryW = NULL;
void Hooking::LLW(bool detour) {
	if (!detour && !fnLoadLibraryW)
		return;
	if (!fnLoadLibraryW)
		fnLoadLibraryW = LoadLibraryW;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (detour) {
		ConsoleUtils::Log("Installing LLW hook...");
		DetourAttach(&(LPVOID&)fnLoadLibraryW, _LoadLibraryW);
	}
	else {
		ConsoleUtils::Log("Removing LLW hook...");
		DetourDetach(&(LPVOID&)fnLoadLibraryW, _LoadLibraryW);
		fnLoadLibraryW = NULL;
	}

	DetourTransactionCommit();
}

HMODULE Hooking::_LoadLibraryW(LPCWSTR lpLibFileName) {
	HMODULE lib = fnLoadLibraryW(lpLibFileName);

	if (wcsstr(lpLibFileName, L"GameAssembly.dll") != 0) { // IL2CPP
		ConsoleUtils::Log("Captured GameAssembly.dll");

		// Save assembly + hook init
		AtiRoNya::hGameAssembly = lib;
		init(true);
	}
	else if (wcsstr(lpLibFileName, L"dxgi.dll") != 0 && !AtiRoNya::bModsLoaded) { // Unity
		ConsoleUtils::Log("Unity has been loaded");

		// Remove hooks
		init(false);
		LLW(false);

		// Set mods as loaded + load mods
		AtiRoNya::bModsLoaded = true;
		AtiRoNya::Load_NET();
	}
	return lib;
}
#pragma endregion

#pragma region il2cpp_init Hook
il2cpp_init_t Hooking::fn_il2cpp_init = NULL;
void Hooking::init(bool detour) {
	if (!detour && !fn_il2cpp_init)
		return;
	if (!fn_il2cpp_init)
		fn_il2cpp_init = (il2cpp_init_t)GetProcAddress(AtiRoNya::hGameAssembly, "il2cpp_init");

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (detour) {
		ConsoleUtils::Log("Installing il2cpp_init hook...");
		DetourAttach(&(LPVOID&)fn_il2cpp_init, _il2cpp_init);
	}
	else {
		ConsoleUtils::Log("Removing il2cpp_init hook...");
		DetourDetach(&(LPVOID&)fn_il2cpp_init, _il2cpp_init);
		fn_il2cpp_init = NULL;
	}

	DetourTransactionCommit();
}

IL2CPPDomain* Hooking::_il2cpp_init(const char* domain_name) {
	// Capture IL2CPP domain
	IL2CPPDomain* domain = fn_il2cpp_init(domain_name);
	AtiRoNya::pIL2CPPDomain = domain;

	// Start Mono
	if (!AtiRoNya::Start_Mono()) {
		init(false);
		LLW(false);
		return domain;
	}

	// Cleanup
	init(false);
	return domain;
}
#pragma endregion