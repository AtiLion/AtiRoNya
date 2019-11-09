#pragma once

#include "InternalHelpers.hpp"
#include <Unknwn.h>

#define INETDomain_GUID "F20A83EB-FB00-454B-9D88-132F7EC693D7"

struct __declspec(uuid(INETDomain_GUID)) INetDomain;

struct INetDomain : IUnknown
{
	virtual HRESULT __stdcall LoadAssembly(const char* assembly) = 0;
	virtual HRESULT __stdcall LoadAssemblyAndExecute(const char* assembly) = 0;
	virtual HRESULT __stdcall LoadMods(const char* path) = 0;
};