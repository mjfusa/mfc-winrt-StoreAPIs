
// MFCWithWinRT.h : main header file for the MFCWithWinRT application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCWithWinRTApp:
// See MFCWithWinRT.cpp for the implementation of this class
//
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Services.Store.h"
using namespace winrt;

class CMFCWithWinRTApp : public CWinApp
{
public:
	CMFCWithWinRTApp() noexcept;

	// Overrides
public:
	virtual BOOL InitInstance();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCWithWinRTApp theApp;
