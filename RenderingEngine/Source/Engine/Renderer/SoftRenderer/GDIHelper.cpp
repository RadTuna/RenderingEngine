
#include "GDIHelper.h"


void GDIHelper::BufferSwap()
{
	BitBlt(hScreenDC, 0, 0, SomWidth, SomHeight, hMemoryDC, 0, 0, SRCCOPY);
}

void GDIHelper::SetColor(BYTE r, BYTE g, BYTE b)
{
	currentColor = RGB(b, g, r);
}

void GDIHelper::SetColor(ULONG color)
{
	currentColor = color;
}

void GDIHelper::Clear()
{
	ULONG* dest = (ULONG*)pBits;
	DWORD bytecount = SomWidth * SomHeight * sizeof(ULONG);
	ULONG value = currentColor;
	bytecount /= 4;
	while (bytecount--)
	{
		*dest++ = value;
	}
	return;
}

void GDIHelper::InitGDI(HWND hWnd)
{
	hScreenDC = GetDC(hWnd);
	hMemoryDC = CreateCompatibleDC(hScreenDC);

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = SomWidth;
	bmi.bmiHeader.biHeight = -SomHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	hDIBitmap = CreateDIBSection(hMemoryDC, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	hDefaultBitmap = (HBITMAP)SelectObject(hMemoryDC, hDIBitmap);
}

void GDIHelper::ReleaseGDI(HWND hWnd)
{
	DeleteObject(hDefaultBitmap);
	DeleteObject(hDIBitmap);
	ReleaseDC(hWnd, hScreenDC);
	ReleaseDC(hWnd, hMemoryDC);
}
