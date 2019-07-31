#pragma once

#include "Engine/Engine.h"


struct Vector2
{
	float X;
	float Y;

	Vector2 operator+(const Vector2& Other) const;
	Vector2 operator-(const Vector2& Other) const;
};

struct Vector3
{
	float X;
	float Y;
	float Z;

};

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;
};

struct IntPoint2D
{
	int X;
	int Y;
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

	ColorRGB();
	ColorRGB(BYTE inRed, BYTE inGreen, BYTE inBlue);
	void SetRGB(BYTE inRed, BYTE inGreen, BYTE inBlue);
	ColorRGB operator*(const ColorRGB& Other) const;
	ColorRGB operator*(const float& Other) const;
	ColorRGB operator+(const ColorRGB& Other) const;
	ColorRGB operator-(const ColorRGB& Other) const;
};

class RenderMath
{
public:

	static void MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat);
	static void MatrixMul(Vector2* outVector, Matrix2x2 inMat);

	static Vector2 VectorSum(Vector2 inVector1, Vector2 inVector2);
	static Vector2 VectorSub(Vector2 inVector1, Vector2 inVector2);
	static Vector2 Vector2Set(float x, float y);
	static Vector3 Vector3Set(float x, float y, float z);
	static float GetVectorLength(Vector2 inVector);
	static float GetTriangleArea(float length1, float length2, float angle);
	static float DotProduct(Vector2 inVector1, Vector2 inVector2);
	static Vector2 Normalize(Vector2 inVector);

	static void SortVecticesByY(class TriangleClass* Vertices);

	static ColorRGB ColorRGBSet(BYTE inRed, BYTE inGreen, BYTE inBlue);

	template <typename T>
	static T Clamp(T targetVal, T minVal, T maxVal);

};

template <typename T>
T RenderMath::Clamp(T targetVal, T minVal, T maxVal)
{
	if (targetVal > maxVal)
	{
		return maxVal;
	}
	else if(targetVal < minVal)
	{
		return minVal;
	}

	return targetVal;
}
