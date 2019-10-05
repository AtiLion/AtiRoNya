#include "VRCLoader.h"
#include "MinHook.h"

#pragma region Global Functions
void Init_Loader() {
	ConsoleUtils::Log("Started VRCLoader!");

	// Initialize
	if (MH_Initialize() != MH_OK)
		return;

	// Create LoadLibrary hooks
	if (!Hooking::HookLoadLibrary()) {
		ConsoleUtils::Log("Failed to hook load library! Aborting...");
		return;
	}
}
void Destroy_Loader() {
	if (MH_Uninitialize() != MH_OK)
		ConsoleUtils::Log("Failed to unload minhook!");
	CLRHost::ReleaseCLR();
}
#pragma endregion

#pragma region VRCLoader
HMODULE VRCLoader::hGameAssembly = NULL;
MonoDomain* VRCLoader::mdIL2CPPDomain = NULL;

void VRCLoader::Setup() {
	if (!VRCLoader::mdIL2CPPDomain) {
		ConsoleUtils::Log("Failed to find mono domain! Aborting...");
		return;
	}

	// Setup for injection
	CLRHost::HostCLR();

	// Load C++
	if (!FileUtils::dirExists("CPPMods"))
		CreateDirectory("CPPMods", NULL);
	for (const auto& file : std::experimental::filesystem::directory_iterator("CPPMods"))
		if (file.path().extension() == std::string(".dll"))
			InjectCPPAssembly(file.path().c_str());

	// Load C#
	if (!FileUtils::dirExists("NETMods"))
		CreateDirectory("NETMods", NULL);
	for (const auto& file : std::experimental::filesystem::directory_iterator("NETMods"))
		if (file.path().extension() == std::string(".dll"))
			InjectNETAssembly(file.path().c_str());
}

bool VRCLoader::InjectNETAssembly(const wchar_t* file) {
	std::wcout << "Loading assembly " << file << std::endl;

	CLRHost::ExecuteAssembly(file, L"Bootloader", L"Main");
	return true;
}
bool VRCLoader::InjectCPPAssembly(const wchar_t* file) {
	std::wcout << "Loading unmanaged assembly " << file << std::endl;

	LoadLibraryW(file);
	return true;
}
#pragma endregion

#pragma region Hooking
#pragma region Load Library Hooks
LoadLibraryW_t Hooking::fnLoadLibraryW = NULL;
HMODULE __stdcall Hooking::_LoadLibraryW(LPCWSTR lpLibFileName) {
	LoadLibraryW_t func = (LoadLibraryW_t)fnLoadLibraryW;
	HMODULE lib = func(lpLibFileName);

	if (wcsstr(lpLibFileName, L"GameAssembly.dll") != 0) {
		ConsoleUtils::Log("Captured GameAssembly.dll LLW! Starting hooks...");

		VRCLoader::hGameAssembly = lib;
		Build_IL2CPP(lib);
		if (!HookIL2CPP(lib)) {
			ConsoleUtils::Log("Failed to hook il2cpp! Aborting...");
			return lib;
		}
	}

	return lib;
}
#pragma endregion

#pragma region IL2CPP Hooks
il2cpp_init_t Hooking::fnil2cpp_init = NULL;
MonoDomain* Hooking::_il2cpp_init(const char* name) {
	il2cpp_init_t func = (il2cpp_init_t)fnil2cpp_init;
	MonoDomain* domain = func(name);

	VRCLoader::mdIL2CPPDomain = domain;
	std::cout << "Captured MonoDomain with name " << name << std::endl;
	UnHookLoadLibrary();
	VRCLoader::Setup();

	return domain;
}
#pragma endregion

bool Hooking::HookLoadLibrary() {
	// Create hooks
	ConsoleUtils::Log("Creating LoadLibrary hooks...");
	if (MH_CreateHook(&LoadLibraryW, &Hooking::_LoadLibraryW, reinterpret_cast<LPVOID*>(&fnLoadLibraryW)) != MH_OK)
		return false;

	// Enable the hooks
	ConsoleUtils::Log("Enabling LoadLibrary hooks...");
	if (MH_EnableHook(&LoadLibraryW) != MH_OK)
		return false;

	// Return
	return true;
}
bool Hooking::UnHookLoadLibrary() {
	// Disable hooks
	ConsoleUtils::Log("Disabling LoadLibrary hooks...");
	if (MH_DisableHook(&LoadLibraryW) != MH_OK)
		return false;

	// Return
	return true;
}

bool Hooking::HookIL2CPP(HMODULE hGameAssembly) {
	// Grab procs
	LPVOID lpvil2cpp_init = (LPVOID)GetProcAddress(hGameAssembly, "il2cpp_init");

	// Create hooks
	ConsoleUtils::Log("Creating IL2CPP hooks...");
	if (MH_CreateHook(lpvil2cpp_init, &Hooking::_il2cpp_init, reinterpret_cast<LPVOID*>(&fnil2cpp_init)) != MH_OK)
		return false;

	// Enable the hooks
	ConsoleUtils::Log("Enabling IL2CPP hooks...");
	if (MH_EnableHook(lpvil2cpp_init) != MH_OK)
		return false;

	// Return
	return true;
}
#pragma endregion