// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "Win32Application.h"

// #include "SomRender_SR.h"
// #include "SomRender_DX11.h"
// #include "SomRender_DX12.h"

// SomWorks :D // WINAPI or APIENTRY
_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	Win32Application* winApp = new Win32Application;
	if (winApp == nullptr)
	{
		return 0;
	}

	winApp->Run(hInstance, nCmdShow);

	delete winApp;
	winApp = nullptr;

	return 0;
}