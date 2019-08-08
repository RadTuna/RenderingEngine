#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"


struct Vertex
{
	Vector2 position;
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

	Vector3 GetVertexWeight(Vector2& inPoint);

private:

	Vector2 mVectorU;
	Vector2 mVectorV;
	Vector2 mVectorW;
	float mWeightDenominator;
	float mDotUV;
	float mDotUU;

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

