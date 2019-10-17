#pragma once

#include "InternalHelpers.hpp"
#include <metahost.h>
#pragma comment(lib, "mscoree.lib")

class CLRHost {
private:
	static bool clrRunning;

	static ICLRMetaHost* metaHost;
	static ICLRRuntimeInfo* runtimeInfo;
	static ICLRRuntimeHost* runtimeHost;

public:
	static bool HostCLR();
	static void ReleaseCLR();
	static DWORD ExecuteAssembly(LPCWSTR dllPath, LPCWSTR className, LPCWSTR funcName);
};