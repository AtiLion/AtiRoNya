#include "Assembly.h"

#pragma region Assembly
void BridgeAssembly::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeAssembly::hIL2CPP = hIL2CPP;
	BridgeAssembly::hMono = hMono;

	// Set functions
	mono_assembly_get_image = (mono_assembly_get_image_t)GetProcAddress(hMono, "mono_assembly_get_image");
	il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)GetProcAddress(hIL2CPP, "il2cpp_assembly_get_image");
}

mono_assembly_get_image_t BridgeAssembly::mono_assembly_get_image = NULL;
il2cpp_assembly_get_image_t BridgeAssembly::il2cpp_assembly_get_image = NULL;

HMODULE BridgeAssembly::hIL2CPP = NULL;
HMODULE BridgeAssembly::hMono = NULL;
#pragma endregion

#pragma region Image
void BridgeImage::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeImage::hIL2CPP = hIL2CPP;
	BridgeImage::hMono = hMono;

	// Set functions
	il2cpp_image_get_class_count = (il2cpp_image_get_class_count_t)GetProcAddress(hIL2CPP, "il2cpp_image_get_class_count");

	il2cpp_image_get_class = (il2cpp_image_get_class_t)GetProcAddress(hIL2CPP, "il2cpp_image_get_class");
}

il2cpp_image_get_class_count_t BridgeImage::il2cpp_image_get_class_count = NULL;

il2cpp_image_get_class_t BridgeImage::il2cpp_image_get_class = NULL;

HMODULE BridgeImage::hIL2CPP = NULL;
HMODULE BridgeImage::hMono = NULL;
#pragma endregion