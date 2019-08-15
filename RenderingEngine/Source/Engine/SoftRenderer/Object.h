#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"


struct Vertex
{
	Vector3 position;
	ColorRGBA Color;
	Vector2 UV;
};

struct Triangle
{

	Vertex point1;
	Vertex point2;
	Vertex point3;

public:

	void Initialize();

	Vector3 GetVertexWeight(Vector3& inPoint);

private:

	Vector3 mVectorU;
	Vector3 mVectorV;
	Vector3 mVectorW;
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
	void SetLocation(const Vector3& location);
	void SetRotation(const float rotation);
	void SetScale(const Vector3& scale);
	void SetTransform(const Vector3& location, const float rotation, const Vector3& scale);
	void DeepCopy(Object* target);

private:

	Triangle* mTriangleList;
	int mVerticesCount;
	Vector3 mLocation;
	float mRotation;
	Vector3 mScale;

public:

	inline Vector3 GetLocation() const { return mLocation; }
	inline float GetRotation() const { return mRotation; }
	inline Vector3 GetScale() const { return mScale; }
	inline Triangle* GetTriangleList() const { return mTriangleList; }
	inline int GetVerticesCount() const { return mVerticesCount; }

};

