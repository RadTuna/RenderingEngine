
#include "SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/Draw2DManager.h"
#include "Engine/SoftRenderer/TriangleClass.h"


SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
	mDraw2DManager = nullptr;
}

bool SoftRenderer::Initialize(GDIHelper* initGDIHelper)
{
	bool Result;
	TriangleClass* vertices;

	if (initGDIHelper == nullptr)
	{
		return false;
	}

	mGDIHelper = initGDIHelper;

	mDraw2DManager = new class Draw2DManager;
	if (mDraw2DManager == nullptr)
	{
		return false;
	}

	Result = mDraw2DManager->Initialize(this, mGDIHelper);
	if (Result == false)
	{
		return false;
	}

	// 트라이앵글리스트를 DrawManager에 등록
	int vertexCount = 3;

	vertices = new TriangleClass[vertexCount];
	if (vertices == nullptr)
	{
		return false;
	}

	vertices[0].point1.position = RenderMath::Vector2DSet(0, 100);
	vertices[0].point2.position = RenderMath::Vector2DSet(-100, -100);
	vertices[0].point3.position = RenderMath::Vector2DSet(100, -100);

	vertices[1].point1.position = RenderMath::Vector2DSet(-200, 100);
	vertices[1].point2.position = RenderMath::Vector2DSet(0, 100);
	vertices[1].point3.position = RenderMath::Vector2DSet(-100, -100);

	vertices[2].point1.position = RenderMath::Vector2DSet(0, 100);
	vertices[2].point2.position = RenderMath::Vector2DSet(200, 100);
	vertices[2].point3.position = RenderMath::Vector2DSet(100, -100);

	Result = mDraw2DManager->SetTriangle(vertices, vertexCount);
	if (Result == false)
	{
		return false;
	}

	// Manager에 등록이 끝났으므로 할당해제.
	delete[] vertices;
	vertices = nullptr;

	return true;
}

void SoftRenderer::Release()
{

}

bool SoftRenderer::IsInRange(int x, int y)
{
	return (abs(x) < (SomWidth / 2)) && (abs(y) < (SomHeight / 2));
}

void SoftRenderer::PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)mGDIHelper->GetpBits();
	DWORD offset = SomWidth * SomHeight / 2 + SomWidth / 2 + x + SomWidth * -y;
	*(dest + offset) = mGDIHelper->GetCurrentColor();

	return;
}

void SoftRenderer::UpdateFrame()
{
	Vector2D points[3];
	ColorRGB Color;

	points[0] = { 0, 150 };
	points[1] = { 135, -120 };
	points[2] = { -135, -120 };

	// Buffer Clear
	mGDIHelper->SetColor(255, 255, 255);
	mGDIHelper->Clear();

	// Set DrawColor
	Color.SetRGB(255, 0, 0);

	// DrawLine
	mDraw2DManager->DrawLine(points[0], points[1], Color, false);
	mDraw2DManager->DrawLine(points[1], points[2], Color, false);
	mDraw2DManager->DrawLine(points[2], points[0], Color, false);

	// DrawTriangle
	mDraw2DManager->DrawTriangleList(Color);

	// Buffer Swap 
	mGDIHelper->BufferSwap();

	return;
}


