#pragma once

#include "Engine/Engine.h"

struct Vector2D
{
	float X;
	float Y;
};

struct Matrix2x2
{
	float mat11;
	float mat12;
	float mat21;
	float mat22;
};

struct TriangleVertices
{
	Vector2D firstVertex;
	Vector2D secondVertex;
	Vector2D thirdVertex;
};

class MatrixHelpers
{
public:

	static void MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat);

	static void MatrixMul(Vector2D* outVector, Matrix2x2 inMat);

	static Vector2D VectorSum(Vector2D inVector1, Vector2D inVector2);

	static Vector2D VectorSub(Vector2D inVector1, Vector2D inVector2);

	static void SortVecticesByY(TriangleVertices* Vertices);

};
