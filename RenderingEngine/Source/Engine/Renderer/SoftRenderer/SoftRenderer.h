#pragma once

#include "Engine/Engine.h"


class SoftRenderer
{
public:

	SoftRenderer();
	~SoftRenderer() = default;

	void Initialize(class GDIHelper* initGDIHelper);
	void UpdateFrame(void);
	bool IsInRange(int x, int y);
	void PutPixel(int x, int y);

	void DrawLine(struct Vector2D startLoc, struct Vector2D endLoc, bool UseAntiAliase);
	void DrawTriangle(struct Vector2D point1, struct Vector2D point2, struct Vector2D point3);
	void DrawTriangle(struct TriangleVertices vertices);

private:

	void GetYLocation(int width, int height, int inX, int* outY);
	void GetYLocationf(int width, int height, int inX, int* outY, float* UpWeight);
	bool IsInTriangle(struct Vector2D vertex1, struct Vector2D vertex2, struct Vector2D vertex3, struct Vector2D currentLocation);
	void IntSwap(int* valueA, int* valueB);

private:

	class GDIHelper* mGDIHelper;

};
