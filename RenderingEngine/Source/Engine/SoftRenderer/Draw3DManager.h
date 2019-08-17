#pragma once

#include "Engine/Engine.h"


class Draw3DManager
{
public:

	Draw3DManager();
	~Draw3DManager();

	bool Initialize(class SoftRenderer* initSoftRenderer, class GDIHelper* initGDIHelper, const char* filename);
	void Release();
	void DrawLine(struct Vector3& startLoc, struct Vector3& endLoc, struct ColorRGBA& rgb, bool useAntiAliase);
	bool GenerateObject(struct Triangle* vertices, int vertexCount);
	void ClearObject();
	void DrawObject(const struct Matrix4x4& viewMatrix, const struct Matrix4x4& projectionMatrix);
	void DrawMesh(struct Triangle* triangleList, int verticesCount);
	void ProcessVertexShader(struct Triangle vertices);
	void TriangleRasterize(struct Triangle2D vertices);

private:

	void GetYLocation(float width, float height, float inX, float* outY);
	void GetYLocationf(float width, float height, float inX, float* outY, float* UpWeight);
	void RasterizeTopTriangle(struct Vertex2D& point1, struct Vertex2D& point2, struct Vertex2D& point3);
	void RasterizeBottomTriangle(struct Vertex2D& point1, struct Vertex2D& point2, struct Vertex2D& point3);
	void DrawFlatLine(struct Vertex2D& point1, struct Vertex2D& point2);
	void SortVecticesByY(struct Triangle2D* Vertices);
	void InitializeZBuffer();

private:

	class SoftRenderer* mSoftRenderer;
	class GDIHelper* mGDIHelper;
	class Object* mObjectList;
	class TextureHelper* mTextureHelper;
	struct Matrix4x4* mTransformMatrix;
	struct Triangle2D* mCurrentTriangle2D;
	float* mZDepthBuffer;
	int mObjectCapacity;
	int mCurrentObjectIndex;
	bool useTexture;

public:

	inline Object* GetMeshList() const { return mObjectList; }

};
