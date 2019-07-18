
#include "SoftRenderer.h"
#include "Engine/Math/MatrixHelpers.h"
#include "Engine/Renderer/SoftRenderer/GDIHelper.h"


#define GetEndLoc(expr) ((expr) ? abs(startLoc.X - endLoc.X) : abs(startLoc.Y - endLoc.Y))
#define CheckZero(expr, num) ((expr) ? num + 1 : num)

SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
}

void SoftRenderer::Initialize(GDIHelper* InitGDIHelper)
{
	if (InitGDIHelper == nullptr)
	{
		return;
	}

	mGDIHelper = InitGDIHelper;

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
	Vector2D Points[3];
	Vector2D SecPoints[3];

	Points[0] = { 0, 100 };
	Points[1] = { 100, -100 };
	Points[2] = { -100, -100 };

	SecPoints[0] = { 0, 150 };
	SecPoints[1] = { 135, -120 };
	SecPoints[2] = { -135, -120 };

	// Buffer Clear
	mGDIHelper->SetColor(32, 128, 255);
	mGDIHelper->Clear();

	// DrawLine
	mGDIHelper->SetColor(255, 0, 0);
	DrawLine(SecPoints[0], SecPoints[1]);
	DrawLine(SecPoints[1], SecPoints[2]);
	DrawLine(SecPoints[2], SecPoints[0]);

	// DrawTriangle
	DrawTriangle(Points[0], Points[1], Points[2]);

	// Buffer Swap 
	mGDIHelper->BufferSwap();

	return;
}

void SoftRenderer::DrawLine(Vector2D startLoc, Vector2D endLoc)
{
	const Matrix2x2 OverTilt = { 0, 1, 1, 0 };
	const Matrix2x2 InverseX = { -1, 0, 0, 1 };
	const Matrix2x2 InverseY = { 1, 0, 0, -1 };

	int width = startLoc.X - endLoc.X;
	int height = startLoc.Y - endLoc.Y;
	int yCoord = 0;

	width = CheckZero(width == 0, width);
	height = CheckZero(height == 0, height);

	for (int x = 0; x <= GetEndLoc(abs(height / width) < 1); ++x)
	{
		if (abs(height / width) < 1)
		{
			GetYLocation(abs(width), abs(height), x, &yCoord);
		}
		else
		{
			IntSwap(&startLoc.X, &startLoc.Y);
			GetYLocation(abs(height), abs(width), x, &yCoord);
			IntSwap(&startLoc.X, &startLoc.Y);
		}

		Vector2D tempLoc = { x, yCoord };

		if (abs(height / width) >= 1) // 기울기 1 초과
		{
			MatrixHelpers::MatrixMul(&tempLoc, OverTilt);

			if (width > 0) // x 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, InverseX);
			}

			if (height > 0) // y 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, InverseY);
			}
		}
		else
		{
			if (height > 0) // x 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, InverseX);
			}

			if (width > 0) // y 반전
			{
				MatrixHelpers::MatrixMul(&tempLoc, InverseY);
			}
		}

		tempLoc.X += startLoc.X;
		tempLoc.Y += startLoc.Y;

		PutPixel(tempLoc.X, tempLoc.Y);
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

void SoftRenderer::GetYLocation(int width, int height, int inX, int* outY)
{
	if (width * (*outY) + -height * inX > 0)
	{
		return;
	}

	(*outY)++;
	return;
}

bool SoftRenderer::IsInTriangle(Vector2D vertex1, Vector2D vertex2, Vector2D vertex3, Vector2D currentLocation)
{
	bool expr1 = (currentLocation.X * (vertex1.Y - vertex2.Y) + currentLocation.Y * (vertex2.X - vertex1.X) + vertex1.X * vertex2.Y - vertex2.X * vertex1.Y < 0);
	bool expr2 = (currentLocation.X * (vertex2.Y - vertex3.Y) + currentLocation.Y * (vertex3.X - vertex2.X) + vertex2.X * vertex3.Y - vertex3.X * vertex2.Y > 0);
	bool expr3 = (currentLocation.X * (vertex3.Y - vertex1.Y) + currentLocation.Y * (vertex1.X - vertex3.X) + vertex3.X * vertex1.Y - vertex1.X * vertex3.Y < 0);

	//expr1 = true;
	//expr2 = true;
	//expr3 = false;

	Vector2D Line1 = MatrixHelpers::VectorSub(vertex2, vertex1);
	Vector2D Line2 = MatrixHelpers::VectorSub(vertex3, vertex2);
	Vector2D Line3 = MatrixHelpers::VectorSub(vertex1, vertex3);


	if (Line1.X < 0)
	{
		expr1 = !expr1;
	}
	if (Line2.X < 0)
	{
		expr2 = !expr2;
	}
	if (Line3.X < 0)
	{
		expr3 = !expr3;
	}

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


