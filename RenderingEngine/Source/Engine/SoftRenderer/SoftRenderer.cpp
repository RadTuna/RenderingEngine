
#include "SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/Draw2DManager.h"
#include "Engine/SoftRenderer/ShapeClass.h"


SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
	mDraw2DManager = nullptr;
	mhWnd = nullptr;
}

bool SoftRenderer::Initialize(GDIHelper* initGDIHelper, HWND* hWnd)
{
	bool Result;
	Triangle* vertices;

	if (initGDIHelper == nullptr)
	{
		return false;
	}

	mGDIHelper = initGDIHelper;

	if (hWnd == nullptr)
	{
		return false;
	}

	mhWnd = hWnd;


	mDraw2DManager = new class Draw2DManager;
	if (mDraw2DManager == nullptr)
	{
		return false;
	}

	Result = mDraw2DManager->Initialize(this, mGDIHelper, "../RenderingEngine/Source/Engine/Resource/stone.bmp");
	if (Result == false)
	{
		return false;
	}
	
	// 트라이앵글리스트를 DrawManager에 등록
	int vertexCount = 1;

	vertices = new Triangle[vertexCount];
	if (vertices == nullptr)
	{
		return false;
	}

	vertices[0].point1.position = RenderMath::Vector3Set(0, 100, 1);
	vertices[0].point1.Color = RenderMath::ColorRGBSet(255, 0, 0);
	vertices[0].point1.UV = RenderMath::Vector2Set(0.5f, 0.0f);

	vertices[0].point2.position = RenderMath::Vector3Set(-100, -100, 1);
	vertices[0].point2.Color = RenderMath::ColorRGBSet(0, 255, 0);
	vertices[0].point2.UV = RenderMath::Vector2Set(0.0f, 1.0f);

	vertices[0].point3.position = RenderMath::Vector3Set(100, -100, 1);
	vertices[0].point3.Color = RenderMath::ColorRGBSet(0, 0, 255);
	vertices[0].point3.UV = RenderMath::Vector2Set(1.0f, 1.0f);

	Result = mDraw2DManager->SetTriangle(vertices, vertexCount);
	if (Result == false)
	{
		return false;
	}

	Vector3 location = RenderMath::Vector3Set(0.0f, 5.0f, 0.0f);
	float rotation = 0.1f;
	Vector3 scale = RenderMath::Vector3Set(1.0f, 1.0f, 0.0f);
	Matrix3x3 transformMatrix = RenderMath::GetTransformMatrix3x3(location, rotation, scale);

	mDraw2DManager->SetTransformMatrix(transformMatrix);
	
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

void SoftRenderer::PutPixel(IntPoint2D inPoint)
{
	PutPixel(inPoint.X, inPoint.Y);
}

void SoftRenderer::UpdateFrame()
{
	Vector3 points[4];
	Matrix3x3 transformMatrix;
	Vector3 location;
	Vector3 scale;
	float rotation;
	ColorRGB Color;

	points[0] = RenderMath::Vector3Set(-225, 110, 1);
	points[1] = RenderMath::Vector3Set(225, 110, 1);
	points[2] = RenderMath::Vector3Set(-115, -110, 1);
	points[3] = RenderMath::Vector3Set(115, -110, 1);

	// Buffer Clear
	mGDIHelper->SetColor(255, 255, 255);
	mGDIHelper->Clear();

	// Set DrawColor
	Color.SetRGB(255, 0, 0);

	// DrawLine
	mDraw2DManager->DrawLine(points[0], points[1], Color, false);
	mDraw2DManager->DrawLine(points[1], points[3], Color, false);
	mDraw2DManager->DrawLine(points[2], points[3], Color, false);
	mDraw2DManager->DrawLine(points[2], points[0], Color, false);

	// DrawTriangle
	mDraw2DManager->DrawTriangleList();

	// Buffer Swap 
	mGDIHelper->BufferSwap();

	return;
}


