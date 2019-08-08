#pragma once

#include "Engine/Engine.h"


class Draw2DManager
{
public:

	Draw2DManager();
	~Draw2DManager();

	bool Initialize(class SoftRenderer* initSoftRenderer, class GDIHelper* initGDIHelper, const char* filename);
	void DrawLine(struct Vector3& startLoc, struct Vector3& endLoc, struct ColorRGB& rgb, bool useAntiAlise);
	bool SetTriangle(struct Triangle* vertices, int vertexCount);
	void UpdateTriangle(struct Matrix3x3& transformMatrix);
	bool SetQuad(struct Quad* vertices, int vertexCount);
	void ClearTriangle();
	void DrawTriangleList();
	void DrawTriangle(struct Triangle& vertices);

private:

	void GetYLocation(float width, float height, float inX, float* outY);
	void GetYLocationf(float width, float height, float inX, float* outY, float* UpWeight);
	void DrawTopTriangle(struct Vertex point1, struct Vertex point2, struct Vertex point3);
	void DrawBottomTriangle(struct Vertex point1, struct Vertex point2, struct Vertex point3);
	void DrawFlatLine(struct Vertex point1, struct Vertex point2);

private:

	class SoftRenderer* mSoftRenderer;
	class GDIHelper* mGDIHelper;
	struct Triangle* mTriangleList;
	class TextureHelper* mTextureHelper;
	int mVerticesCount;
	int mCurrentVerticesCount;
	bool useTexture;

};
