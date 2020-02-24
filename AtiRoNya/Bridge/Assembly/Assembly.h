#pragma once

#include "../Bridge.h"

#pragma region Assembly
DO_API(MonoImage*, (*mono_assembly_get_image_t), (MonoAssembly* assembly));
DO_API(IL2CPPImage*, (*il2cpp_assembly_get_image_t), (IL2CPPAssembly* assembly));

class BridgeAssembly {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_assembly_get_image_t mono_assembly_get_image;
	static il2cpp_assembly_get_image_t il2cpp_assembly_get_image;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion

#pragma region Image
DO_API(uint32_t, (*il2cpp_image_get_class_count_t), (IL2CPPImage* image));

DO_API(IL2CPPClass*, (*il2cpp_image_get_class_t), (IL2CPPImage* image, uint32_t index));

class BridgeImage {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static il2cpp_image_get_class_count_t il2cpp_image_get_class_count;

	static il2cpp_image_get_class_t il2cpp_image_get_class;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion