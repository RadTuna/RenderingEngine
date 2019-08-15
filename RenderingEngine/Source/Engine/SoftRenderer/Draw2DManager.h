#pragma once

#include "Engine/Engine.h"


class Draw2DManager
{
public:

	Draw2DManager();
	~Draw2DManager();

	bool Initialize(class SoftRenderer* initSoftRenderer, class GDIHelper* initGDIHelper, const char* filename);
	void Release();
	void DrawLine(struct Vector3& startLoc, struct Vector3& endLoc, struct ColorRGBA& rgb, bool useAntiAliase);
	bool GenerateMesh(struct Triangle* vertices, int vertexCount);
	void ClearMesh();
	void DrawMesh(const struct Matrix3x3& viewMatrix);
	void DrawTriangleList(struct Triangle* triangleList, int verticesCount);
	void DrawTriangle(struct Triangle vertices);

private:

	void GetYLocation(float width, float height, float inX, float* outY);
	void GetYLocationf(float width, float height, float inX, float* outY, float* UpWeight);
	void DrawTopTriangle(struct Vertex point1, struct Vertex point2, struct Vertex point3);
	void DrawBottomTriangle(struct Vertex point1, struct Vertex point2, struct Vertex point3);
	void DrawFlatLine(struct Vertex point1, struct Vertex point2);
	void TransformTriangle(struct Triangle& vertices);

private:

	class SoftRenderer* mSoftRenderer;
	class GDIHelper* mGDIHelper;
	class Object* mObjectList;
	class TextureHelper* mTextureHelper;
	struct Matrix3x3* mTransformMatrix;
	struct Triangle* mCurrentTriangle;
	int mObjectCapacity;
	int mCurrentObjectIndex;
	bool useTexture;

public:

	inline Object* GetMeshList() const { return mObjectList; }

};
