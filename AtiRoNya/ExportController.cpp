#include "Exports.h"
#include "InternalHelpers.hpp"
#include "VRCLoader.h"

IL2CPPDomain* atironya_get_domain() {
	return VRCLoader::mdIL2CPPDomain;
}

IL2CPPImage* atironya_get_assembly(const char* name) {
	if (!VRCLoader::mdIL2CPPDomain)
		return NULL;
	IL2CPPAssembly* assembly = il2cpp_domain_assembly_open(VRCLoader::mdIL2CPPDomain, name);

	if (!assembly)
		return NULL;
	return il2cpp_assembly_get_image(assembly);
}

IL2CPPArray* atironya_box_array(void** _array, IL2CPPClass* type, size_t objectSize, int length) {
	if (!_array)
		return NULL;
	IL2CPPArray* buffer = il2cpp_array_new(type, length);

	for (int i = 0; i < length; i++)
		il2cpp_array_set(buffer, objectSize, i, (char*)_array[i]);
	return buffer;
}
void** atironya_unbox_array(IL2CPPArray* _array, size_t objectSize) {
	if (!_array)
		return NULL;
	void** buffer = new void* [_array->max_length];

	for (int i = 0; i < _array->max_length; i++)
		buffer[i] = il2cpp_array_get(_array, objectSize, i);
	return buffer;
}

void atironya_wait_for_game(void(__stdcall* callback)()) {
	VRCLoader::qOnGameLoad.push(callback);
}

IL2CPPMethodPointer atironya_override(IL2CPPMethod* method, IL2CPPMethodPointer newMethod) {
	IL2CPPMethodPointer original = method->methodPointer;

	method->methodPointer = newMethod;
	return original;
}