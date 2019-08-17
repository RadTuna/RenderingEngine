
#include "Draw3DManager.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/Object.h"
#include "Engine/SoftRenderer/TextureHelper.h"


#define GetEndLoc(expr) ((expr) ? abs(startLoc.X - endLoc.X) : abs(startLoc.Y - endLoc.Y))
#define CheckZero(expr, num) ((expr) ? num + 1 : num)

Draw3DManager::Draw3DManager()
{
	mGDIHelper = nullptr;
	mSoftRenderer = nullptr;
	mTextureHelper = nullptr;
	useTexture = false;
	mObjectCapacity = 5;
	mCurrentObjectIndex = 0;
}

Draw3DManager::~Draw3DManager()
{
	if (mZDepthBuffer != nullptr)
	{
		delete[] mZDepthBuffer;
		mZDepthBuffer = nullptr;
	}

	if (mObjectList != nullptr)
	{
		delete[] mObjectList;
		mObjectList = nullptr;
	}

	if (mTextureHelper != nullptr)
	{
		delete mTextureHelper;
		mTextureHelper = nullptr;
	}

	if (mTransformMatrix != nullptr)
	{
		delete mTransformMatrix;
		mTransformMatrix = nullptr;
	}
}

bool Draw3DManager::Initialize(SoftRenderer* initSoftRenderer, GDIHelper* initGDIHelper, const char* filename)
{
	if (initSoftRenderer == nullptr)
	{
		return false;
	}
	if (initGDIHelper == nullptr)
	{
		return false;
	}

	mSoftRenderer = initSoftRenderer;
	mGDIHelper = initGDIHelper;

	mTextureHelper = new class TextureHelper;
	if (mTextureHelper == nullptr)
	{
		return false;
	}

	mTransformMatrix = new struct Matrix4x4;
	if (mTransformMatrix == nullptr)
	{
		return false;
	}

	mObjectList = new class Object[mObjectCapacity];
	if (mObjectList == nullptr)
	{
		return false;
	}

	useTexture = mTextureHelper->Initialize(filename);

	mZDepthBuffer = new float[ScreenWidth * ScreenHeight];
	if (mZDepthBuffer == nullptr)
	{
		return false;
	}

	InitializeZBuffer();

	return true;
}

void Draw3DManager::Release()
{
	if (mZDepthBuffer != nullptr)
	{
		delete[] mZDepthBuffer;
		mZDepthBuffer = nullptr;
	}

	if (mObjectList != nullptr)
	{
		delete[] mObjectList;
		mObjectList = nullptr;
	}

	if (mTextureHelper != nullptr)
	{
		delete mTextureHelper;
		mTextureHelper = nullptr;
	}

	if (mTransformMatrix != nullptr)
	{
		delete mTransformMatrix;
		mTransformMatrix = nullptr;
	}
}

