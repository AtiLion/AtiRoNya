#include "CLRHost.h"

bool CLRHost::clrRunning = false;

ICLRMetaHost* CLRHost::metaHost = NULL;
ICLRRuntimeInfo* CLRHost::runtimeInfo = NULL;
ICLRRuntimeHost* CLRHost::runtimeHost = NULL;

bool CLRHost::HostCLR() {
	ConsoleUtils::Log("Setting up CLR host...");

	ConsoleUtils::Log("Getting CLR meta host...");
	if (CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)& metaHost) != S_OK) {
		ConsoleUtils::Log("Failed to create meta host instance!");
		return false;
	}
	ConsoleUtils::Log("Getting CLR runtime information...");
	if (metaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)& runtimeInfo) != S_OK) {
		ConsoleUtils::Log("Failed to get runtime information!");
		return false;
	}
	ConsoleUtils::Log("Getting CLR runtime host...");
	if (runtimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)& runtimeHost) != S_OK) {
		ConsoleUtils::Log("Failed to get runtime host interface!");
		return false;
	}
	ConsoleUtils::Log("Starting CLR host...");
	if (runtimeHost->Start() != S_OK) {
		ConsoleUtils::Log("Failed to start CLR host!");
		return false;
	}

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
	metaHost->Release();
}

DWORD CLRHost::ExecuteAssembly(LPCWSTR dllPath, LPCWSTR className, LPCWSTR funcName) {
	if (!clrRunning)
		return NULL;

	DWORD ret;
	runtimeHost->ExecuteInDefaultAppDomain(dllPath, className, funcName, GetCommandLineW(), &ret);
	return ret;
}