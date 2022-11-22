﻿#pragma once

class m_IDirect3D3 : public IDirect3D3, public AddressLookupTableObject
{
private:
	IDirect3D3 *ProxyInterface;
	ULONG Refs;
	std::shared_ptr<WrapperLookupTable<void>> WrapperAddressLookupTable;
public:
	m_IDirect3D3(IDirect3D3 *aOriginal, std::shared_ptr<WrapperLookupTable<void>> wrapperAddressLookupTable)
		: ProxyInterface(aOriginal)
		, Refs(1)
		, WrapperAddressLookupTable(wrapperAddressLookupTable)
	{
		ProxyAddressLookupTable.SaveAddress(this, ProxyInterface);
		WrapperAddressLookupTable->SaveWrapper(this, IID_IDirect3D3);
	}
	~m_IDirect3D3()
	{
		ProxyAddressLookupTable.DeleteAddress(this);
		WrapperAddressLookupTable->DeleteWrapper(IID_IDirect3D3);
	}

	IDirect3D3 *GetProxyInterface() { return ProxyInterface; }

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3D3 methods ***/
	STDMETHOD(EnumDevices)(THIS_ LPD3DENUMDEVICESCALLBACK, LPVOID);
	STDMETHOD(CreateLight)(THIS_ LPDIRECT3DLIGHT*, LPUNKNOWN);
	STDMETHOD(CreateMaterial)(THIS_ LPDIRECT3DMATERIAL3*, LPUNKNOWN);
	STDMETHOD(CreateViewport)(THIS_ LPDIRECT3DVIEWPORT3*, LPUNKNOWN);
	STDMETHOD(FindDevice)(THIS_ LPD3DFINDDEVICESEARCH, LPD3DFINDDEVICERESULT);
	STDMETHOD(CreateDevice)(THIS_ REFCLSID, LPDIRECTDRAWSURFACE4, LPDIRECT3DDEVICE3*, LPUNKNOWN);
	STDMETHOD(CreateVertexBuffer)(THIS_ LPD3DVERTEXBUFFERDESC, LPDIRECT3DVERTEXBUFFER*, DWORD, LPUNKNOWN);
	STDMETHOD(EnumZBufferFormats)(THIS_ REFCLSID, LPD3DENUMPIXELFORMATSCALLBACK, LPVOID);
	STDMETHOD(EvictManagedTextures)(THIS);
};
