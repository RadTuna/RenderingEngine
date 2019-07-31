#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"


struct Vertex
{
	Vector2 position;
	ColorRGB Color;
};

class TriangleClass
{
public:

	TriangleClass();
	~TriangleClass();

	Vector3 GetVertexWeight(Vector2& inPoint);

public:

	Vertex point1;
	Vertex point2;
	Vertex point3;

};

