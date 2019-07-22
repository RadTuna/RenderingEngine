// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "Engine/Engine.h"

class Win32Application
{
public:

	// SomWorks :D // WinAPI Setup
	int Run(HINSTANCE hInstance, int nCmdShow);

	// SomWorks :D // 초기화 성공 여부
	bool bIsActive;

	Win32Application();
	~Win32Application();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//private:
	
	HWND m_hwnd;
	HINSTANCE m_hInstance;
	class GDIHelper* mGDIHelper;
	class SoftRenderer* mSoftRenderer;

public:

	inline HWND GetHwnd() { return m_hwnd; }
	inline HINSTANCE GetHInstnace() { return m_hInstance; }

};


static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

static Win32Application* applicationHandle = nullptr;
