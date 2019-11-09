#include "CLRHost.h"

bool CLRHost::clrRunning = false;

ICLRMetaHost* CLRHost::clrInstance = NULL;
ICLRRuntimeInfo* CLRHost::runtimeInfo = NULL;
ICLRRuntimeHost* CLRHost::runtimeHost = NULL;
ICLRControl* CLRHost::clrControl = NULL;

INetDomain* CLRHost::netDomain = NULL;

bool CLRHost::HostCLR() {
	ConsoleUtils::Log("Setting up CLR host...");

	ConsoleUtils::Log("Getting CLR meta host...");
	if (CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)& clrInstance) != S_OK) {
		ConsoleUtils::Log("Failed to create meta host instance!");
		return false;
	}
	ConsoleUtils::Log("Getting CLR runtime information...");
	if (clrInstance->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)& runtimeInfo) != S_OK) {
		ConsoleUtils::Log("Failed to get runtime information!");
		return false;
	}
	ConsoleUtils::Log("Getting CLR runtime host...");
	if (runtimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)& runtimeHost) != S_OK) {
		ConsoleUtils::Log("Failed to get runtime host interface!");
		return false;
	}
	ConsoleUtils::Log("Creating custom CLR IHostControl...");
	NetHostControl* hostControl = new NetHostControl();
	if (runtimeHost->SetHostControl((IHostControl*)hostControl) != S_OK) {
		ConsoleUtils::Log("Failed to create custom CLR IHostControl!");
		delete hostControl;
		return false;
	}
	ConsoleUtils::Log("Grabbing CLR controller...");
	if (runtimeHost->GetCLRControl(&clrControl) != S_OK) {
		ConsoleUtils::Log("Failed to grab CLR controller!");
		return false;
	}
	ConsoleUtils::Log("Setting custom AppDomain manager...");
	if (clrControl->SetAppDomainManagerType(L"NativeHandler", L"NativeHandler.NativeAppDomain") != S_OK) {
		ConsoleUtils::Log("Failed to set custom AppDomain manager!");
		return false;
	}
	ConsoleUtils::Log("Starting CLR host...");
	if (runtimeHost->Start() != S_OK) {
		ConsoleUtils::Log("Failed to start CLR host!");
		return false;
	}

	ConsoleUtils::Log("Saving CLR interface reference...");
	netDomain = hostControl->GetINetDomain();

	ConsoleUtils::Log("CLR host up and running! We have .NET :)");
	clrRunning = true;
	return true;
}
void CLRHost::ReleaseCLR() {
	if (!clrRunning)
		return;

	runtimeHost->Stop();
	runtimeHost->Release();
	runtimeInfo->Release();
	clrInstance->Release();
}

bool CLRHost::LoadAssembly(const char* assembly) {
	if (!clrRunning)
		return false;

	return (netDomain->LoadAssembly(assembly) == S_OK);
}
bool CLRHost::LoadAssemblyAndExecute(const char* assembly) {
	if (!clrRunning)
		return false;

	return (netDomain->LoadAssemblyAndExecute(assembly) == S_OK);
}
bool CLRHost::LoadMods(const char* path) {
	if (!clrRunning)
		return false;

	return (netDomain->LoadMods(path) == S_OK);
}