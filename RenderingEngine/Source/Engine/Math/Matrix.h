#pragma once

class MatrixHelpers
{
public:

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

	void MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat);

	void MatrixMul(Vector2D* outVector, Matrix2x2 inMat);

	Vector2D VectorSum(Vector2D inVector1, Vector2D inVector2);

};
