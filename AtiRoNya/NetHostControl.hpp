#pragma once

#include "InternalHelpers.hpp"
#include "INetDomain.h"
#include <metahost.h>

class NetHostControl : IHostControl {
public:
	NetHostControl() {
		lRefCount = 0;
		indDefaultAppDomain = NULL;
	}
	virtual ~NetHostControl() {
		if (indDefaultAppDomain)
			indDefaultAppDomain->Release();
	}

	HRESULT __stdcall GetHostManager(REFIID id, void** ppHostManager) {
		*ppHostManager = NULL;
		return E_NOINTERFACE;
	}
	HRESULT __stdcall SetAppDomainManager(DWORD dwAppDomainID, IUnknown* pUnkAppDomainManager) {
		return pUnkAppDomainManager->QueryInterface(__uuidof(INetDomain), (PVOID*)&indDefaultAppDomain);
	}

	INetDomain* GetINetDomain() {
		if (indDefaultAppDomain)
			indDefaultAppDomain->AddRef();
		return indDefaultAppDomain;
	}
	HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) {
		if (!ppv) return E_POINTER;

		*ppv = this;
		AddRef();
		return S_OK;
	}

	ULONG __stdcall AddRef() {
		return InterlockedIncrement(&lRefCount);
	}
	ULONG __stdcall Release() {
		if (InterlockedDecrement(&lRefCount) == 0) {
			delete this;
			return 0;
		}
		return lRefCount;
	}

private:
	long lRefCount;
	INetDomain* indDefaultAppDomain;
};