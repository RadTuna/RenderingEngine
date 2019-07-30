// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "Win32Application.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/SoftRenderer.h"

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Win32Application::Win32Application()
{
	m_hInstance = nullptr;
	m_hwnd = nullptr;
	mGDIHelper = nullptr;
	mSoftRenderer = nullptr;
	bIsActive = false;
}

Win32Application::~Win32Application()
{
	if (mSoftRenderer != nullptr)
	{
		mSoftRenderer->Release();
		delete mSoftRenderer;
		mSoftRenderer = nullptr;
	}

	if (mGDIHelper != nullptr)
	{
		delete mGDIHelper;
		mGDIHelper = nullptr;
	}
}

// �������� �ʱ�ȭ �� ���η����� ���ÿ� ����մϴ�.
int Win32Application::Run(HINSTANCE hInstance, int nCmdShow)
{
	applicationHandle = this;

	m_hInstance = hInstance;

	// Parse the command line parameters
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	LocalFree(argv);

	// SomWorks :D // Initialize the window class. // â Ŭ������ ����մϴ�.
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = m_hInstance;
	windowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOMENGINE));
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_SOMENGINE);
	windowClass.lpszClassName = SomTitle;
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (RegisterClassEx(&windowClass) == 0) // 0�̸� Register�� �����Ͽ� Return
	{
		return 0;
	}

	
	// SomWorks :D // Instance Init // �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
	m_hInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	RECT windowRect = { 0, 0, static_cast<LONG>(SomWidth), static_cast<LONG>(SomHeight) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the window and store a handle to it.
	m_hwnd = CreateWindow(
		SomTitle,
		SomTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,        // We have no parent window.
		nullptr,        // We aren't using menus.
		m_hInstance,
		nullptr);

	if (m_hwnd == nullptr)
	{
		return 0;
	}

	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
	   
	// SomWorks :D // Main sample loop.
	MSG msg = {};

	mSoftRenderer = new SoftRenderer;
	if (mSoftRenderer == nullptr)
	{
		return 0;
	}

	mSoftRenderer->Initialize(mGDIHelper);
	

	while (msg.message != WM_QUIT)
	{
		// Process any messages in the queue.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (bIsActive)
		{
			// SomWorks :D // SoftRender ���� ������Ʈ
			mSoftRenderer->UpdateFrame();
		}
		else
		{
			WaitMessage();
		}
	}

	// Return this part of the WM_QUIT message to Windows.
	return static_cast<char>(msg.wParam);
}

// Main message handler for the sample.
LRESULT CALLBACK Win32Application::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_COMMAND: // ���� ���α׷� �޴��� ó���մϴ�.
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	// SomWorks :D // GDI Initialize
	case WM_CREATE:
	{
		mGDIHelper = new GDIHelper;
		if (mGDIHelper == nullptr)
		{
			return 0;
		}

		mGDIHelper->InitGDI(hWnd);
		bIsActive = true;
	}
	break;

	case WM_PAINT: // �� â�� �׸��ϴ�.
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY: // ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
		bIsActive = false;
		mGDIHelper->ReleaseGDI(hWnd);
		PostQuitMessage(0);

		delete mGDIHelper;
		mGDIHelper = nullptr;

		delete mSoftRenderer;
		mSoftRenderer = nullptr;

		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return applicationHandle->MessageHandler(hWnd, message, wParam, lParam);

}

// SomWorks :D // ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
