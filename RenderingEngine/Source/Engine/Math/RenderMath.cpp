
#include "RenderMath.h"
#include "Engine/SoftRenderer/ShapeClass.h"


void RenderMath::MatrixMul(Matrix2x2* outMat, const Matrix2x2& inMat)
{
	Matrix2x2 tempMat = *outMat;

	outMat->mat11 = tempMat.mat11 * inMat.mat11 + tempMat.mat12 * inMat.mat21;
	outMat->mat12 = tempMat.mat11 * inMat.mat12 + tempMat.mat12 * inMat.mat22;
	outMat->mat21 = tempMat.mat21 * inMat.mat11 + tempMat.mat22 * inMat.mat21;
	outMat->mat22 = tempMat.mat21 * inMat.mat12 + tempMat.mat22 * inMat.mat22;
}

void RenderMath::MatrixMul(Vector2* outVector, const Matrix2x2& inMat)
{
	Vector2 tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat21;
	outVector->Y = tempVec.X * inMat.mat12 + tempVec.Y * inMat.mat22;
}

void RenderMath::MatrixMul(Matrix3x3* outMat, const Matrix3x3& inMat)
{
	Matrix3x3 tempMat = *outMat;

	outMat->mat11 = tempMat.mat11 * inMat.mat11 + tempMat.mat12 * inMat.mat21 + tempMat.mat13 * inMat.mat31;
	outMat->mat12 = tempMat.mat11 * inMat.mat12 + tempMat.mat12 * inMat.mat22 + tempMat.mat13 * inMat.mat32;
	outMat->mat13 = tempMat.mat11 * inMat.mat13 + tempMat.mat12 * inMat.mat23 + tempMat.mat13 * inMat.mat33;
	outMat->mat21 = tempMat.mat21 * inMat.mat11 + tempMat.mat22 * inMat.mat21 + tempMat.mat23 * inMat.mat31;
	outMat->mat22 = tempMat.mat21 * inMat.mat12 + tempMat.mat22 * inMat.mat22 + tempMat.mat23 * inMat.mat32;
	outMat->mat23 = tempMat.mat21 * inMat.mat13 + tempMat.mat22 * inMat.mat23 + tempMat.mat23 * inMat.mat33;
	outMat->mat31 = tempMat.mat31 * inMat.mat11 + tempMat.mat32 * inMat.mat21 + tempMat.mat33 * inMat.mat31;
	outMat->mat32 = tempMat.mat31 * inMat.mat12 + tempMat.mat32 * inMat.mat22 + tempMat.mat33 * inMat.mat32;
	outMat->mat33 = tempMat.mat31 * inMat.mat13 + tempMat.mat32 * inMat.mat23 + tempMat.mat33 * inMat.mat33;
}

Matrix3x3 RenderMath::GetRotationMatrix3x3(float rotation)
{
	Matrix3x3 tempMat = { std::cosf(rotation / (float)M_PI), std::sinf(rotation / (float)M_PI), 0.0f, std::sinf(rotation / (float)M_PI) * -1.0f, std::cosf(rotation / (float)M_PI), 0.0f, 0.0f, 0.0f, 1.0f };
	return tempMat;
}

Matrix3x3 RenderMath::GetLocationMatrix3x3(Vector3& location)
{
	Matrix3x3 tempMat = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, location.X, location.Y, 1.0f };
	return tempMat;
}

Matrix3x3 RenderMath::GetScaleMatrix3x3(Vector3& scale)
{
	Matrix3x3 tempMat = { scale.X, 0.0f, 0.0f, 0.0f, scale.Y, 0.0f, 0.0f, 0.0f, 1.0f };
	return tempMat;
}

Matrix3x3 RenderMath::GetTransformMatrix3x3(Vector3& location, float rotation, Vector3& scale)
{
	Matrix3x3 locationMat = GetLocationMatrix3x3(location);
	Matrix3x3 rotationMat = GetRotationMatrix3x3(rotation);
	Matrix3x3 scaleMat = GetScaleMatrix3x3(scale);

	RenderMath::MatrixMul(&scaleMat, rotationMat);
	RenderMath::MatrixMul(&scaleMat, locationMat);

	return scaleMat;
}

