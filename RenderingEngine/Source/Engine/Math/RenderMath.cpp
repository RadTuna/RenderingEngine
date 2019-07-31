
#include "RenderMath.h"
#include "Engine/SoftRenderer/TriangleClass.h"


void RenderMath::MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat)
{
	Matrix2x2 tempMat = *outMat;

	outMat->mat11 = tempMat.mat11 * inMat.mat11 + tempMat.mat12 * inMat.mat21;
	outMat->mat12 = tempMat.mat11 * inMat.mat12 + tempMat.mat12 * inMat.mat22;
	outMat->mat21 = tempMat.mat21 * inMat.mat11 + tempMat.mat22 * inMat.mat21;
	outMat->mat22 = tempMat.mat21 * inMat.mat12 + tempMat.mat22 * inMat.mat22;
}

void RenderMath::MatrixMul(Vector2* outVector, Matrix2x2 inMat)
{
	Vector2 tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat12;
	outVector->Y = tempVec.X * inMat.mat21 + tempVec.Y * inMat.mat22;
}

Vector2 RenderMath::VectorSum(Vector2 inVector1, Vector2 inVector2)
{
	Vector2 outVector;
	outVector.X = inVector1.X + inVector2.X;
	outVector.Y = inVector1.Y + inVector2.Y;

	return outVector;
}

Vector2 RenderMath::VectorSub(Vector2 inVector1, Vector2 inVector2)
{
	Vector2 outVector;
	outVector.X = inVector1.X - inVector2.X;
	outVector.Y = inVector1.Y - inVector2.Y;

	return outVector;
}

float RenderMath::GetVectorLength(Vector2 inVector)
{
	return std::sqrtf(std::powf(inVector.X, 2) + std::powf(inVector.Y, 2));
}

float RenderMath::GetTriangleArea(float length1, float length2, float angle)
{
	return length1 * length2 * 0.5f * std::sinf(angle);
}

float RenderMath::DotProduct(Vector2 inVector1, Vector2 inVector2)
{
	return inVector1.X * inVector2.X + inVector1.Y * inVector2.Y;
}

Vector2 RenderMath::Normalize(Vector2 inVector)
{
	float vectorLength = RenderMath::GetVectorLength(inVector);

	inVector.X = inVector.X / vectorLength;
	inVector.Y = inVector.Y / vectorLength;

	return inVector;
}

void RenderMath::SortVecticesByY(TriangleClass* vertices)
{
	if (!(vertices->point1.position.Y >= vertices->point2.position.Y) && (vertices->point1.position.Y >= vertices->point3.position.Y))
	{
		if (vertices->point2.position.Y > vertices->point3.position.Y)
		{
			std::swap(vertices->point1, vertices->point2);
		}
		else
		{
			std::swap(vertices->point1, vertices->point3);
		}
	}

	if (!vertices->point2.position.Y < vertices->point3.position.Y)
	{
		std::swap(vertices->point2, vertices->point3);
	}

	return;
}

Vector2 RenderMath::Vector2Set(float x, float y)
{
	Vector2 Temp = { x, y };
	return Temp;
}

Vector3 RenderMath::Vector3Set(float x, float y, float z)
{
	Vector3 Temp = { x, y, z };
	return Temp;
}

ColorRGB RenderMath::ColorRGBSet(BYTE inRed, BYTE inGreen, BYTE inBlue)
{
	ColorRGB Temp = { inRed, inGreen, inBlue };
	return Temp;
}

Vector2 Vector2::operator+(const Vector2& Other) const
{
	Vector2 Temp;
	Temp.X = X + Other.X;
	Temp.Y = Y + Other.Y;
	return Temp;
}

Vector2 Vector2::operator-(const Vector2& Other) const
{
	Vector2 Temp;
	Temp.X = X - Other.X;
	Temp.Y = Y - Other.Y;
	return Temp;
}

ColorRGB::ColorRGB()
{
	Red = 0; Green = 0; Blue = 0;
}

ColorRGB::ColorRGB(BYTE inRed, BYTE inGreen, BYTE inBlue)
{
	Red = inRed; Green = inGreen; Blue = inBlue;
}

ColorRGB ColorRGB::operator*(const ColorRGB& Other) const
{
	ColorRGB Temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	Temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red * Other.Red), minByte, maxByte);
	Temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green * Other.Green), minByte, maxByte);
	Temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue * Other.Blue), minByte, maxByte);
	return Temp;
}

ColorRGB ColorRGB::operator*(const float& Other) const
{
	ColorRGB Temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	Temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red * Other), minByte, maxByte);
	Temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green * Other), minByte, maxByte);
	Temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue * Other), minByte, maxByte);
	return Temp;
}
ColorRGB ColorRGB::operator+(const ColorRGB& Other) const
{
	ColorRGB Temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	Temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red + Other.Red), minByte, maxByte);
	Temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green + Other.Green), minByte, maxByte);
	Temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue + Other.Blue), minByte, maxByte);
	return Temp;
}

ColorRGB ColorRGB::operator-(const ColorRGB& Other) const
{
	ColorRGB Temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	Temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red - Other.Red), minByte, maxByte);
	Temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green - Other.Green), minByte, maxByte);
	Temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue - Other.Blue), minByte, maxByte);
	return Temp;
}

void ColorRGB::SetRGB(BYTE inRed, BYTE inGreen, BYTE inBlue)
{
	Red = inRed; Green = inGreen; Blue = inBlue;
}