#include "VRCLoader.h"
#include "Exports.h"

#pragma region Global Functions
void Init_Loader() {
	ConsoleUtils::Log("Started VRCLoader!");

	// Create LoadLibrary hooks
	if (!Hooking::HookLoadLibrary()) {
		ConsoleUtils::Log("Failed to hook load library! Aborting...");
		return;
	}
}
void Destroy_Loader() {
	CLRHost::ReleaseCLR();
}
#pragma endregion

#pragma region VRCLoader
HMODULE VRCLoader::hGameAssembly = NULL;
IL2CPPDomain* VRCLoader::mdIL2CPPDomain = NULL;

void VRCLoader::Setup() {
	if (!VRCLoader::mdIL2CPPDomain) {
		ConsoleUtils::Log("Failed to find mono domain! Aborting...");
		return;
	}

	// Setup for injection
	CLRHost::HostCLR();
}
void VRCLoader::LoadAssemblies() {
	// Load C++
	if (!FileUtils::dirExists("CPPMods"))
		CreateDirectory("CPPMods", NULL);
	for (const auto& file : std::filesystem::directory_iterator("CPPMods"))
		if (file.path().extension() == std::string(".dll"))
			InjectCPPAssembly(file.path().c_str());

	// Load C#
	if (!FileUtils::dirExists("NETMods"))
		CreateDirectory("NETMods", NULL);
	for (const auto& file : std::filesystem::directory_iterator("NETMods"))
		if (file.path().extension() == std::string(".dll"))
			InjectNETAssembly(file.path().c_str());
}

bool VRCLoader::InjectNETAssembly(const wchar_t* file) {
	std::wcout << "Loading managed assembly " << file << std::endl;

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
	HMODULE lib = fnLoadLibraryW(lpLibFileName);

	std::wcout << "Loaded assembly: " << lpLibFileName << std::endl;
	if (wcsstr(lpLibFileName, L"GameAssembly.dll") != 0) {
		ConsoleUtils::Log("Captured GameAssembly.dll LLW! Starting hooks...");

		VRCLoader::hGameAssembly = lib;
		Build_IL2CPP(lib);
		if (!HookIL2CPP(lib)) {
			ConsoleUtils::Log("Failed to hook il2cpp! Aborting...");
			return lib;
		}
	}
	if (wcsstr(lpLibFileName, L"dxgi.dll") != 0) {
		ConsoleUtils::Log("Unity has been loaded!");

		UnHookLoadLibrary();
		VRCLoader::LoadAssemblies();
	}

	return lib;
}
#pragma endregion
#pragma region IL2CPP Hooks
il2cpp_init_t Hooking::fnil2cpp_init = NULL;
IL2CPPDomain* Hooking::_il2cpp_init(const char* name) {
	IL2CPPDomain* domain = fnil2cpp_init(name);

	VRCLoader::mdIL2CPPDomain = domain;
	std::cout << "Captured IL2CPPDomain with name " << name << std::endl;
	UnHookIL2CPP();
	VRCLoader::Setup();

	return domain;
}
#pragma endregion

bool Hooking::HookLoadLibrary() {
	// Get address
	if (!fnLoadLibraryW)
		fnLoadLibraryW = LoadLibraryW;

	// Setup detours
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Install the hooks
	ConsoleUtils::Log("Installing LoadLibrary hooks...");
	DetourAttach(&(LPVOID&)fnLoadLibraryW, _LoadLibraryW);

	// Finish
	DetourTransactionCommit();
	return true;
}
bool Hooking::UnHookLoadLibrary() {
	// Setup detours
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Disable hooks
	ConsoleUtils::Log("Disabling LoadLibrary hooks...");
	DetourDetach(&(LPVOID&)fnLoadLibraryW, _LoadLibraryW);

	// Finish
	DetourTransactionCommit();
	return true;
}

bool Hooking::HookIL2CPP(HMODULE hGameAssembly) {
	// Get address
	if (!fnil2cpp_init)
		fnil2cpp_init = (il2cpp_init_t)GetProcAddress(hGameAssembly, "il2cpp_init");

	// Setup detours
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Install the hooks
	ConsoleUtils::Log("Installing IL2CPP hooks...");
	DetourAttach(&(LPVOID&)fnil2cpp_init, _il2cpp_init);

	// Finish
	DetourTransactionCommit();
	return true;
}
bool Hooking::UnHookIL2CPP() {
	// Setup detours
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Disable hooks
	ConsoleUtils::Log("Disabling IL2CPP hooks...");
	DetourDetach(&(LPVOID&)fnil2cpp_init, _il2cpp_init);

	// Finish
	DetourTransactionCommit();
	return true;
}
#pragma endregion

#pragma region Exports
IL2CPPDomain* atironya_get_domain() {
	return VRCLoader::mdIL2CPPDomain;
}
IL2CPPImage* atironya_get_assembly(const char* name) {
	if (!VRCLoader::mdIL2CPPDomain)
		return NULL;
	IL2CPPAssembly* assembly = il2cpp_domain_assembly_open(VRCLoader::mdIL2CPPDomain, name);

	if (!assembly)
		return NULL;
	return il2cpp_assembly_get_image(assembly);
}
IL2CPPClass* atironya_get_class(const char* name_space, const char* name, IL2CPPImage* assembly) {
	if (!assembly)
		return NULL;

	return il2cpp_class_from_name(assembly, name_space, name);
}
IL2CPPMethod* atironya_get_method(const char* name, IL2CPPClass* klass, int paramcount) {
	if (!klass)
		return NULL;

	return il2cpp_class_get_method_from_name(klass, name, paramcount);
}
IL2CPPObject* atironya_execute(IL2CPPMethod* method, void* obj, void** params) {
	if (!method)
		return NULL;

	return il2cpp_runtime_invoke(method, obj, params, NULL);
}

IL2CPPString* atironya_tostring(const char* text) {
	return il2cpp_string_new(text);
}
void* atironya_from_mono(IL2CPPObject* obj) {
	if (!obj)
		return NULL;

	return il2cpp_object_unbox(obj);
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
