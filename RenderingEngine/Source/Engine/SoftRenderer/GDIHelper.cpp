
#include "GDIHelper.h"
#include "Engine/Math/RenderMath.h"


void GDIHelper::BufferSwap()
{
	BitBlt(hScreenDC, 0, 0, ScreenWidth, ScreenHeight, hMemoryDC, 0, 0, SRCCOPY);
}

void GDIHelper::SetColor(BYTE r, BYTE g, BYTE b)
{
	currentColor = RGB(b, g, r);
}

void GDIHelper::SetColor(struct ColorRGBA rgb)
{
	currentColor = RGB(rgb.blue, rgb.green, rgb.red);
}

void GDIHelper::SetColor(ULONG color)
{
	currentColor = color;
}

ColorRGBA GDIHelper::GetPixelColor(int x, int y)
{
	ColorRGBA temp;

	x += ScreenWidth / 2;
	y += ScreenHeight / 2;

	int destCoord = (ScreenWidth * ScreenHeight) - (ScreenWidth * y - x);

	ULONG* colorField = reinterpret_cast<ULONG*>(pBits);

	temp.red = GetBValue(colorField[destCoord]);
	temp.green = GetGValue(colorField[destCoord]);
	temp.blue = GetRValue(colorField[destCoord]);
	temp.alpha = 255;

	return temp;
}

void GDIHelper::Clear()
{
	ULONG* dest = (ULONG*)pBits;
	DWORD bytecount = ScreenWidth * ScreenHeight * sizeof(ULONG);
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
	bmi.bmiHeader.biWidth = ScreenWidth;
	bmi.bmiHeader.biHeight = -ScreenHeight;
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
