
#include "Draw2DManager.h"
#include "Engine/SoftRenderer/GDIHelper.h"
#include "Engine/SoftRenderer/SoftRenderer.h"
#include "Engine/Math/RenderMath.h"
#include "Engine/SoftRenderer/TriangleClass.h"


#define GetEndLoc(expr) ((expr) ? abs(startLoc.X - endLoc.X) : abs(startLoc.Y - endLoc.Y))
#define CheckZero(expr, num) ((expr) ? num + 1 : num)

Draw2DManager::Draw2DManager()
{
	mGDIHelper = nullptr;
	mSoftRenderer = nullptr;
	mTriangleList = nullptr;
}

Draw2DManager::~Draw2DManager()
{
	if (mTriangleList != nullptr)
	{
		delete[] mTriangleList;
		mTriangleList = nullptr;
	}
}

bool Draw2DManager::Initialize(SoftRenderer* initSoftRenderer, GDIHelper* initGDIHelper)
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

	return true;
}

void Draw2DManager::DrawLine(Vector2 startLoc, Vector2 endLoc, ColorRGB rgb, bool useAntiAliase)
{
	mGDIHelper->SetColor(rgb);

	const Matrix2x2 overTilt = { 0, 1, 1, 0 };
	const Matrix2x2 inverseX = { -1, 0, 0, 1 };
	const Matrix2x2 inverseY = { 1, 0, 0, -1 };

	int width = startLoc.X - endLoc.X;
	int height = startLoc.Y - endLoc.Y;
	int yCoord = 0;
	int inclination = (width == 0) ? 100 : abs(height / width);

	for (int x = 0; x <= GetEndLoc(inclination < 1) - 1; ++x)
	{
		float UpWeight = 0.0f;

		if (inclination < 1)
		{
			if (useAntiAliase == true)
			{
				GetYLocationf(abs(width), abs(height), x, &yCoord, &UpWeight);
			}
			else
			{
				GetYLocation(abs(width), abs(height), x, &yCoord);
			}
		}
		else // 기울기 1 초과
		{
			if (useAntiAliase == true)
			{
				std::swap(startLoc.X, startLoc.Y);
				GetYLocationf(abs(height), abs(width), x, &yCoord, &UpWeight);
				std::swap(startLoc.X, startLoc.Y);
			}
			else
			{
				std::swap(startLoc.X, startLoc.Y);
				GetYLocation(abs(height), abs(width), x, &yCoord);
				std::swap(startLoc.X, startLoc.Y);
			}
		}

		Vector2 tempLoc = { x, yCoord };

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
				mSoftRenderer->PutPixel(tempLoc.X, tempLoc.Y);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * UpWeight));
				mSoftRenderer->PutPixel(tempLoc.X + 1, tempLoc.Y);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor));
			}
			else
			{
				ULONG currentColor = mGDIHelper->GetCurrentColor();
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * (1.0f - UpWeight)));
				mSoftRenderer->PutPixel(tempLoc.X, tempLoc.Y);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * UpWeight));
				mSoftRenderer->PutPixel(tempLoc.X, tempLoc.Y + 1);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor));
			}
		}
		else
		{
			mSoftRenderer->PutPixel(tempLoc.X, tempLoc.Y);
		}
	}

	return;
}

void Draw2DManager::GetYLocation(int width, int height, int inX, int* outY)
{
	// 정수 연산을 사용하는 기존의 수식 (안티 앨리어싱이 힘듬)
	if (width * (*outY) + -height * inX > 0)
	{
		return;
	}

	(*outY)++;
	return;
}

void Draw2DManager::GetYLocationf(int width, int height, int inX, int* outY, float* upWeight)
{
	// 부동소수점 연산을 사용하는 새로운 수식 (안티 앨리어싱 쉬움, 퍼포먼스 떨어짐)
	float inclination = static_cast<float>(height) / static_cast<float>(width);

	float downWeight = inclination * inX - *outY;
	*upWeight = (*outY + 1) - inclination * inX;

	if (*upWeight > downWeight)
	{
		return;
	}

	(*outY)++;
	return;
}