void RenderMath::MatrixMul(Vector3* outVector, const Matrix3x3& inMat)
{
	Vector3 tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat21 + tempVec.Z * inMat.mat31;
	outVector->Y = tempVec.X * inMat.mat12 + tempVec.Y * inMat.mat22 + tempVec.Z * inMat.mat32;
	outVector->Z = tempVec.X * inMat.mat13 + tempVec.Y * inMat.mat23 + tempVec.Z * inMat.mat33;
}

float RenderMath::GetVectorLength(const Vector2& inVector)
{
	return std::sqrtf(std::powf(inVector.X, 2) + std::powf(inVector.Y, 2));
}

float RenderMath::GetTriangleArea(const float& length1, const float& length2, const float& angle)
{
	return length1 * length2 * 0.5f * std::sinf(angle);
}

float RenderMath::DotProduct(const Vector2& inVector1, const Vector2& inVector2)
{
	return inVector1.X * inVector2.X + inVector1.Y * inVector2.Y;
}

float RenderMath::DotProduct(const Vector3& inVector1, const Vector3& inVector2)
{
	return inVector1.X * inVector2.X + inVector1.Y * inVector2.Y + inVector1.Z * inVector2.Z;
}

float RenderMath::HomoDotProduct(const Vector3& inVector1, const Vector3& inVector2)
{
	return inVector1.X * inVector2.X + inVector1.Y * inVector2.Y;
}

Vector2 RenderMath::Normalize(const Vector2& inVector)
{
	Vector2 temp;

	float vectorLength = RenderMath::GetVectorLength(inVector);

	if (vectorLength <= 0.001f)
	{
		return inVector;
	}
	
	temp.X = inVector.X / vectorLength;
	temp.Y = inVector.Y / vectorLength;

	return temp;
}

IntPoint2D RenderMath::Vector2toIntPoint2D(const Vector2& inVector)
{
	IntPoint2D temp;
	temp.X = static_cast<int>(inVector.X);
	temp.Y = static_cast<int>(inVector.Y);
	return temp;
}

IntPoint2D RenderMath::Vector3toIntPoint2D(const Vector3& inVector)
{
	IntPoint2D temp;
	temp.X = static_cast<int>(inVector.X);
	temp.Y = static_cast<int>(inVector.Y);
	return temp;
}


void RenderMath::SortVecticesByY(Triangle* vertices)
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

	if (vertices->point2.position.Y < vertices->point3.position.Y)
	{
		std::swap(vertices->point2, vertices->point3);
	}

	if (vertices->point1.position.Y == vertices->point2.position.Y)
	{
		if (vertices->point1.position.X > vertices->point1.position.X)
		{
			std::swap(vertices->point1, vertices->point2);
		}
	}

	if (vertices->point2.position.Y == vertices->point3.position.Y)
	{
		if (vertices->point2.position.X > vertices->point3.position.X)
		{
			std::swap(vertices->point2, vertices->point3);
		}
	}

	return;
}

ColorRGB RenderMath::ColorRGBSet(BYTE inRed, BYTE inGreen, BYTE inBlue)
{
	ColorRGB temp = { inRed, inGreen, inBlue };
	return temp;
}

Vector2 Vector2::operator+(const Vector2& Other) const
{
	Vector2 temp;
	temp.X = X + Other.X;
	temp.Y = Y + Other.Y;
	return temp;
}

Vector2 Vector2::operator-(const Vector2& Other) const
{
	Vector2 temp;
	temp.X = X - Other.X;
	temp.Y = Y - Other.Y;
	return temp;
}

Vector2 Vector2::operator*(const Vector2& Other) const
{
	Vector2 temp;
	temp.X = X * Other.X;
	temp.Y = Y * Other.Y;
	return temp;
}

Vector2 Vector2::operator*(const float& Other) const
{
	Vector2 temp;
	temp.X = X * Other;
	temp.Y = Y * Other;
	return temp;
}

