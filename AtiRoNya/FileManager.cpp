#include "FileManager.h"

std::string FileManager::MainDir = "AtiRoNya";
std::string FileManager::CPPModsDir = "CPPMods";
std::string FileManager::NETModsDir = "NETMods";

void FileManager::Initialize() {
	// Check NETMods directory
	if (!FileUtils::dirExists((MainDir + "\\" + NETModsDir).c_str()))
		CreateDirectoryA((MainDir + "\\" + NETModsDir).c_str(), NULL);

	// Check CPPMods directory
	if (!FileUtils::dirExists((MainDir + "\\" + CPPModsDir).c_str()))
		CreateDirectoryA((MainDir + "\\" + CPPModsDir).c_str(), NULL);
}
void FileManager::LoadCPP(void (*fn)(const wchar_t*)) {
	for (const auto& file : std::filesystem::directory_iterator((MainDir + "\\" + CPPModsDir).c_str()))
		if (file.path().extension() == std::string(".dll"))
			(*fn)(file.path().c_str());
}