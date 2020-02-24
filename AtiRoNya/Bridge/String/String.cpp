#include "String.h"

#pragma region String
void BridgeString::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeString::hIL2CPP = hIL2CPP;
	BridgeString::hMono = hMono;

	// Set functions
	mono_string_to_utf8 = (mono_string_to_utf8_t)GetProcAddress(hMono, "mono_string_to_utf8");
}

mono_string_to_utf8_t BridgeString::mono_string_to_utf8 = NULL;

HMODULE BridgeString::hIL2CPP = NULL;
HMODULE BridgeString::hMono = NULL;
#pragma endregion