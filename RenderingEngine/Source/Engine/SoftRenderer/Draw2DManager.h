#pragma once

#include "Engine/Engine.h"


class Draw2DManager
{
public:

	Draw2DManager();
	~Draw2DManager();

	bool Initialize(class SoftRenderer* initSoftRenderer, class GDIHelper* initGDIHelper);
	void DrawLine(struct Vector2 startLoc, struct Vector2 endLoc, struct ColorRGB rgb, bool useAntiAlise);
	bool SetTriangle(class TriangleClass* vertices, int vertexCount);
	void ClearTriangle();
	void DrawTriangleList();
	void DrawTriangle(class TriangleClass vertices);

private:

	void GetYLocation(int width, int height, int inX, int* outY);
	void GetYLocationf(int width, int height, int inX, int* outY, float* UpWeight);
	void DrawTopTriangle(struct Vertex point1, struct Vertex point2, struct Vertex point3);
	void DrawBottomTriangle(struct Vertex point1, struct Vertex point2, struct Vertex point3);
	void DrawFlatLine(struct Vertex point1, struct Vertex point2);

private:

	class SoftRenderer* mSoftRenderer;
	class GDIHelper* mGDIHelper;
	class TriangleClass* mTriangleList;
	int mVertexCount;
	int mCurrentVertexCount;

};
