#pragma once

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <filesystem>

class FileUtils {
public:
	static bool fileExists(const char* fileName) {
		std::ifstream file;
		file.open(fileName, std::ios::in | std::ios::binary);

		bool exists = file.good();

		if (exists && file.is_open())
			file.close();
		return exists;
	}
	static bool dirExists(const char* dirName_in)
	{
		DWORD ftyp = GetFileAttributesA(dirName_in);

		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;
		return false;
	}
};

class ConsoleUtils {
public:
	static bool HasConsole() {
		return GetConsoleWindow() != NULL;
	}
	static void CreateConsole() {
		if (HasConsole())
			return;

		// Alloc console
		if (!AllocConsole()) {
			MessageBox(NULL, "Failed to create debug console.", NULL, MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// Setup outputs
		freopen_s(reinterpret_cast<FILE * *>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitle("VRCLoader Debug Console");
	}
	static void DestroyConsole() {
		if (!HasConsole())
			return;

		// Remove outputs
		fclose(reinterpret_cast<FILE*>(stdout));

		// Free console
		FreeConsole();
	}

	static void Log(const char* text) {
		if (!HasConsole())
			return;
		std::cout << text << std::endl;
	}
};