bool Draw2DManager::SetTriangle(TriangleClass* vertices, int vertexCount)
{

	mTriangleList = new class TriangleClass[vertexCount];
	if (mTriangleList == nullptr)
	{
		return false;
	}

	mVertexCount = vertexCount;

	for (int i = 0; i < mVertexCount; ++i)
	{
		mTriangleList[i] = vertices[i];
	}

	return true;
}

void Draw2DManager::ClearTriangle()
{
	if (mTriangleList != nullptr)
	{
		delete[] mTriangleList;
		mTriangleList = nullptr;
	}

	return;
}

void Draw2DManager::DrawTriangleList()
{
	// 현재 버텍스 카운트를 초기화.
	mCurrentVertexCount = 0;

	for (int i = 0; i < mVertexCount; ++i)
	{
		DrawTriangle(mTriangleList[i]);
		mCurrentVertexCount++;
	}
}

void Draw2DManager::DrawTriangle(TriangleClass vertices)
{

	// 버텍스를 Y값 순으로 정렬함.
	RenderMath::SortVecticesByY(&vertices);

	if (vertices.point2.position.Y == vertices.point3.position.Y)
	{
		DrawBottomTriangle(vertices.point1, vertices.point2, vertices.point3);
	}
	else if (vertices.point1.position.Y == vertices.point2.position.Y)
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
	if (point2.position.Y != point3.position.Y)
	{
		return;
	}

	float inclinationL = (point2.position.X - point1.position.X) / (point2.position.Y - point1.position.Y);
	float inclinationR = (point3.position.X - point1.position.X) / (point3.position.Y - point1.position.Y);

	float StartPosX = point1.position.X;
	float EndPosX = point1.position.X;

	for (int ScanLineY = point1.position.Y; ScanLineY >= point2.position.Y; --ScanLineY)
	{
		Vertex TempVertex1;
		Vertex TempVertex2;

		TempVertex1.position = RenderMath::Vector2Set(StartPosX, ScanLineY);
		TempVertex2.position = RenderMath::Vector2Set(EndPosX, ScanLineY);

		DrawFlatLine(TempVertex1, TempVertex2);

		StartPosX -= inclinationL;
		EndPosX -= inclinationR;
	}

	return;
}

void Draw2DManager::DrawTopTriangle(Vertex point1, Vertex point2, Vertex point3)
{
	if (point1.position.Y != point2.position.Y)
	{
		return;
	}

	float inclinationL = (point3.position.X - point1.position.X) / (point3.position.Y - point1.position.Y);
	float inclinationR = (point3.position.X - point2.position.X) / (point3.position.Y - point2.position.Y);

	float StartPosX = point3.position.X;
	float EndPosX = point3.position.X;

	for (int ScanLineY = point3.position.Y; ScanLineY <= point1.position.Y; ++ScanLineY)
	{
		Vertex TempVertex1;
		Vertex TempVertex2;

		TempVertex1.position = RenderMath::Vector2Set(StartPosX, ScanLineY);
		TempVertex2.position = RenderMath::Vector2Set(EndPosX, ScanLineY);

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

	for (int i = point1.position.X; i <= point2.position.X; ++i)
	{
		Vector2 currentPoint = { i, point1.position.Y };

		Vector3 vertexWeight = mTriangleList[mCurrentVertexCount].GetVertexWeight(currentPoint);
		ColorRGB currentColor = 
			mTriangleList[mCurrentVertexCount].point1.Color * vertexWeight.X +
			mTriangleList[mCurrentVertexCount].point2.Color * vertexWeight.Y +
			mTriangleList[mCurrentVertexCount].point3.Color * vertexWeight.Z;

		mGDIHelper->SetColor(currentColor);

		mSoftRenderer->PutPixel(i, point1.position.Y);
	}

}
