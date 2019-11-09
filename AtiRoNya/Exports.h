#pragma once

#include "il2cpp.h"

extern "C" {
	__declspec(dllexport) IL2CPPDomain* __stdcall atironya_get_domain();

	__declspec(dllexport) IL2CPPImage* __stdcall atironya_get_assembly(const char* name);

	__declspec(dllexport) IL2CPPArray* __stdcall atironya_box_array(void** _array, IL2CPPClass* type, size_t objectSize, int length);
	__declspec(dllexport) void** __stdcall atironya_unbox_array(IL2CPPArray* _array, size_t objectSize);

	__declspec(dllexport) void __stdcall atironya_wait_for_game(void (__stdcall *callback)());

	__declspec(dllexport) IL2CPPMethodPointer __stdcall atironya_override(IL2CPPMethod* method, IL2CPPMethodPointer newMethod);
}