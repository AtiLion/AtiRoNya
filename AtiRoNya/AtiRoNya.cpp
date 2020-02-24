#include "AtiRoNya.h"
#include "InternalHelpers.hpp"

#include "Hooking/Hooks.h"
#include "Bridge/Metadata/Metadata.h"
#include "Bridge/Assembly/Assembly.h"
#include "Bridge/Class/Class.h"
#include "Bridge/Method/Method.h"
#include "Bridge/String/String.h"
#include "Bridge/Array/Array.h"

#include "Externals/MonoExternals.h"

#pragma region Defaults
HMODULE AtiRoNya::hGameAssembly = NULL;
HMODULE AtiRoNya::hMono = NULL;

void* AtiRoNya::pIL2CPPDomain = NULL;
void* AtiRoNya::pMonoDomain = NULL;

bool AtiRoNya::bModsLoaded = false;
#pragma endregion

#pragma region Initializers
void Init_AtiRoNya() {
	ConsoleUtils::Log("Starting AtiRoNya...");

	// Load mono
	AtiRoNya::hMono = LoadLibrary("AtiRoNya\\Mono\\mono.dll");
	LoadLibrary("AtiRoNya\\Mono\\MonoPosixHelper.dll");

	// Hook LLW
	Hooking::LLW(true);
}
void Destroy_AtiRoNya() {
	// Cleanup hooks
	Hooking::LLW(false);
	Hooking::init(false);
}
#pragma endregion

#pragma region Mono Functions
bool AtiRoNya::Start_Mono() {
	if (!hGameAssembly || !hMono)
		return false;
	ConsoleUtils::Log("Starting Mono...");

	// Initialize bridge
	BridgeMono::Initialize(hGameAssembly, hMono);
	BridgeDomain::Initialize(hGameAssembly, hMono);
	BridgeAssembly::Initialize(hGameAssembly, hMono);
	BridgeClass::Initialize(hGameAssembly, hMono);
	BridgeMethod::Initialize(hGameAssembly, hMono);
	BridgeImage::Initialize(hGameAssembly, hMono);
	BridgeString::Initialize(hGameAssembly, hMono);
	BridgeArray::Initialize(hGameAssembly, hMono);

	// Setup Mono working directories
	BridgeMono::mono_set_assemblies_path("AtiRoNya\\Game");
	BridgeMono::mono_set_config_dir("AtiRoNya\\etc");

	// Start Mono domain
	pMonoDomain = BridgeMono::mono_jit_init("AtiRoNya Domain");

	// Check
	if (pMonoDomain) {
		InitExternals();
		ConsoleUtils::Log("Mono domain has been started! We have Mono :)");
	}
	else
		ConsoleUtils::Log("Failed to start Mono domain! Well shit...");
	return (pMonoDomain != NULL);
}
#pragma endregion

#pragma region Loaders
void* AtiRoNya::Load_NetDll(const char* file) {
	if (!hGameAssembly || !hMono || !pMonoDomain)
		return NULL;
	if (!FileUtils::fileExists(file))
		return NULL;
	std::cout << ConsoleUtils::GetPrefix() << "Loading " << file << "..." << std::endl;

	// Open Assembly
	MonoAssembly* assembly = BridgeDomain::mono_domain_assembly_open((MonoDomain*)pMonoDomain, file);
	if (!assembly)
		return NULL;

	// Get image
	return BridgeAssembly::mono_assembly_get_image(assembly);
}
bool AtiRoNya::Run_NetDll(const char* file) {
	// Load assembly
	MonoImage* assembly = (MonoImage*)Load_NetDll(file);
	if (!assembly) return false;

	// Get Class
	MonoClass* klass = BridgeClass::mono_class_from_name(assembly, "", "Bootloader");
	if (!klass)
		return false;

	// Get Method
	MonoMethod* method = BridgeClass::mono_class_get_method_from_name(klass, "Main", 0);
	if (!method)
		return false;

	// Execute
	BridgeMethod::mono_runtime_invoke(method, NULL, NULL, NULL);

	// End
	std::cout << ConsoleUtils::GetPrefix() << "Executed " << file << std::endl;
	return true;
}
void AtiRoNya::Load_NET() {
	if (!hGameAssembly || !hMono || !pMonoDomain)
		return;

	// Load AtiRoNyaSDK
	if (FileUtils::fileExists("AtiRoNya\\AtiRoNyaSDK.dll"))
		Load_NetDll("AtiRoNya\\AtiRoNyaSDK.dll");

	// Execute RuntimeDumper
	if (FileUtils::fileExists("AtiRoNya\\RuntimeDumper.dll"))
		Run_NetDll("AtiRoNya\\RuntimeDumper.dll");

	// Execute ModLoader
	if (FileUtils::fileExists("AtiRoNya\\Loader.dll"))
		Run_NetDll("AtiRoNya\\Loader.dll");

	// Execute TestNet
	if (FileUtils::fileExists("AtiRoNya\\TestNet.dll"))
		Run_NetDll("AtiRoNya\\TestNet.dll");
}
#pragma endregion

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		Init_AtiRoNya();
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		Destroy_AtiRoNya();
        break;
    }
    return TRUE;
}

