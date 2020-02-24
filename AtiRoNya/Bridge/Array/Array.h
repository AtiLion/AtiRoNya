#pragma once

#include "../Bridge.h"

#pragma region Array
DO_API(uintptr_t, (*mono_array_length_t), (MonoArray* arr));

DO_API(char*, (*mono_array_addr_with_size_t), (MonoArray* array, int size, uintptr_t idx));

class BridgeArray {
public:
	static void Initialize(HMODULE hIL2CPP, HMODULE hMono);

	static mono_array_length_t mono_array_length;
	
	static mono_array_addr_with_size_t mono_array_addr_with_size;
private:
	static HMODULE hIL2CPP;
	static HMODULE hMono;
};
#pragma endregion

#define mono_array_addr(array,type,index) ((type*)BridgeArray::mono_array_addr_with_size ((array), sizeof (type), (index)))
#define mono_array_get(array,type,index) ( *(type*)mono_array_addr ((array), type, (index)) ) 