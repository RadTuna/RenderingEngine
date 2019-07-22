
#include "SoftRenderer.h"
#include "Engine/Math/MatrixHelpers.h"
#include "Engine/Renderer/SoftRenderer/GDIHelper.h"


#define GetEndLoc(expr) ((expr) ? abs(startLoc.X - endLoc.X) : abs(startLoc.Y - endLoc.Y))
#define CheckZero(expr, num) ((expr) ? num + 1 : num)

SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
}

void SoftRenderer::Initialize(GDIHelper* initGDIHelper)
{
	if (initGDIHelper == nullptr)
	{
		return;
	}

	mGDIHelper = initGDIHelper;

	return;
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
	Vector2D secPoints[3];
	TriangleVertices vertices;

	points[0] = { 0, 100 };
	points[1] = { 100, -100 };
	points[2] = { -100, -100 };

	vertices.FirstVertex = points[0];
	vertices.SecondVertex = points[1];
	vertices.ThirdVertex = points[2];

	secPoints[0] = { 0, 150 };
	secPoints[1] = { 135, -120 };
	secPoints[2] = { -135, -120 };

	// Buffer Clear
	mGDIHelper->SetColor(255, 255, 255);
	mGDIHelper->Clear();

	// DrawLine
	mGDIHelper->SetColor(255, 0, 0);
	DrawLine(secPoints[0], secPoints[1], false);
	DrawLine(secPoints[1], secPoints[2], false);
	DrawLine(secPoints[2], secPoints[0], false);

	// DrawTriangle
	DrawTriangle(vertices);

	// Buffer Swap 
	mGDIHelper->BufferSwap();

	return;
}

// 안티 앨리어싱은 색상 문제가 있음 GDI를 수정하고 나서 사용을 권장함.
void SoftRenderer::DrawLine(Vector2D startLoc, Vector2D endLoc, bool UseAntialiase)
{
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
			if (UseAntialiase == true)
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
			if (UseAntialiase == true)
			{
				IntSwap(&startLoc.X, &startLoc.Y);
				GetYLocationf(abs(height), abs(width), x, &yCoord, &UpWeight);
				IntSwap(&startLoc.X, &startLoc.Y);
			}
			else
			{
				IntSwap(&startLoc.X, &startLoc.Y);
				GetYLocation(abs(height), abs(width), x, &yCoord);
				IntSwap(&startLoc.X, &startLoc.Y);
			}
		}

		Vector2D tempLoc = { x, yCoord };

		if (inclination >= 1) // 기울기 1 초과
		{
			MatrixHelpers::MatrixMul(&tempLoc, overTilt);

			if (width > 0) // x 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, inverseX);
			}

			if (height > 0) // y 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, inverseY);
			}
		}
		else
		{
			if (width > 0) // x 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, inverseX);
			}

			if (height > 0) // y 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, inverseY);
			}
		}

		tempLoc.X += startLoc.X;
		tempLoc.Y += startLoc.Y;

		if (UseAntialiase == true)
		{
			if (inclination >= 1) // 기울기 1 초과
			{
				ULONG currentColor = mGDIHelper->GetCurrentColor();
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * (1.0f - UpWeight)));
				PutPixel(tempLoc.X, tempLoc.Y);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * UpWeight));
				PutPixel(tempLoc.X + 1, tempLoc.Y);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor));
			}
			else
			{
				ULONG currentColor = mGDIHelper->GetCurrentColor();
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * (1.0f - UpWeight)));
				PutPixel(tempLoc.X, tempLoc.Y);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor * UpWeight));
				PutPixel(tempLoc.X, tempLoc.Y + 1);
				mGDIHelper->SetColor(static_cast<ULONG>(currentColor));
			}
		}
		else
		{
			PutPixel(tempLoc.X, tempLoc.Y);
		}
	}

	return;
}

void SoftRenderer::DrawTriangle(Vector2D vertex1, Vector2D vertex2, Vector2D vertex3)
{
	Vector2D maxVertex = { max(vertex1.X, max(vertex2.X, vertex3.X)), max(vertex1.Y, max(vertex2.Y, vertex3.Y)) };
	Vector2D minVertex = { min(vertex1.X, min(vertex2.X, vertex3.X)), min(vertex1.Y, min(vertex2.Y, vertex3.Y)) };

	for (int x = minVertex.X; x <= maxVertex.X; ++x)
	{
		for (int y = minVertex.Y; y <= maxVertex.X; ++y)
		{
			Vector2D CurrentLocation = { x, y };
			if (IsInTriangle(vertex1, vertex2, vertex3, CurrentLocation))
			{
				PutPixel(x, y);
			}
		}
	}

	return;
}

void SoftRenderer::DrawTriangle(TriangleVertices vertices)
{
	DrawTriangle(vertices.FirstVertex, vertices.SecondVertex, vertices.ThirdVertex);

	return;
}

void SoftRenderer::GetYLocation(int width, int height, int inX, int* outY)
{
	// 정수 연산을 사용하는 기존의 수식 (안티 앨리어싱이 힘듬)
	if (width * (*outY) + -height * inX > 0)
	{
		return;
	}

	(*outY)++;
	return;
}

void SoftRenderer::GetYLocationf(int width, int height, int inX, int* outY, float* upWeight)
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

bool SoftRenderer::IsInTriangle(Vector2D vertex1, Vector2D vertex2, Vector2D vertex3, Vector2D currentLocation)
{
	bool expr1 = ((vertex1.X - vertex2.X) * currentLocation.Y - (vertex1.Y - vertex2.Y) * currentLocation.X - (vertex1.X - vertex2.X) * vertex1.Y + (vertex1.Y - vertex2.Y) * vertex1.X > 0);
	bool expr2 = ((vertex2.X - vertex3.X) * currentLocation.Y - (vertex2.Y - vertex3.Y) * currentLocation.X - (vertex2.X - vertex3.X) * vertex2.Y + (vertex2.Y - vertex3.Y) * vertex2.X > 0);
	bool expr3 = ((vertex3.X - vertex1.X) * currentLocation.Y - (vertex3.Y - vertex1.Y) * currentLocation.X - (vertex3.X - vertex1.X) * vertex3.Y + (vertex3.Y - vertex1.Y) * vertex3.X > 0);

	if (expr1 && expr2 && expr3)
	{
		return true;
	}
	
	return false;
}

void SoftRenderer::IntSwap(int* valueA, int* valueB)
{
	int temp = *valueA;
	*valueA = *valueB;
	*valueB = temp;

	return;
}


