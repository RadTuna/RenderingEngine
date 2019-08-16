#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"


struct Vertex
{
	Vector4 position;
	ColorRGBA Color;
	Vector2 UV;
};

struct Triangle
{
	Vertex point1;
	Vertex point2;
	Vertex point3;
};

struct Vertex2D
{
	Vector2 position;
	ColorRGBA Color;
	Vector2 UV;
};

struct Triangle2D
{

	Vertex2D point1;
	Vertex2D point2;
	Vertex2D point3;

public:

	void Initialize();
	Vector3 GetVertexWeight(Vector2& inPoint);

private:

	Vector2 mVectorU;
	Vector2 mVectorV;
	Vector2 mVectorW;
	float mWeightDenominator;
	float mDotUV;
	float mDotUU;
	float mDotVV;

};

class Object
{
public:

	Object();
	~Object();

	bool Initialize(Triangle* triangleList, int verticesCount);
	void Release();
	void SetLocation(const Vector4& location);
	void SetRotation(const float rotation);
	void SetScale(const Vector4& scale);
	void SetTransform(const Vector4& location, const float rotation, const Vector4& scale);
	void DeepCopy(Object* target);

private:

	Triangle* mMesh;
	int mVerticesCount;
	Vector4 mLocation;
	float mRotation;
	Vector4 mScale;

public:

	inline Vector4 GetLocation() const { return mLocation; }
	inline float GetRotation() const { return mRotation; }
	inline Vector4 GetScale() const { return mScale; }
	inline Triangle* GetTriangleList() const { return mMesh; }
	inline int GetVerticesCount() const { return mVerticesCount; }

};

