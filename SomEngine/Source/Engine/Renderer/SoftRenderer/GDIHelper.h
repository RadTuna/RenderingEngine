// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

// SomWorks :D // GDI : Graphics Device Interface

#pragma once

#include "Engine/Engine.h"

class GDIHelper
{
public:

	GDIHelper() = default;
	~GDIHelper() = default;

	void InitGDI(HWND hWnd);
	void ReleaseGDI(HWND hWnd);

	void SetColor(BYTE r, BYTE g, BYTE b);
	void Clear();
	void BufferSwap();

private:

	ULONG currentColor;
	BYTE* pBits;
	HDC	hScreenDC, hMemoryDC;
	HBITMAP hDefaultBitmap, hDIBitmap;

public:

	inline BYTE* GetpBits() const { return pBits; }
	inline ULONG GetCurrentColor() const { return currentColor; }

};