void Draw3DManager::DrawLine(Vector3& startLoc, Vector3& endLoc, ColorRGBA& rgb, bool useAntiAliase)
{
	mGDIHelper->SetColor(rgb);

	Matrix3x3 overTilt = { 0, 1, 0, 1, 0, 0, 0, 0, 1 };
	Matrix3x3 inverseX = { -1, 0, 0, 0, 1, 0, 0, 0, 1 };
	Matrix3x3 inverseY = { 1, 0, 0, 0, -1, 0, 0, 0, 1 };

	float width = startLoc.X - endLoc.X;
	float height = startLoc.Y - endLoc.Y;
	float yCoord = 0.0f;
	float inclination = (width == 0) ? 100.0f : abs(height / width);

	for (int x = 0; x <= GetEndLoc(inclination < 1); ++x)
	{
		float UpWeight = 0.0f;

		if (inclination < 1)
		{
			if (useAntiAliase == true)
			{
				GetYLocationf(abs(width), abs(height), (float)x, &yCoord, &UpWeight);
			}
			else
			{
				GetYLocation(abs(width), abs(height), (float)x, &yCoord);
			}
		}
		else // 기울기 1 초과
		{
			if (useAntiAliase == true)
			{
				std::swap(startLoc.X, startLoc.Y);
				GetYLocationf(abs(height), abs(width), (float)x, &yCoord, &UpWeight);
				std::swap(startLoc.X, startLoc.Y);
			}
			else
			{
				std::swap(startLoc.X, startLoc.Y);
				GetYLocation(abs(height), abs(width), (float)x, &yCoord);
				std::swap(startLoc.X, startLoc.Y);
			}
		}

		Vector3 tempLoc = RenderMath::Vector3Set(x, yCoord, 1.0f);

		if (inclination >= 1) // 기울기 1 초과
		{
			RenderMath::MatrixMul(&tempLoc, overTilt);

			if (width > 0) // x 반전
			{
				RenderMath::MatrixMul(&tempLoc, inverseX);
			}

			if (height > 0) // y 반전
			{
				RenderMath::MatrixMul(&tempLoc, inverseY);
			}
		}
		else
		{
			if (width > 0) // x 반전
			{
				RenderMath::MatrixMul(&tempLoc, inverseX);
			}

			if (height > 0) // y 반전
			{
				RenderMath::MatrixMul(&tempLoc, inverseY);
			}
		}

		tempLoc.X += startLoc.X;
		tempLoc.Y += startLoc.Y;

		if (useAntiAliase == true)
		{
			if (inclination >= 1) // 기울기 1 초과
			{
				ULONG currentColor = mGDIHelper->GetCurrentColor();
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * (1.0f - UpWeight)));
				mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(tempLoc.X, tempLoc.Y));
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * UpWeight));
				mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(tempLoc.X + 1.0f, tempLoc.Y));
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor));
			}
			else
			{
				ULONG currentColor = mGDIHelper->GetCurrentColor();
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * (1.0f - UpWeight)));
				mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(tempLoc.X, tempLoc.Y));
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * UpWeight));
				mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(tempLoc.X, tempLoc.Y + 1.0f));
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor));
			}
		}
		else
		{
			mSoftRenderer->PutPixel(RenderMath::Vector3toIntPoint2D(tempLoc));
		}
	}

	return;
}

void Draw3DManager::GetYLocation(float width, float height, float inX, float* outY)
{
	// 정수 연산을 사용하는 기존의 수식 (안티 앨리어싱이 힘듬)
	if (width * (*outY) + -height * inX > 0)
	{
		return;
	}

	(*outY)++;
	return;
}

void Draw3DManager::GetYLocationf(float width, float height, float inX, float* outY, float* upWeight)
{
	// 부동소수점 연산을 사용하는 새로운 수식 (안티 앨리어싱 쉬움, 퍼포먼스 떨어짐)
	float inclination = height / width;

	float downWeight = inclination * inX - *outY;
	*upWeight = (*outY + 1) - inclination * inX;

	if (*upWeight > downWeight)
	{
		return;
	}

	(*outY)++;
	return;
}

bool Draw3DManager::GenerateObject(struct Triangle* vertices, int vertexCount)
{
	bool Result;

	Result = mObjectList[mCurrentObjectIndex].Initialize(vertices, vertexCount);
	if (Result == false)
	{
		return false;
	}

	mCurrentObjectIndex++;

	// ObjectCapacity를 초과하면 2배로 용량을 늘림.
	if (mCurrentObjectIndex >= mObjectCapacity)
	{
		mObjectCapacity *= 2;
		Object* tempObjectList = new Object[mObjectCapacity];
		if (tempObjectList == nullptr)
		{
			return false;
		}

		mObjectList->DeepCopy(tempObjectList);

		if (mObjectList != nullptr)
		{
			mObjectList->Release();
			delete[] mObjectList;
			mObjectList = nullptr;
		}

		mObjectList = tempObjectList;
	}

	return true;
}

void Draw3DManager::ClearObject()
{
	mObjectList[mCurrentObjectIndex].Release();

	mCurrentObjectIndex--;
}

void Draw3DManager::DrawObject(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
	InitializeZBuffer();

	for (int i = 0; i < mCurrentObjectIndex; ++i)
	{
		*mTransformMatrix = RenderMath::GetTransformMatrix4x4(mObjectList[i].GetLocation(), mObjectList[i].GetRotation(), mObjectList[i].GetScale());
		RenderMath::MatrixMul(mTransformMatrix, viewMatrix);
		RenderMath::MatrixMul(mTransformMatrix, projectionMatrix);
		DrawMesh(mObjectList[i].GetTriangleList(), mObjectList[i].GetVerticesCount());
	}
}