Vector3 Vector3::operator+(const Vector3& Other) const
{
	Vector3 temp;
	temp.X = X + Other.X;
	temp.Y = Y + Other.Y;
	temp.Z = Z + Other.Z;
	return temp;
}

Vector3 Vector3::operator-(const Vector3& Other) const
{
	Vector3 temp;
	temp.X = X - Other.X;
	temp.Y = Y - Other.Y;
	temp.Z = Z - Other.Z;
	return temp;
}

Vector3 Vector3::operator*(const Vector3& Other) const
{
	Vector3 temp;
	temp.X = X * Other.X;
	temp.Y = Y * Other.Y;
	temp.Z = Z * Other.Z;
	return temp;
}

Vector3 Vector3::operator*(const float& Other) const
{
	Vector3 temp;
	temp.X = X * Other;
	temp.Y = Y * Other;
	temp.Z = Z * Other;
	return temp;
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
	ColorRGB temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red * Other.Red), minByte, maxByte);
	temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green * Other.Green), minByte, maxByte);
	temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue * Other.Blue), minByte, maxByte);
	return temp;
}

ColorRGB ColorRGB::operator*(const float& Other) const
{
	ColorRGB temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red * Other), minByte, maxByte);
	temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green * Other), minByte, maxByte);
	temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue * Other), minByte, maxByte);
	return temp;
}
ColorRGB ColorRGB::operator+(const ColorRGB& Other) const
{
	ColorRGB temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red + Other.Red), minByte, maxByte);
	temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green + Other.Green), minByte, maxByte);
	temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue + Other.Blue), minByte, maxByte);
	return temp;
}

ColorRGB ColorRGB::operator-(const ColorRGB& Other) const
{
	ColorRGB temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.Red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Red - Other.Red), minByte, maxByte);
	temp.Green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Green - Other.Green), minByte, maxByte);
	temp.Blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(Blue - Other.Blue), minByte, maxByte);
	return temp;
}

void ColorRGB::SetRGB(BYTE inRed, BYTE inGreen, BYTE inBlue)
{
	Red = inRed; Green = inGreen; Blue = inBlue;
}

Matrix2x2 Matrix2x2::GetIdentity()
{
	Matrix2x2 temp = { 1, 0, 0, 1 };
	return temp;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& Other) const
{
	Matrix2x2 temp;

	temp.mat11 = mat11 + Other.mat11;
	temp.mat12 = mat12 + Other.mat12;
	temp.mat21 = mat21 + Other.mat21;
	temp.mat22 = mat22 + Other.mat22;

	return temp;
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& Other) const
{
	Matrix2x2 temp;

	temp.mat11 = mat11 - Other.mat11;
	temp.mat12 = mat12 - Other.mat12;
	temp.mat21 = mat21 - Other.mat21;
	temp.mat22 = mat22 - Other.mat22;

	return temp;
}

Matrix3x3 Matrix3x3::GetIdentity()
{
	Matrix3x3 temp = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	return temp;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& Other) const
{
	Matrix3x3 temp;

	temp.mat11 = mat11 + Other.mat11;
	temp.mat12 = mat12 + Other.mat12;
	temp.mat13 = mat13 + Other.mat13;
	temp.mat21 = mat21 + Other.mat21;
	temp.mat22 = mat22 + Other.mat22;
	temp.mat23 = mat23 + Other.mat23;
	temp.mat31 = mat31 + Other.mat31;
	temp.mat32 = mat32 + Other.mat32;
	temp.mat33 = mat33 + Other.mat33;

	return temp;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& Other) const
{
	Matrix3x3 temp;

	temp.mat11 = mat11 - Other.mat11;
	temp.mat12 = mat12 - Other.mat12;
	temp.mat13 = mat13 - Other.mat13;
	temp.mat21 = mat21 - Other.mat21;
	temp.mat22 = mat22 - Other.mat22;
	temp.mat23 = mat23 - Other.mat23;
	temp.mat31 = mat31 - Other.mat31;
	temp.mat32 = mat32 - Other.mat32;
	temp.mat33 = mat33 - Other.mat33;

	return temp;
}


