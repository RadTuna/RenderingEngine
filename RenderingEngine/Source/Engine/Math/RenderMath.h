#pragma once

#define _USE_MATH_DEFINES

#include "Engine/Engine.h"


struct Vector2
{
	float X;
	float Y;

	Vector2 operator+(const Vector2& Other) const;
	Vector2 operator-(const Vector2& Other) const;
	Vector2 operator*(const Vector2& Other) const;
	Vector2 operator*(const float& Other) const;
};

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3 operator+(const Vector3& Other) const;
	Vector3 operator-(const Vector3& Other) const;
	Vector3 operator*(const Vector3& Other) const;
	Vector3 operator*(const float& Other) const;
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

	static Matrix2x2 GetIdentity();
	Matrix2x2 operator+(const Matrix2x2& Other) const;
	Matrix2x2 operator-(const Matrix2x2& Other) const;
};

struct Matrix3x3
{
	float mat11;
	float mat12;
	float mat13;
	float mat21;
	float mat22;
	float mat23;
	float mat31;
	float mat32;
	float mat33;

	static Matrix3x3 GetIdentity();
	Matrix3x3 operator+(const Matrix3x3& Other) const;
	Matrix3x3 operator-(const Matrix3x3& Other) const;
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

	static void MatrixMul(Matrix2x2* outMat, const Matrix2x2& inMat);
	static void MatrixMul(Vector2* outVector, const Matrix2x2& inMat);
	static void MatrixMul(Matrix3x3* outVector, const Matrix3x3& inMat);
	static void MatrixMul(Vector3* outVector, const Matrix3x3& inMat);
	static Matrix3x3 GetRotationMatrix3x3(float rotation);
	static Matrix3x3 GetLocationMatrix3x3(Vector3& location);
	static Matrix3x3 GetScaleMatrix3x3(Vector3& scale);
	static Matrix3x3 GetTransformMatrix3x3(Vector3& location, float rotation, Vector3& scale);

	static float GetVectorLength(const Vector2& inVector);
	static float GetTriangleArea(const float& length1, const float& length2, const float& angle);
	static float DotProduct(const Vector2& inVector1, const Vector2& inVector2);
	static float DotProduct(const Vector3& inVector1, const Vector3& inVector2);
	static float HomoDotProduct(const Vector3& inVector1, const Vector3& inVector2);
	static Vector2 Normalize(const Vector2& inVector);
	static IntPoint2D Vector2toIntPoint2D(const Vector2& inVector);
	static IntPoint2D Vector3toIntPoint2D(const Vector3& inVector);

	static void SortVecticesByY(struct Triangle* Vertices);

	static ColorRGB ColorRGBSet(BYTE inRed, BYTE inGreen, BYTE inBlue);

public:

	template <typename T>
	static T Clamp(T targetVal, T minVal, T maxVal);

	template<typename T, typename U>
	static IntPoint2D IntFloat2toIntPoint2D(T x, U y);

	template<typename T, typename U>
	static Vector2 Vector2Set(T x, U y);

	template<typename T, typename U, typename V>
	static Vector3 Vector3Set(T x, U y, V z);

	template<typename T>
	static T GetMax(T aVal, T bVal);

	template<typename T>
	static T GetMin(T aVal, T bVal);

};

template<typename T>
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

template<typename T, typename U>
IntPoint2D RenderMath::IntFloat2toIntPoint2D(T x, U y)
{
	IntPoint2D temp;
	temp.X = static_cast<int>(x);
	temp.Y = static_cast<int>(y);
	return temp;
}

template<typename T, typename U>
Vector2 RenderMath::Vector2Set(T x, U y)
{
	Vector2 temp;
	temp.X = static_cast<float>(x);
	temp.Y = static_cast<float>(y);
	return temp;
}

template<typename T, typename U, typename V>
Vector3 RenderMath::Vector3Set(T x, U y, V z)
{
	Vector3 temp;
	temp.X = static_cast<float>(x);
	temp.Y = static_cast<float>(y);
	temp.Z = static_cast<float>(z);
	return temp;
}

template<typename T>
T RenderMath::GetMax(T aVal, T bVal)
{
	if (aVal > bVal)
	{
		return aVal;
	}
	else
	{
		return bVal;
	}
}

template<typename T>
T RenderMath::GetMin(T aVal, T bVal)
{
	if (aVal < bVal)
	{
		return aVal;
	}
	else
	{
		return bVal;
	}
}