void Draw3DManager::DrawMesh(Triangle* triangleList, int verticesCount)
{
	for (int i = 0; i < verticesCount; ++i)
	{
		ProcessVertexShader(triangleList[i]);
	}
}

void Draw3DManager::ProcessVertexShader(Triangle vertices)
{
	// TransformMatrix로 버텍스 위치 변경.
	RenderMath::MatrixMul(&vertices.point1.position, *mTransformMatrix);
	RenderMath::MatrixMul(&vertices.point2.position, *mTransformMatrix);
	RenderMath::MatrixMul(&vertices.point3.position, *mTransformMatrix);

	TriangleRasterize(vertices);
}

void Draw3DManager::TriangleRasterize(Triangle2D vertices)
{
	mCurrentTriangle2D = &vertices;

	// 버텍스를 Y값 순으로 정렬함.
	SortVecticesByY(&vertices);

	vertices.Initialize();

	if (RenderMath::IsNearlyFloat(vertices.point2.position.Y, vertices.point3.position.Y))
	{
		RasterizeBottomTriangle(vertices.point1, vertices.point2, vertices.point3);
	}
	else if (RenderMath::IsNearlyFloat(vertices.point1.position.Y, vertices.point2.position.Y))
	{
		RasterizeTopTriangle(vertices.point1, vertices.point2, vertices.point3);
	}
	else
	{
		Vertex2D NewVertex;
		NewVertex.position.Y = vertices.point2.position.Y;
		NewVertex.position.X = (vertices.point1.position.X + ((vertices.point2.position.Y - vertices.point1.position.Y) /
			(vertices.point3.position.Y - vertices.point1.position.Y)) * (vertices.point3.position.X - vertices.point1.position.X));
		RasterizeBottomTriangle(vertices.point1, vertices.point2, NewVertex);
		RasterizeTopTriangle(vertices.point2, NewVertex, vertices.point3);
	}
}

void Draw3DManager::RasterizeBottomTriangle(Vertex2D& point1, Vertex2D& point2, Vertex2D& point3)
{
	if (!RenderMath::IsNearlyFloat(point2.position.Y, point3.position.Y))
	{
		return;
	}

	float inclinationL = (point2.position.X - point1.position.X) / (point2.position.Y - point1.position.Y);
	float inclinationR = (point3.position.X - point1.position.X) / (point3.position.Y - point1.position.Y);

	float StartPosX = point1.position.X;
	float EndPosX = point1.position.X;

	for (int ScanLineY = (int)point1.position.Y; ScanLineY >= point2.position.Y; --ScanLineY)
	{
		Vertex2D TempVertex1;
		Vertex2D TempVertex2;

		TempVertex1.position = RenderMath::Vector3Set(StartPosX, ScanLineY, 1.0f);
		TempVertex2.position = RenderMath::Vector3Set(EndPosX, ScanLineY, 1.0f);

		DrawFlatLine(TempVertex1, TempVertex2);

		StartPosX -= inclinationL;
		EndPosX -= inclinationR;
	}

	return;
}

void Draw3DManager::RasterizeTopTriangle(Vertex2D& point1, Vertex2D& point2, Vertex2D& point3)
{
	if (!RenderMath::IsNearlyFloat(point1.position.Y, point2.position.Y))
	{
		return;
	}

	float inclinationL = (point3.position.X - point1.position.X) / (point3.position.Y - point1.position.Y);
	float inclinationR = (point3.position.X - point2.position.X) / (point3.position.Y - point2.position.Y);

	float StartPosX = point3.position.X;
	float EndPosX = point3.position.X;

	for (int ScanLineY = (int)point3.position.Y; ScanLineY <= point1.position.Y; ++ScanLineY)
	{
		Vertex2D TempVertex1;
		Vertex2D TempVertex2;

		TempVertex1.position = RenderMath::Vector3Set(StartPosX, ScanLineY, 1.0f);
		TempVertex2.position = RenderMath::Vector3Set(EndPosX, ScanLineY, 1.0f);

		DrawFlatLine(TempVertex1, TempVertex2);

		StartPosX += inclinationL;
		EndPosX += inclinationR;
	}

	return;
}

void Draw3DManager::DrawFlatLine(Vertex2D& point1, Vertex2D& point2)
{
	if (point1.position.Y != point2.position.Y)
	{
		return;
	}
	
	for (int i = (int)RenderMath::GetMin(point1.position.X, point2.position.X); i <= RenderMath::GetMax(point1.position.X, point2.position.X); ++i)
	{
		// 포인트가 화면을 벗어나면 그리지 않음.
		if (abs(i) >= ScreenWidth / 2 || abs(point1.position.Y) >= ScreenHeight / 2)
		{
			continue;
		}

		if (useTexture == true)
		{
			Vector2 currentPoint = RenderMath::Vector2Set(i, point1.position.Y);

			Vector3 vertexWeight = mCurrentTriangle2D->GetVertexWeight(currentPoint);

			float currentDepth = 
				mCurrentTriangle2D->point1.position.Z * vertexWeight.X +
				mCurrentTriangle2D->point2.position.Z * vertexWeight.Y +
				mCurrentTriangle2D->point3.position.Z * vertexWeight.Z;

			currentDepth = RenderMath::NormalizeFloat(currentDepth, CameraNear, CameraFar);

			if (mZDepthBuffer[ScreenWidth * ((int)currentPoint.Y + ScreenHeight / 2) + ((int)currentPoint.X + ScreenWidth / 2)] > currentDepth)
			{
				mZDepthBuffer[ScreenWidth * ((int)currentPoint.Y + ScreenHeight / 2) + ((int)currentPoint.X + ScreenWidth / 2)] = currentDepth;
			}
			else
			{
				continue;
			}

			Vector2 currentUV = 
				mCurrentTriangle2D->point1.UV * vertexWeight.X +
				mCurrentTriangle2D->point2.UV * vertexWeight.Y +
				mCurrentTriangle2D->point3.UV * vertexWeight.Z;
			ColorRGBA currentColor = mTextureHelper->GetPixelColor(currentUV);

			currentColor = currentColor * RenderMath::NormalizeFloat(currentColor.alpha, 0, 255) + (mGDIHelper->GetPixelColor(static_cast<int>(currentPoint.X), static_cast<int>(currentPoint.Y)) * (1.0f - RenderMath::NormalizeFloat(currentColor.alpha, 0, 255)));

			mGDIHelper->SetColor(currentColor);

			mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(currentPoint.X, currentPoint.Y));
		}
		else
		{
			Vector2 currentPoint = RenderMath::Vector2Set(i, point1.position.Y);

			Vector3 vertexWeight = mCurrentTriangle2D->GetVertexWeight(currentPoint);
			ColorRGBA currentColor =
				mCurrentTriangle2D->point1.Color * vertexWeight.X +
				mCurrentTriangle2D->point2.Color * vertexWeight.Y +
				mCurrentTriangle2D->point3.Color * vertexWeight.Z;

			mGDIHelper->SetColor(currentColor);

			mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(currentPoint.X, currentPoint.Y));
		}
	}
}

void Draw3DManager::SortVecticesByY(Triangle2D* vertices)
{
	if (!((vertices->point1.position.Y >= vertices->point2.position.Y) && (vertices->point1.position.Y >= vertices->point3.position.Y)))
	{
		if (vertices->point2.position.Y > vertices->point3.position.Y)
		{
			std::swap(vertices->point1, vertices->point2);
		}
		else
		{
			std::swap(vertices->point1, vertices->point3);
		}
	}

	if (vertices->point2.position.Y < vertices->point3.position.Y)
	{
		std::swap(vertices->point2, vertices->point3);
	}


	if (vertices->point1.position.Y == vertices->point2.position.Y)
	{
		if (vertices->point1.position.X > vertices->point1.position.X)
		{
			std::swap(vertices->point1, vertices->point2);
		}
	}

	if (vertices->point2.position.Y == vertices->point3.position.Y)
	{
		if (vertices->point2.position.X > vertices->point3.position.X)
		{
			std::swap(vertices->point2, vertices->point3);
		}
	}

	return;
}

void Draw3DManager::InitializeZBuffer()
{
	// ZBuffer의 초기화 실시.
	for (int i = 0; i < ScreenWidth * ScreenHeight; ++i)
	{
		mZDepthBuffer[i] = 1.0f;
	}
}
