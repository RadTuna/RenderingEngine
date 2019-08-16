#pragma once

#include "Engine/Engine.h"


class SoftRenderer
{
public:

	SoftRenderer();
	~SoftRenderer();

	bool Initialize(class GDIHelper* initGDIHelper, HWND* hWnd);
	void Release();
	void UpdateFrame(float deltaTime);
	bool IsInRange(int x, int y);
	void PutPixel(int x, int y);
	void PutPixel(struct IntPoint2D inPoint);

private:

	bool SetRenderParameter();

private:

	class GDIHelper* mGDIHelper;
	class Draw3DManager* mDraw2DManager;
	class ViewCamera* mViewCamera;
	HWND* mhWnd;

};
