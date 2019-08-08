#pragma once

#include "Engine/Engine.h"


class SoftRenderer
{
public:

	SoftRenderer();
	~SoftRenderer() = default;

	bool Initialize(class GDIHelper* initGDIHelper, HWND* hWnd);
	void Release();
	void UpdateFrame(void);
	bool IsInRange(int x, int y);
	void PutPixel(int x, int y);
	void PutPixel(struct IntPoint2D inPoint);

private:

private:

	class GDIHelper* mGDIHelper;
	class Draw2DManager* mDraw2DManager;
	HWND* mhWnd;

};
