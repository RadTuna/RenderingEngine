
#include "SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/Draw2DManager.h"
#include "Engine/SoftRenderer/ShapeClass.h"


SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
	mDraw2DManager = nullptr;
}

bool SoftRenderer::Initialize(GDIHelper* initGDIHelper)
{
	bool Result;
	//Triangle* vertices;
	Quad* vertices;

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

	Result = mDraw2DManager->Initialize(this, mGDIHelper, "../RenderingEngine/Source/Engine/Resource/stone.bmp");
	if (Result == false)
	{
		return false;
	}

	/*
	// 트라이앵글리스트를 DrawManager에 등록
	int vertexCount = 2;

	vertices = new Triangle[vertexCount];
	if (vertices == nullptr)
	{
		return false;
	}

	vertices[0].point1.position = RenderMath::Vector2Set(0, 100);
	vertices[0].point1.Color = RenderMath::ColorRGBSet(0, 0, 255);
	vertices[0].point1.UV = RenderMath::Vector2Set(0.5f, 0.0f);

	vertices[0].point2.position = RenderMath::Vector2Set(-100, -100);
	vertices[0].point2.Color = RenderMath::ColorRGBSet(0, 255, 0);
	vertices[0].point2.UV = RenderMath::Vector2Set(0.0f, 1.0f);

	vertices[0].point3.position = RenderMath::Vector2Set(100, -100);
	vertices[0].point3.Color = RenderMath::ColorRGBSet(255, 0, 0);
	vertices[0].point3.UV = RenderMath::Vector2Set(1.0f, 1.0f);

	Result = mDraw2DManager->SetTriangle(vertices, vertexCount);
	if (Result == false)
	{
		return false;
	}
	*/

	int vertexCount = 2;

	vertices = new Quad[vertexCount / 2];
	if (vertices == nullptr)
	{
		return false;
	}

	Vertex quadVertices[4];
	quadVertices[0].position = RenderMath::Vector2Set(-100, 100);
	quadVertices[0].Color = RenderMath::ColorRGBSet(255, 0, 0);
	quadVertices[0].UV = RenderMath::Vector2Set(0.0f, 0.0f);

	quadVertices[1].position = RenderMath::Vector2Set(100, 100);
	quadVertices[1].Color = RenderMath::ColorRGBSet(255, 0, 0);
	quadVertices[1].UV = RenderMath::Vector2Set(1.0f, 0.0f);

	quadVertices[2].position = RenderMath::Vector2Set(100, -100);
	quadVertices[2].Color = RenderMath::ColorRGBSet(255, 0, 0);
	quadVertices[2].UV = RenderMath::Vector2Set(1.0f, 1.0f);

	quadVertices[3].position = RenderMath::Vector2Set(-100, -100);
	quadVertices[3].Color = RenderMath::ColorRGBSet(255, 0, 0);
	quadVertices[3].UV = RenderMath::Vector2Set(0.0f, 1.0f);

	vertices[0].SetQuad(quadVertices[0], quadVertices[1], quadVertices[2], quadVertices[3]);

	Result = mDraw2DManager->SetQuad(vertices, vertexCount);
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

void SoftRenderer::PutPixel(IntPoint2D inPoint)
{
	PutPixel(inPoint.X, inPoint.Y);
}

void SoftRenderer::UpdateFrame()
{
	Vector2 points[4];
	ColorRGB Color;

	points[0] = RenderMath::Vector2Set(-225, 110);
	points[1] = RenderMath::Vector2Set(225, 110);
	points[2] = RenderMath::Vector2Set(-115, -110);
	points[3] = RenderMath::Vector2Set(115, -110);

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


