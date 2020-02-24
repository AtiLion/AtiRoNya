#include "Array.h"

#pragma region Array
void BridgeArray::Initialize(HMODULE hIL2CPP, HMODULE hMono) {
	// Set variables
	BridgeArray::hIL2CPP = hIL2CPP;
	BridgeArray::hMono = hMono;

	// Set functions
	mono_array_length = (mono_array_length_t)GetProcAddress(hMono, "mono_array_length");

	mono_array_addr_with_size = (mono_array_addr_with_size_t)GetProcAddress(hMono, "mono_array_addr_with_size");
}

mono_array_length_t BridgeArray::mono_array_length = NULL;

mono_array_addr_with_size_t BridgeArray::mono_array_addr_with_size = NULL;

HMODULE BridgeArray::hIL2CPP = NULL;
HMODULE BridgeArray::hMono = NULL;
#pragma endregion