#pragma once

struct Vector2D
{
	int X;
	int Y;
};

struct Matrix2x2
{
	int mat11;
	int mat12;
	int mat21;
	int mat22;
};

struct TriangleVertices
{
	Vector2D FirstVertex;
	Vector2D SecondVertex;
	Vector2D ThirdVertex;
};

class MatrixHelpers
{
public:

	static void MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat);

	static void MatrixMul(Vector2D* outVector, Matrix2x2 inMat);

	static Vector2D VectorSum(Vector2D inVector1, Vector2D inVector2);

	static Vector2D VectorSub(Vector2D inVector1, Vector2D inVector2);

};
