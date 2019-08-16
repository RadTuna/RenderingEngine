
#include "SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/Draw3DManager.h"
#include "Engine/SoftRenderer/Object.h"
#include "Engine/SoftRenderer/ViewCamera.h"


SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
	mDraw2DManager = nullptr;
	mhWnd = nullptr;
}

SoftRenderer::~SoftRenderer()
{
	if (mViewCamera != nullptr)
	{
		mViewCamera->Release();
		delete mViewCamera;
		mViewCamera = nullptr;
	}

	if (mDraw2DManager != nullptr)
	{
		mDraw2DManager->Release();
		delete mDraw2DManager;
		mDraw2DManager = nullptr;
	}
}

bool SoftRenderer::Initialize(GDIHelper* initGDIHelper, HWND* hWnd)
{
	bool Result;

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


	mDraw2DManager = new class Draw3DManager;
	if (mDraw2DManager == nullptr)
	{
		return false;
	}

	Result = mDraw2DManager->Initialize(this, mGDIHelper, "../RenderingEngine/Source/Engine/Resource/tuna.tga");
	if (Result == false)
	{
		return false;
	}

	mViewCamera = new class ViewCamera;
	if (mViewCamera == nullptr)
	{
		return false;
	}

	Result = mViewCamera->Initialize();
	if (Result == false)
	{
		return false;
	}

	Result = SetRenderParameter();
	if (Result == false)
	{
		return false;
	}

	return true;
}

void SoftRenderer::Release()
{
	if (mViewCamera != nullptr)
	{
		mViewCamera->Release();
		delete mViewCamera;
		mViewCamera = nullptr;
	}

	if (mDraw2DManager != nullptr)
	{
		mDraw2DManager->Release();
		delete mDraw2DManager;
		mDraw2DManager = nullptr;
	}
}

bool SoftRenderer::SetRenderParameter()
{
	bool Result;
	Triangle* vertices;

	// 2D Render 관련 파라미터 설정.

	// 카메라 위치, 회전을 설정.
	Vector3 cameraLocation = RenderMath::Vector3Set(0.0f, 0.0f, 0.0f);
	float cameraRotation = 0.0f;

	mViewCamera->SetLocation(cameraLocation);
	mViewCamera->SetRotation(cameraRotation);
	mViewCamera->CalculrateViewMatrix();


	// 트라이앵글리스트를 DrawManager에 등록
	int vertexCount = 2;

	vertices = new Triangle[vertexCount];
	if (vertices == nullptr)
	{
		return false;
	}

	vertices[0].point1.position = RenderMath::Vector3Set(-50, 50, 1);
	vertices[0].point1.Color = RenderMath::ColorRGBASet(255, 0, 0, 255);
	vertices[0].point1.UV = RenderMath::Vector2Set(0.0f, 0.0f);

	vertices[0].point2.position = RenderMath::Vector3Set(50, 50, 1);
	vertices[0].point2.Color = RenderMath::ColorRGBASet(0, 255, 0, 255);
	vertices[0].point2.UV = RenderMath::Vector2Set(1.0f, 0.0f);

	vertices[0].point3.position = RenderMath::Vector3Set(-50, -50, 1);
	vertices[0].point3.Color = RenderMath::ColorRGBASet(0, 0, 255, 255);
	vertices[0].point3.UV = RenderMath::Vector2Set(0.0f, 1.0f);

	vertices[1].point1.position = RenderMath::Vector3Set(50, 50, 1);
	vertices[1].point1.Color = RenderMath::ColorRGBASet(255, 0, 0, 255);
	vertices[1].point1.UV = RenderMath::Vector2Set(1.0f, 0.0f);

	vertices[1].point2.position = RenderMath::Vector3Set(50, -50, 1);
	vertices[1].point2.Color = RenderMath::ColorRGBASet(0, 255, 0, 255);
	vertices[1].point2.UV = RenderMath::Vector2Set(1.0f, 1.0f);

	vertices[1].point3.position = RenderMath::Vector3Set(-50, -50, 1);
	vertices[1].point3.Color = RenderMath::ColorRGBASet(0, 0, 255, 255);
	vertices[1].point3.UV = RenderMath::Vector2Set(0.0f, 1.0f);

	Result = mDraw2DManager->GenerateObject(vertices, vertexCount);
	if (Result == false)
	{
		return false;
	}

	mDraw2DManager->GetMeshList()[0].SetTransform(RenderMath::Vector3Set(0.0f, 0.0f, 0.0f), 0.0f, RenderMath::Vector3Set(1.0f, 1.0f, 0.0f));

	delete[] vertices;
	vertices = nullptr;

	return true;
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

void SoftRenderer::UpdateFrame(float deltaTime)
{
	Vector3 points[4];
	ColorRGBA Color;

	points[0] = RenderMath::Vector3Set(-100, 100, 1);
	points[1] = RenderMath::Vector3Set(100, 100, 1);
	points[2] = RenderMath::Vector3Set(-100, -100, 1);
	points[3] = RenderMath::Vector3Set(100, -100, 1);

	// Buffer Clear
	mGDIHelper->SetColor(0, 100, 150);
	mGDIHelper->Clear();

	// Set DrawColor
	Color.SetRGB(255, 0, 0, 255);

	// DrawLine
	mDraw2DManager->DrawLine(points[0], points[1], Color, false);
	mDraw2DManager->DrawLine(points[1], points[3], Color, false);
	mDraw2DManager->DrawLine(points[2], points[3], Color, false);
	mDraw2DManager->DrawLine(points[2], points[0], Color, false);

	// DrawTriangle
	mDraw2DManager->GetMeshList()[0].SetLocation(mDraw2DManager->GetMeshList()[0].GetLocation() + (RenderMath::Vector3Set(-30.0f, 0.0f, 0.0f) * deltaTime));
	mDraw2DManager->GetMeshList()[0].SetRotation(mDraw2DManager->GetMeshList()[0].GetRotation() + (100.0f * deltaTime));
	mDraw2DManager->DrawObject(mViewCamera->GetViewMatrix());

	// Buffer Swap 
	mGDIHelper->BufferSwap();

	return;
}


