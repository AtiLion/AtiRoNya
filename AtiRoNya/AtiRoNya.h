#pragma once

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <queue>
#include <functional>
#include <map>

class AtiRoNya {
public:
	static HMODULE hGameAssembly;
	static HMODULE hMono;
	
	static void* pIL2CPPDomain;
	static void* pMonoDomain;

	static bool bModsLoaded;

	static bool Start_Mono();

	static void* Load_NetDll(const char* file);
	static bool Run_NetDll(const char* file);
	static void Load_NET();
};