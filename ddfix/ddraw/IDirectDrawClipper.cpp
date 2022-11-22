﻿/**
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

HRESULT m_IDirectDrawClipper::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{
	if ((riid == IID_IDirectDrawClipper || riid == CLSID_DirectDrawClipper || riid == IID_IUnknown) && ppvObj)
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

ULONG m_IDirectDrawClipper::AddRef()
{
	return ++Refs;
}

ULONG m_IDirectDrawClipper::Release()
{
	ULONG x = --Refs;

	if (x == 0)
	{
		delete this;
	}

	return x;
}

HRESULT m_IDirectDrawClipper::GetClipList(LPRECT a, LPRGNDATA b, LPDWORD c)
{
	return ProxyInterface->GetClipList(a, b, c);
}

HRESULT m_IDirectDrawClipper::GetHWnd(HWND FAR * a)
{
	*a = Hwnd;
	return DD_OK;
}

HRESULT m_IDirectDrawClipper::Initialize(LPDIRECTDRAW a, DWORD b)
{
	if (a)
	{
		a = static_cast<m_IDirectDraw *>(a)->GetProxyInterface();
	}

	return ProxyInterface->Initialize(a, b);
}

HRESULT m_IDirectDrawClipper::IsClipListChanged(BOOL FAR * a)
{
	return ProxyInterface->IsClipListChanged(a);
}

HRESULT m_IDirectDrawClipper::SetClipList(LPRGNDATA a, DWORD b)
{
	return ProxyInterface->SetClipList(a, b);
}

HRESULT m_IDirectDrawClipper::SetHWnd(DWORD a, HWND b)
{
	Hwnd = b;
	return DD_OK;
}
