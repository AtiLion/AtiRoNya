#include "VRCLoader.h"
#include "Exports.h"
#include "FileManager.h"

#pragma region Global Functions
void Init_Loader() {
	ConsoleUtils::Log("Started VRCLoader!");

	// Initialize
	FileManager::Initialize();

	// Get LLW pointers
	if (!Hooking::fnLoadLibraryW)
		Hooking::fnLoadLibraryW = LoadLibraryW;

	// Start detour transaction
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Install the hooks
	ConsoleUtils::Log("Installing LLW hooks...");
	DetourAttach(&(LPVOID&)Hooking::fnLoadLibraryW, Hooking::_LoadLibraryW);

	// Commit changes
	DetourTransactionCommit();
}
void Destroy_Loader() {
	CLRHost::ReleaseCLR();
}
#pragma endregion

#pragma region VRCLoader
HMODULE VRCLoader::hGameAssembly = NULL;
IL2CPPDomain* VRCLoader::mdIL2CPPDomain = NULL;

bool VRCLoader::bLoadedMods = false;

std::queue<std::function<void()>> VRCLoader::qOnGameLoad;

void VRCLoader::Setup() {
	if (!VRCLoader::mdIL2CPPDomain) {
		ConsoleUtils::Log("Failed to find mono domain! Aborting...");
		return;
	}

	// Setup for injection
	CLRHost::HostCLR();
}
void VRCLoader::LoadAssemblies() {
	bLoadedMods = true;

	// Priority load NET
	RunNETAssembly("AtiRoNya\\NET_SDK.dll");

	// Priority load CPP
	// TODO: Populate when needed

	// Load CPP mods
	FileManager::LoadCPP(LoadCPPAssembly);
	ConsoleUtils::Log("Successfully loaded CPP mods");

	// Load NET mods
	if (CLRHost::LoadMods((FileManager::MainDir + "\\" + FileManager::NETModsDir).c_str()))
		ConsoleUtils::Log("Successfully loaded all mods in .NET");
	else
		ConsoleUtils::Log("Failed to load mods in .NET");
}

void VRCLoader::LoadNETAssembly(const char* file) {
	std::cout << "Priority loading NET assembly " << file << std::endl;

	if (CLRHost::LoadAssembly(file))
		std::cout << "Priority loaded NET assembly " << file << std::endl;
	else
		std::cout << "Failed to priority load NET assembly " << file << std::endl;
}
void VRCLoader::RunNETAssembly(const char* file) {
	std::cout << "Priority loading and executing NET assembly " << file << std::endl;

	if (CLRHost::LoadAssemblyAndExecute(file))
		std::cout << "Priority loaded and executed NET assembly " << file << std::endl;
	else
		std::cout << "Failed to priority load/execute NET assembly " << file << std::endl;
}
void VRCLoader::LoadCPPAssembly(const wchar_t* file) {
	std::wcout << "Loading unmanaged assembly " << file << std::endl;

	LoadLibraryW(file);
}
#pragma endregion

#pragma region Hooking
#pragma region Load Library Hooks
LoadLibraryW_t Hooking::fnLoadLibraryW = NULL;
HMODULE __stdcall Hooking::_LoadLibraryW(LPCWSTR lpLibFileName) {
	HMODULE lib = fnLoadLibraryW(lpLibFileName);

	std::wcout << "Loaded assembly W: " << lpLibFileName << std::endl;
	if (wcsstr(lpLibFileName, L"GameAssembly.dll") != 0) { // This is loaded when Unity begins initialization of the NET environment
		ConsoleUtils::Log("Captured GameAssembly.dll LLW! Starting hooks...");

		// Build game information
		VRCLoader::hGameAssembly = lib;
		Build_IL2CPP(lib);

		// Get next hook pointers
		if (!fnil2cpp_init)
			fnil2cpp_init = (il2cpp_init_t)GetProcAddress(VRCLoader::hGameAssembly, "il2cpp_init");

		// Start detour transaction
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		// Install the hooks
		ConsoleUtils::Log("Installing IL2CPP hooks...");
		DetourAttach(&(LPVOID&)fnil2cpp_init, _il2cpp_init);

		// Commit changes
		DetourTransactionCommit();
	}
	if (wcsstr(lpLibFileName, L"dxgi.dll") != 0 && !VRCLoader::bLoadedMods) { // This is loaded when DirectX is loaded
		ConsoleUtils::Log("Unity has been loaded!");

		// Load our assemblies
		VRCLoader::LoadAssemblies();
	}
	if (wcsstr(lpLibFileName, L"sqlite3.dll") != 0) { // This is loaded when the game is loaded
		ConsoleUtils::Log("Game has been loaded!");

		// Start detour transaction
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		// Remove old hooks
		ConsoleUtils::Log("Removing LLW hooks...");
		DetourDetach(&(LPVOID&)fnLoadLibraryW, _LoadLibraryW);

		// Commit changes
		DetourTransactionCommit();

		// Execute on load functions
		while (!VRCLoader::qOnGameLoad.empty()) {
			try
			{
				(VRCLoader::qOnGameLoad.front())();
				VRCLoader::qOnGameLoad.pop();
			}
			catch (...) {}
		}
	}

	return lib;
}
#pragma endregion
#pragma region IL2CPP Hooks
il2cpp_init_t Hooking::fnil2cpp_init = NULL;
IL2CPPDomain* Hooking::_il2cpp_init(const char* name) {
	IL2CPPDomain* domain = fnil2cpp_init(name);

	// Capture the domain
	VRCLoader::mdIL2CPPDomain = domain;
	std::cout << "Captured IL2CPPDomain with name " << name << std::endl;

	// Start detour transaction
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Disable hooks
	ConsoleUtils::Log("Removing IL2CPP hooks...");
	DetourDetach(&(LPVOID&)fnil2cpp_init, _il2cpp_init);

	// Commit changes
	DetourTransactionCommit();

	// Setup the COR environment
	VRCLoader::Setup();

	return domain;
}
#pragma endregion

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Init_Loader();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Destroy_Loader();
		break;
	}
	return TRUE;
}
