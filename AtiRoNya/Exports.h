#pragma once

#include "il2cpp.h"

extern "C" {
	__declspec(dllexport) IL2CPPDomain* __stdcall atironya_get_domain();
	__declspec(dllexport) IL2CPPImage* __stdcall atironya_get_assembly(const char* name);
	__declspec(dllexport) IL2CPPClass* __stdcall atironya_get_class(const char* name_space, const char* name, IL2CPPImage* assembly);
	__declspec(dllexport) IL2CPPMethod* __stdcall atironya_get_method(const char* name, IL2CPPClass* klass, int paramcount = 0);
	__declspec(dllexport) IL2CPPObject* __stdcall atironya_execute(IL2CPPMethod* method, void* obj, void** params);

	__declspec(dllexport) IL2CPPString* __stdcall atironya_tostring(const char* text);
	__declspec(dllexport) void* __stdcall atironya_from_mono(IL2CPPObject* obj);
}