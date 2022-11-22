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

#include "dinput.h"

HRESULT m_IDirectInput2W::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	if ((riid == IID_IDirectInput2W || riid == IID_IUnknown) && ppvObj)
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

ULONG m_IDirectInput2W::AddRef()
{
	return ProxyInterface->AddRef();
}

ULONG m_IDirectInput2W::Release()
{
	ULONG x = ProxyInterface->Release();

	if (x == 0)
	{
		delete this;
	}

	return x;
}

HRESULT m_IDirectInput2W::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICEW *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	HRESULT hr = ProxyInterface->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpDirectInputDevice = ProxyAddressLookupTable.FindAddress<m_IDirectInputDeviceW>(*lplpDirectInputDevice);
	}

	return hr;
}

HRESULT m_IDirectInput2W::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKW lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return ProxyInterface->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT m_IDirectInput2W::GetDeviceStatus(REFGUID rguidInstance)
{
	return ProxyInterface->GetDeviceStatus(rguidInstance);
}

HRESULT m_IDirectInput2W::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return ProxyInterface->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT m_IDirectInput2W::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return ProxyInterface->Initialize(hinst, dwVersion);
}

HRESULT m_IDirectInput2W::FindDevice(REFGUID rguidClass, LPCWSTR ptszName, LPGUID pguidInstance)
{
	return ProxyInterface->FindDevice(rguidClass, ptszName, pguidInstance);
}
