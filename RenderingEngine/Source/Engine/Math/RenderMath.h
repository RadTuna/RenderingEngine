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

struct ColorRGB
{
	BYTE Red;
	BYTE Green;
	BYTE Blue;

	ColorRGB()
	{
		Red = 0; Green = 0; Blue = 0;
	}

	ColorRGB(BYTE inRed, BYTE inGreen, BYTE inBlue)
	{
		Red = inRed; Green = inGreen; Blue = inBlue;
	}

	void SetRGB(BYTE inRed, BYTE inGreen, BYTE inBlue)
	{
		Red = inRed; Green = inGreen; Blue = inBlue;
	}
};

class RenderMath
{
public:

	static void MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat);

	static void MatrixMul(Vector2D* outVector, Matrix2x2 inMat);

	static Vector2D VectorSum(Vector2D inVector1, Vector2D inVector2);

	static Vector2D VectorSub(Vector2D inVector1, Vector2D inVector2);

	static void SortVecticesByY(class TriangleClass* Vertices);

	static Vector2D Vector2DSet(float x, float y);

};
