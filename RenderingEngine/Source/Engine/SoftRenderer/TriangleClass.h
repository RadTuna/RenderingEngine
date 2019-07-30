#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"


struct Vertex
{
	Vector2D position;
	Vector2D uv;
	Vector2D normal;
};

class TriangleClass
{
public:

	TriangleClass();
	~TriangleClass();

public:

	Vertex point1;
	Vertex point2;
	Vertex point3;

};

