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

namespace NDINPUT8
{
#undef __DINPUT_INCLUDED__
#undef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#undef DIRECTINPUT_VERSION
}

HRESULT WINAPI MyDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	return NDINPUT8::DirectInput8Create(hinst, dwVersion, IID_IDirectInput8A, ppvOut, punkOuter);
}

HRESULT m_IDirectInput7A::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	if ((riid == IID_IDirectInput7A || riid == IID_IUnknown) && ppvObj)
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

ULONG m_IDirectInput7A::AddRef()
{
	return ProxyInterface->AddRef();
}

ULONG m_IDirectInput7A::Release()
{
	ULONG x = ProxyInterface->Release();

	if (x == 0)
	{
		delete this;
	}

	return x;
}

HRESULT m_IDirectInput7A::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICEA *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	NDINPUT8::LPDIRECTINPUTDEVICE8A dinputDevice8;
	HRESULT hr = ProxyInterface->CreateDevice(rguid, &dinputDevice8, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpDirectInputDevice = ProxyAddressLookupTable.FindAddress<m_IDirectInputDeviceA>(dinputDevice8);
	}

	return hr;
}

HRESULT m_IDirectInput7A::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return ProxyInterface->EnumDevices(dwDevType, reinterpret_cast<NDINPUT8::LPDIENUMDEVICESCALLBACKA>(lpCallback), pvRef, dwFlags);
}

HRESULT m_IDirectInput7A::GetDeviceStatus(REFGUID rguidInstance)
{
	return ProxyInterface->GetDeviceStatus(rguidInstance);
}

HRESULT m_IDirectInput7A::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return ProxyInterface->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT m_IDirectInput7A::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return ProxyInterface->Initialize(hinst, dwVersion);
}

HRESULT m_IDirectInput7A::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
	return ProxyInterface->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT m_IDirectInput7A::CreateDeviceEx(REFGUID rguid, REFIID riid, LPVOID * ppvObj, LPUNKNOWN pUnkOuter)
{
	NDINPUT8::LPDIRECTINPUTDEVICE8A dinputDevice8;
	HRESULT hr = ProxyInterface->CreateDevice(rguid, &dinputDevice8, pUnkOuter);
	*ppvObj = dinputDevice8;

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj);
	}

	return hr;
}
