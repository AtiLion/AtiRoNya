#pragma once

#include "../Bridge.h"

#pragma region String
DO_API(char*, (*mono_string_to_utf8_t), (MonoString* str));

class BridgeString {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_string_to_utf8_t mono_string_to_utf8;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion
