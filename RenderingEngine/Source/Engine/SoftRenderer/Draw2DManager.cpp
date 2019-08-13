
#include "Draw2DManager.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/Mesh.h"
#include "Engine/SoftRenderer/TextureHelper.h"


#define GetEndLoc(expr) ((expr) ? abs(startLoc.X - endLoc.X) : abs(startLoc.Y - endLoc.Y))
#define CheckZero(expr, num) ((expr) ? num + 1 : num)

Draw2DManager::Draw2DManager()
{
	mGDIHelper = nullptr;
	mSoftRenderer = nullptr;
	mTextureHelper = nullptr;
	useTexture = false;
	mMeshCapacity = 5;
	mCurrentMeshIndex = 0;
}

Draw2DManager::~Draw2DManager()
{
	if (mMeshList != nullptr)
	{
		delete[] mMeshList;
		mMeshList = nullptr;
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

bool Draw2DManager::Initialize(SoftRenderer* initSoftRenderer, GDIHelper* initGDIHelper, const char* filename)
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

	mTransformMatrix = new struct Matrix3x3;
	if (mTransformMatrix == nullptr)
	{
		return false;
	}

	mMeshList = new class Mesh[mMeshCapacity];
	if (mMeshList == nullptr)
	{
		return false;
	}

	useTexture = mTextureHelper->Initialize(filename);

	return true;
}

void Draw2DManager::Release()
{
	if (mMeshList != nullptr)
	{
		delete[] mMeshList;
		mMeshList = nullptr;
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

void Draw2DManager::DrawLine(Vector3& startLoc, Vector3& endLoc, ColorRGB& rgb, bool useAntiAliase)
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

void Draw2DManager::GetYLocation(float width, float height, float inX, float* outY)
{
	// 정수 연산을 사용하는 기존의 수식 (안티 앨리어싱이 힘듬)
	if (width * (*outY) + -height * inX > 0)
	{
		return;
	}

	(*outY)++;
	return;
}

void Draw2DManager::GetYLocationf(float width, float height, float inX, float* outY, float* upWeight)
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

void Draw2DManager::TransformTriangle(Triangle& vertices)
{
	RenderMath::MatrixMul(&vertices.point1.position, *mTransformMatrix);
	RenderMath::MatrixMul(&vertices.point2.position, *mTransformMatrix);
	RenderMath::MatrixMul(&vertices.point3.position, *mTransformMatrix);
}

bool Draw2DManager::GenerateMesh(struct Triangle* vertices, int vertexCount)
{
	bool Result;

	Result = mMeshList[mCurrentMeshIndex].Initialize(vertices, vertexCount);
	if (Result == false)
	{
		return false;
	}

	mCurrentMeshIndex++;

	return true;
}

void Draw2DManager::ClearMesh()
{
	mMeshList[mCurrentMeshIndex].Release();

	mCurrentMeshIndex--;
}

void Draw2DManager::DrawMesh(const Matrix3x3& viewMatrix)
{
	for (int i = 0; i < mCurrentMeshIndex; ++i)
	{
		*mTransformMatrix = RenderMath::GetTransformMatrix3x3(mMeshList[i].GetLocation(), mMeshList[i].GetRotation(), mMeshList[i].GetScale());
		RenderMath::MatrixMul(mTransformMatrix, viewMatrix);
		DrawTriangleList(mMeshList[i].GetTriangleList(), mMeshList[i].GetVerticesCount());
	}
}

void Draw2DManager::DrawTriangleList(Triangle* triangleList, int verticesCount)
{
	for (int i = 0; i < verticesCount; ++i)
	{
		DrawTriangle(triangleList[i]);
	}
}

void Draw2DManager::DrawTriangle(Triangle vertices)
{
	mCurrentTriangle = &vertices;

	TransformTriangle(vertices);

	// 버텍스를 Y값 순으로 정렬함.
	RenderMath::SortVecticesByY(&vertices);

	vertices.Initialize();

	if (RenderMath::IsNearestFloat(vertices.point2.position.Y, vertices.point3.position.Y))
	{
		DrawBottomTriangle(vertices.point1, vertices.point2, vertices.point3);
	}
	else if (RenderMath::IsNearestFloat(vertices.point1.position.Y, vertices.point2.position.Y))
	{
		DrawTopTriangle(vertices.point1, vertices.point2, vertices.point3);
	}
	else
	{
		Vertex NewVertex;
		NewVertex.position.Y = vertices.point2.position.Y;
		NewVertex.position.X = (vertices.point1.position.X + ((vertices.point2.position.Y - vertices.point1.position.Y) /
			(vertices.point3.position.Y - vertices.point1.position.Y)) * (vertices.point3.position.X - vertices.point1.position.X));
		DrawBottomTriangle(vertices.point1, vertices.point2, NewVertex);
		DrawTopTriangle(vertices.point2, NewVertex, vertices.point3);
	}


}

void Draw2DManager::DrawBottomTriangle(Vertex point1, Vertex point2, Vertex point3)
{
	if (!RenderMath::IsNearestFloat(point2.position.Y, point3.position.Y))
	{
		return;
	}

	float inclinationL = (point2.position.X - point1.position.X) / (point2.position.Y - point1.position.Y);
	float inclinationR = (point3.position.X - point1.position.X) / (point3.position.Y - point1.position.Y);

	float StartPosX = point1.position.X;
	float EndPosX = point1.position.X;

	for (int ScanLineY = (int)point1.position.Y; ScanLineY >= point2.position.Y; --ScanLineY)
	{
		Vertex TempVertex1;
		Vertex TempVertex2;

		TempVertex1.position = RenderMath::Vector3Set(StartPosX, ScanLineY, 1.0f);
		TempVertex2.position = RenderMath::Vector3Set(EndPosX, ScanLineY, 1.0f);

		DrawFlatLine(TempVertex1, TempVertex2);

		StartPosX -= inclinationL;
		EndPosX -= inclinationR;
	}

	return;
}

void Draw2DManager::DrawTopTriangle(Vertex point1, Vertex point2, Vertex point3)
{
	if (!RenderMath::IsNearestFloat(point1.position.Y, point2.position.Y))
	{
		return;
	}

	float inclinationL = (point3.position.X - point1.position.X) / (point3.position.Y - point1.position.Y);
	float inclinationR = (point3.position.X - point2.position.X) / (point3.position.Y - point2.position.Y);

	float StartPosX = point3.position.X;
	float EndPosX = point3.position.X;

	for (int ScanLineY = (int)point3.position.Y; ScanLineY <= point1.position.Y; ++ScanLineY)
	{
		Vertex TempVertex1;
		Vertex TempVertex2;

		TempVertex1.position = RenderMath::Vector3Set(StartPosX, ScanLineY, 1.0f);
		TempVertex2.position = RenderMath::Vector3Set(EndPosX, ScanLineY, 1.0f);

		DrawFlatLine(TempVertex1, TempVertex2);

		StartPosX += inclinationL;
		EndPosX += inclinationR;
	}

	return;
}

void Draw2DManager::DrawFlatLine(Vertex point1, Vertex point2)
{
	if (point1.position.Y != point2.position.Y)
	{
		return;
	}
	
	for (int i = (int)RenderMath::GetMin(point1.position.X, point2.position.X); i <= RenderMath::GetMax(point1.position.X, point2.position.X); ++i)
	{
		if (useTexture == true)
		{
			Vector3 currentPoint = RenderMath::Vector3Set(i, point1.position.Y, 1.0f);

			Vector3 vertexWeight = mCurrentTriangle->GetVertexWeight(currentPoint);

			Vector2 currentUV = 
				mCurrentTriangle->point1.UV * vertexWeight.X +
				mCurrentTriangle->point2.UV * vertexWeight.Y +
				mCurrentTriangle->point3.UV * vertexWeight.Z;
			ColorRGB currentColor = mTextureHelper->GetPixelUV(currentUV);

			mGDIHelper->SetColor(currentColor);

			mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(i, point1.position.Y));
		}
		else
		{
			Vector3 currentPoint = RenderMath::Vector3Set(i, point1.position.Y, 1.0f);

			Vector3 vertexWeight = mCurrentTriangle->GetVertexWeight(currentPoint);
			ColorRGB currentColor =
				mCurrentTriangle->point1.Color * vertexWeight.X +
				mCurrentTriangle->point2.Color * vertexWeight.Y +
				mCurrentTriangle->point3.Color * vertexWeight.Z;

			mGDIHelper->SetColor(currentColor);

			mSoftRenderer->PutPixel(RenderMath::IntFloat2toIntPoint2D(i, point1.position.Y));
		}
	}

}
