#include "MonoExternals.h"

#include "../InternalHelpers.hpp"

#pragma region Internal Calls
static char* atironya_addrof(MonoObject* obj) {
	return (char*)obj;
}
static MonoObject* atironya_valueof(char* obj) {
	return (MonoObject*)obj;
}
static void* atironya_get_il2cpp_domain() {
	return AtiRoNya::pIL2CPPDomain;
}
static void* atironya_get_mono_domain() {
	return AtiRoNya::pMonoDomain;
}
#pragma endregion

void InitExternals() {
	BridgeMono::mono_add_internal_call("AtiRoNyaSDK.NativeSDK::atironya_get_il2cpp_domain", atironya_get_il2cpp_domain);
	BridgeMono::mono_add_internal_call("AtiRoNyaSDK.NativeSDK::atironya_get_mono_domain", atironya_get_mono_domain);
	BridgeMono::mono_add_internal_call("AtiRoNyaSDK.NativeSDK::atironya_addrof", atironya_addrof);
	BridgeMono::mono_add_internal_call("AtiRoNyaSDK.NativeSDK::atironya_valueof", atironya_valueof);
}