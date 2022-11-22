/**
* Copyright (C) 2017 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "ddraw.h"

HRESULT m_IDirect3D2::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	if ((riid == IID_IDirect3D2 || riid == IID_IUnknown) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj);
	}

	return hr;
}

ULONG m_IDirect3D2::AddRef()
{
	return ProxyInterface->AddRef();
}

ULONG m_IDirect3D2::Release()
{
	ULONG x = ProxyInterface->Release();

	if (x == 0)
	{
		delete this;
	}

	return x;
}

HRESULT m_IDirect3D2::EnumDevices(LPD3DENUMDEVICESCALLBACK a, LPVOID b)
{
	return ProxyInterface->EnumDevices(a, b);
}

HRESULT m_IDirect3D2::CreateLight(LPDIRECT3DLIGHT * a, IUnknown * b)
{
	HRESULT hr = ProxyInterface->CreateLight(a, b);

	if (SUCCEEDED(hr))
	{
		*a = ProxyAddressLookupTable.FindAddress<m_IDirect3DLight>(*a);
	}

	return hr;
}

HRESULT m_IDirect3D2::CreateMaterial(LPDIRECT3DMATERIAL2 * a, IUnknown * b)
{
	HRESULT hr = ProxyInterface->CreateMaterial(a, b);

	if (SUCCEEDED(hr))
	{
		*a = ProxyAddressLookupTable.FindAddress<m_IDirect3DMaterial2>(*a);
	}

	return hr;
}

HRESULT m_IDirect3D2::CreateViewport(LPDIRECT3DVIEWPORT2 * a, IUnknown * b)
{
	HRESULT hr = ProxyInterface->CreateViewport(a, b);

	if (SUCCEEDED(hr))
	{
		*a = ProxyAddressLookupTable.FindAddress<m_IDirect3DViewport2>(*a);
	}

	return hr;
}

HRESULT m_IDirect3D2::FindDevice(LPD3DFINDDEVICESEARCH a, LPD3DFINDDEVICERESULT b)
{
	return ProxyInterface->FindDevice(a, b);
}

HRESULT m_IDirect3D2::CreateDevice(REFCLSID a, LPDIRECTDRAWSURFACE b, LPDIRECT3DDEVICE2 * c)
{
	if (b)
	{
		b = static_cast<m_IDirectDrawSurface *>(b)->GetProxyInterface();
	}

	HRESULT hr = ProxyInterface->CreateDevice(a, b, c);

	if (SUCCEEDED(hr))
	{
		*c = ProxyAddressLookupTable.FindAddress<m_IDirect3DDevice2>(*c);
	}

	return hr;
}
