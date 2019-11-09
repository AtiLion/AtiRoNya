#pragma once

#include "InternalHelpers.hpp"

class FileManager {
public:
	static std::string MainDir;
	static std::string CPPModsDir;
	static std::string NETModsDir;

	static void Initialize();
	static void LoadCPP(void (*fn)(const wchar_t*));
};