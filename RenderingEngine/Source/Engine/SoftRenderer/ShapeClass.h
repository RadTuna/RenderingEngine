#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"


struct Vertex
{
	Vector3 position;
	ColorRGB Color;
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

struct Quad
{

	Triangle triangle1;
	Triangle triangle2;

public:

	void SetQuad(Vertex& point1, Vertex& point2, Vertex& point3, Vertex& point4);

};

class ShapeClass
{
public:

	ShapeClass();
	~ShapeClass() = default;

};

