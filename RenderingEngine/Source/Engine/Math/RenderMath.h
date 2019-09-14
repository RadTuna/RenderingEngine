#pragma once

#define _USE_MATH_DEFINES

#include "Engine/Engine.h"


#define KINDA_SMALL_NUMBER 1.e-3f

struct Vector2
{
	float X;
	float Y;

	Vector2 operator+(const Vector2& Other) const;
	Vector2 operator-(const Vector2& Other) const;
	Vector2 operator*(const Vector2& Other) const;
	Vector2 operator*(const float& Other) const;
	Vector2 operator/(const float& Other) const;
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
	Vector3 operator/(const float& Other) const;
};

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;

	Vector4 operator+(const Vector4& Other) const;
	Vector4 operator-(const Vector4& Other) const;
	Vector4 operator*(const Vector4& Other) const;
	Vector4 operator*(const float& Other) const;
	Vector4 operator/(const float& Other) const;
};

struct IntPoint2D
{
	int X;
	int Y;
};

struct Matrix2x2
{
	float mat11, mat12;
	float mat21, mat22;

	static Matrix2x2 GetIdentity();
	Matrix2x2 operator+(const Matrix2x2& Other) const;
	Matrix2x2 operator-(const Matrix2x2& Other) const;
};

struct Matrix3x3
{
	float mat11, mat12, mat13;
	float mat21, mat22, mat23;
	float mat31, mat32, mat33;

	static Matrix3x3 GetIdentity();
	Matrix3x3 operator+(const Matrix3x3& Other) const;
	Matrix3x3 operator-(const Matrix3x3& Other) const;
};

struct Matrix4x4
{
	float mat11, mat12, mat13, mat14;
	float mat21, mat22, mat23, mat24;
	float mat31, mat32, mat33, mat34;
	float mat41, mat42, mat43, mat44;

	static Matrix4x4 GetIdentity();
	Matrix4x4 operator+(const Matrix4x4& Other) const;
	Matrix4x4 operator-(const Matrix4x4& Other) const;
};

struct ColorRGBA
{
	BYTE red;
	BYTE green;
	BYTE blue;
	BYTE alpha;

	ColorRGBA();
	ColorRGBA(BYTE inRed, BYTE inGreen, BYTE inBlue, BYTE inAlpha);
	void SetRGB(BYTE inRed, BYTE inGreen, BYTE inBlue, BYTE inAlpha);
	ColorRGBA operator*(const ColorRGBA& Other) const;
	ColorRGBA operator*(const float& Other) const;
	ColorRGBA operator+(const ColorRGBA& Other) const;
	ColorRGBA operator-(const ColorRGBA& Other) const;
	ColorRGBA operator/(const float& Other) const;
};

class RenderMath
{
public:

	static void MatrixMul(Matrix2x2* outMat, const Matrix2x2& inMat);
	static void MatrixMul(Vector2* outVector, const Matrix2x2& inMat);
	static void MatrixMul(Matrix3x3* outMat, const Matrix3x3& inMat);
	static void MatrixMul(Vector3* outVector, const Matrix3x3& inMat);
	static void MatrixMul(Matrix4x4* outMat, const Matrix4x4& inMat);
	static void MatrixMul(Vector4* outVector, const Matrix4x4& inMat);
	static Matrix4x4 GetRotationMatrix4x4(const Vector4& rotation);
	static Matrix4x4 GetLocationMatrix4x4(const Vector4& location);
	static Matrix4x4 GetScaleMatrix4x4(const Vector4& scale);
	static Matrix4x4 GetTransformMatrix4x4(const Vector4& location, const Vector4& rotation, const Vector4& scale);

	static float GetVectorLength(const Vector2& inVector);
	static float GetVectorLength(const Vector3& inVector);
	static float GetVectorLength(const Vector4& inVector);
	static float GetTriangleArea(const float& length1, const float& length2, const float& angle);
	static float DotProduct(const Vector2& inVector1, const Vector2& inVector2);
	static float DotProduct(const Vector3& inVector1, const Vector3& inVector2);
	static float DotProduct(const Vector4& inVector1, const Vector4& inVector2);
	static Vector4 CrossProduct(const Vector4& inVector1, const Vector4& inVector2);
	static bool Normalize(Vector2* outVector);
	static bool Normalize(Vector3* outVector);
	static bool Normalize(Vector4* outVector);
	static IntPoint2D Vector2toIntPoint2D(const Vector2& inVector);
	static IntPoint2D Vector3toIntPoint2D(const Vector3& inVector);
	static constexpr float GetConvertRadianValue();
	static bool IsNearlyFloat(float valueA, float valueB, float tolerance = KINDA_SMALL_NUMBER);
	static float NormalizeFloat(float target, float min, float max);
	static Vector2 Vector3toVector2(const Vector3& inVector);
	static Vector2 Vector4toVector2(const Vector4& inVector);

	static ColorRGBA ColorRGBASet(BYTE inRed, BYTE inGreen, BYTE inBlue, BYTE inAlpha);

public:

	template <typename T>
	static T Clamp(T targetVal, T minVal, T maxVal);

	template<typename T, typename U>
	static IntPoint2D IntFloat2toIntPoint2D(T x, U y);

	template<typename T, typename U>
	static Vector2 Vector2Set(T x, U y);

	template<typename T, typename U, typename V>
	static Vector3 Vector3Set(T x, U y, V z);

	template<typename T, typename U, typename V, typename W>
	static Vector4 Vector4Set(T x, U y, V z, W w);

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

template<typename T, typename U, typename V, typename W>
Vector4 RenderMath::Vector4Set(T x, U y, V z, W w)
{
	Vector4 temp;
	temp.X = static_cast<float>(x);
	temp.Y = static_cast<float>(y);
	temp.Z = static_cast<float>(z);
	temp.W = static_cast<float>(w);
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
