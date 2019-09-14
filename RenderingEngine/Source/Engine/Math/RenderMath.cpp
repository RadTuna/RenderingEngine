
#include "RenderMath.h"


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

void RenderMath::MatrixMul(Vector3* outVector, const Matrix3x3& inMat)
{
	Vector3 tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat21 + tempVec.Z * inMat.mat31;
	outVector->Y = tempVec.X * inMat.mat12 + tempVec.Y * inMat.mat22 + tempVec.Z * inMat.mat32;
	outVector->Z = tempVec.X * inMat.mat13 + tempVec.Y * inMat.mat23 + tempVec.Z * inMat.mat33;
}

void RenderMath::MatrixMul(Matrix4x4* outMat, const Matrix4x4& inMat)
{
	Matrix4x4 tempMat = *outMat;

	outMat->mat11 = tempMat.mat11 * inMat.mat11 + tempMat.mat12 * inMat.mat21 + tempMat.mat13 * inMat.mat31 + tempMat.mat14 * inMat.mat41;
	outMat->mat12 = tempMat.mat11 * inMat.mat12 + tempMat.mat12 * inMat.mat22 + tempMat.mat13 * inMat.mat32 + tempMat.mat14 * inMat.mat42;
	outMat->mat13 = tempMat.mat11 * inMat.mat13 + tempMat.mat12 * inMat.mat23 + tempMat.mat13 * inMat.mat33 + tempMat.mat14 * inMat.mat43;
	outMat->mat14 = tempMat.mat11 * inMat.mat14 + tempMat.mat12 * inMat.mat24 + tempMat.mat13 * inMat.mat34 + tempMat.mat14 * inMat.mat44;
	outMat->mat21 = tempMat.mat21 * inMat.mat11 + tempMat.mat22 * inMat.mat21 + tempMat.mat23 * inMat.mat31 + tempMat.mat24 * inMat.mat41;
	outMat->mat22 = tempMat.mat21 * inMat.mat12 + tempMat.mat22 * inMat.mat22 + tempMat.mat23 * inMat.mat32 + tempMat.mat24 * inMat.mat42;
	outMat->mat23 = tempMat.mat21 * inMat.mat13 + tempMat.mat22 * inMat.mat23 + tempMat.mat23 * inMat.mat33 + tempMat.mat24 * inMat.mat43;
	outMat->mat24 = tempMat.mat21 * inMat.mat14 + tempMat.mat22 * inMat.mat24 + tempMat.mat23 * inMat.mat34 + tempMat.mat24 * inMat.mat44;
	outMat->mat31 = tempMat.mat31 * inMat.mat11 + tempMat.mat32 * inMat.mat21 + tempMat.mat33 * inMat.mat31 + tempMat.mat34 * inMat.mat41;
	outMat->mat32 = tempMat.mat31 * inMat.mat12 + tempMat.mat32 * inMat.mat22 + tempMat.mat33 * inMat.mat32 + tempMat.mat34 * inMat.mat42;
	outMat->mat33 = tempMat.mat31 * inMat.mat13 + tempMat.mat32 * inMat.mat23 + tempMat.mat33 * inMat.mat33 + tempMat.mat34 * inMat.mat43;
	outMat->mat34 = tempMat.mat31 * inMat.mat14 + tempMat.mat32 * inMat.mat24 + tempMat.mat33 * inMat.mat34 + tempMat.mat34 * inMat.mat44;
	outMat->mat41 = tempMat.mat41 * inMat.mat11 + tempMat.mat42 * inMat.mat21 + tempMat.mat43 * inMat.mat31 + tempMat.mat44 * inMat.mat41;
	outMat->mat42 = tempMat.mat41 * inMat.mat12 + tempMat.mat42 * inMat.mat22 + tempMat.mat43 * inMat.mat32 + tempMat.mat44 * inMat.mat42;
	outMat->mat43 = tempMat.mat41 * inMat.mat13 + tempMat.mat42 * inMat.mat23 + tempMat.mat43 * inMat.mat33 + tempMat.mat44 * inMat.mat43;
	outMat->mat44 = tempMat.mat41 * inMat.mat14 + tempMat.mat42 * inMat.mat24 + tempMat.mat43 * inMat.mat34 + tempMat.mat44 * inMat.mat44;
}

void RenderMath::MatrixMul(Vector4* outVector, const Matrix4x4& inMat)
{
	Vector4 tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat21 + tempVec.Z * inMat.mat31 + tempVec.W * inMat.mat41;
	outVector->Y = tempVec.X * inMat.mat12 + tempVec.Y * inMat.mat22 + tempVec.Z * inMat.mat32 + tempVec.W * inMat.mat42;
	outVector->Z = tempVec.X * inMat.mat13 + tempVec.Y * inMat.mat23 + tempVec.Z * inMat.mat33 + tempVec.W * inMat.mat43;
	outVector->W = tempVec.X * inMat.mat14 + tempVec.Y * inMat.mat24 + tempVec.Z * inMat.mat34 + tempVec.W * inMat.mat44;
}

Matrix4x4 RenderMath::GetRotationMatrix4x4(const Vector4& rotation)
{
	Matrix4x4 xRotMat = { 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cosf(rotation.X / GetConvertRadianValue()), std::sinf(rotation.X / GetConvertRadianValue()), 0.0f, 
		0.0f, std::sinf(rotation.X / GetConvertRadianValue()) * -1.0f, std::cosf(rotation.X / GetConvertRadianValue()), 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f };
	Matrix4x4 yRotMat = {
		std::cosf(rotation.Y / GetConvertRadianValue()), 0.0f, std::sinf(rotation.Y / GetConvertRadianValue()) * -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sinf(rotation.Y / GetConvertRadianValue()), 0.0f, std::cosf(rotation.Y / GetConvertRadianValue()), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
	Matrix4x4 zRotMat = {
		std::cosf(rotation.Z / GetConvertRadianValue()), std::sinf(rotation.Z / GetConvertRadianValue()), 0.0f, 0.0f,
		std::sinf(rotation.Z / GetConvertRadianValue()) * -1.0f, std::cosf(rotation.Z / GetConvertRadianValue()), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	RenderMath::MatrixMul(&zRotMat, yRotMat);
	RenderMath::MatrixMul(&zRotMat, xRotMat);

	return zRotMat;
}

Matrix4x4 RenderMath::GetLocationMatrix4x4(const Vector4& location)
{
	Matrix4x4 tempMat = { 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		location.X, location.Y, location.Z, 1.0f };
	return tempMat;
}

Matrix4x4 RenderMath::GetScaleMatrix4x4(const Vector4& scale)
{
	Matrix4x4 tempMat = { 
		scale.X, 0.0f, 0.0f, 0.0f,
		0.0f, scale.Y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};
	return tempMat;
}

Matrix4x4 RenderMath::GetTransformMatrix4x4(const Vector4& location, const Vector4& rotation, const Vector4& scale)
{
	Matrix4x4 locationMat = GetLocationMatrix4x4(location);
	Matrix4x4 rotationMat = GetRotationMatrix4x4(rotation);
	Matrix4x4 scaleMat = GetScaleMatrix4x4(scale);

	RenderMath::MatrixMul(&scaleMat, rotationMat);
	RenderMath::MatrixMul(&scaleMat, locationMat);

	return scaleMat;
}

float RenderMath::GetVectorLength(const Vector2& inVector)
{
	return std::sqrtf(std::powf(inVector.X, 2) + std::powf(inVector.Y, 2));
}

float RenderMath::GetVectorLength(const Vector3& inVector)
{
	return std::sqrtf(std::powf(inVector.X, 2) + std::powf(inVector.Y, 2));
}

float RenderMath::GetVectorLength(const Vector4& inVector)
{
	return std::sqrtf(std::powf(inVector.X, 2) + std::powf(inVector.Y, 2) + std::powf(inVector.Z, 2));
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
	return inVector1.X * inVector2.X + inVector1.Y * inVector2.Y;
}

float RenderMath::DotProduct(const Vector4& inVector1, const Vector4& inVector2)
{
	return inVector1.X * inVector2.X + inVector1.Y * inVector2.Y + inVector1.Z * inVector2.Z;
}

Vector4 RenderMath::CrossProduct(const Vector4& inVector1, const Vector4& inVector2)
{
	return RenderMath::Vector4Set(
		inVector1.Y * inVector2.Z - inVector1.Z * inVector2.Y,
		inVector1.Z * inVector2.X - inVector1.X * inVector2.Z,
		inVector1.X * inVector2.Y - inVector1.Y * inVector2.X,
		0.0f);
}

bool RenderMath::Normalize(Vector2* outVector)
{
	float vectorLength = RenderMath::GetVectorLength(*outVector);

	if (vectorLength <= KINDA_SMALL_NUMBER)
	{
		return false;
	}
	
	outVector->X /= vectorLength;
	outVector->Y /= vectorLength;

	return true;
}

bool RenderMath::Normalize(Vector3* outVector)
{
	float vectorLength = RenderMath::GetVectorLength(*outVector);

	if (vectorLength <= KINDA_SMALL_NUMBER)
	{
		return false;
	}

	outVector->X /= vectorLength;
	outVector->Y /= vectorLength;

	return true;
}

bool RenderMath::Normalize(Vector4* outVector)
{
	float vectorLength = RenderMath::GetVectorLength(*outVector);

	if (vectorLength <= KINDA_SMALL_NUMBER)
	{
		return false;
	}

	outVector->X /= vectorLength;
	outVector->Y /= vectorLength;
	outVector->Z /= vectorLength;

	return true;
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

constexpr float RenderMath::GetConvertRadianValue()
{
	return 360.0f / (static_cast<float>(M_PI) * 2.0f);
}

bool RenderMath::IsNearlyFloat(float valueA, float valueB, float tolerance)
{
	if (abs(valueA - valueB) < tolerance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float RenderMath::NormalizeFloat(float target, float min, float max)
{
	if (target < min || target > max || min >= max)
	{
		return target;
	}

	return (target - min) / (max - min);
}

ColorRGBA RenderMath::ColorRGBASet(BYTE inRed, BYTE inGreen, BYTE inBlue, BYTE inAlpha)
{
	ColorRGBA temp = { inRed, inGreen, inBlue, inAlpha };
	return temp;
}

Vector2 RenderMath::Vector3toVector2(const Vector3& inVector)
{
	Vector2 temp;
	temp.X = inVector.X;
	temp.Y = inVector.Y;
	return temp;
}

Vector2 RenderMath::Vector4toVector2(const Vector4& inVector)
{
	Vector2 temp;
	temp.X = inVector.X;
	temp.Y = inVector.Y;
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

Vector2 Vector2::operator/(const float& Other) const
{
	Vector2 temp;
	temp.X = X / Other;
	temp.Y = Y / Other;
	return temp;
}

Vector3 Vector3::operator+(const Vector3& Other) const
{
	Vector3 temp;
	temp.X = X + Other.X;
	temp.Y = Y + Other.Y;
	return temp;
}

Vector3 Vector3::operator-(const Vector3& Other) const
{
	Vector3 temp;
	temp.X = X - Other.X;
	temp.Y = Y - Other.Y;
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
	return temp;
}

Vector3 Vector3::operator/(const float& Other) const
{
	Vector3 temp;
	temp.X = X / Other;
	temp.Y = Y / Other;
	return temp;
}

Vector4 Vector4::operator+(const Vector4& Other) const
{
	Vector4 temp;
	temp.X = X + Other.X;
	temp.Y = Y + Other.Y;
	temp.Z = Z + Other.Z;
	return temp;
}

Vector4 Vector4::operator-(const Vector4& Other) const
{
	Vector4 temp;
	temp.X = X - Other.X;
	temp.Y = Y - Other.Y;
	temp.Z = Z - Other.Z;
	return temp;
}

Vector4 Vector4::operator*(const Vector4& Other) const
{
	Vector4 temp;
	temp.X = X * Other.X;
	temp.Y = Y * Other.Y;
	temp.Z = Z * Other.Z;
	temp.W = W * Other.W;
	return temp;
}

Vector4 Vector4::operator*(const float& Other) const
{
	Vector4 temp;
	temp.X = X * Other;
	temp.Y = Y * Other;
	temp.Z = Z * Other;
	return temp;
}

Vector4 Vector4::operator/(const float& Other) const
{
	Vector4 temp;
	temp.X = X / Other;
	temp.Y = Y / Other;
	temp.Z = Z / Other;
	return temp;
}

ColorRGBA::ColorRGBA()
{
	red = 0; green = 0; blue = 0; alpha = 0;
}

ColorRGBA::ColorRGBA(BYTE inRed, BYTE inGreen, BYTE inBlue, BYTE inAlpha)
{
	red = inRed; green = inGreen; blue = inBlue; alpha = inAlpha;
}

ColorRGBA ColorRGBA::operator*(const ColorRGBA& Other) const
{
	ColorRGBA temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(red * Other.red), minByte, maxByte);
	temp.green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(green * Other.green), minByte, maxByte);
	temp.blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(blue * Other.blue), minByte, maxByte);
	temp.alpha = RenderMath::Clamp<BYTE>(static_cast<BYTE>(alpha * Other.alpha), minByte, maxByte);
	return temp;
}

ColorRGBA ColorRGBA::operator*(const float& Other) const
{
	ColorRGBA temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(red * Other), minByte, maxByte);
	temp.green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(green * Other), minByte, maxByte);
	temp.blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(blue * Other), minByte, maxByte);
	temp.alpha = RenderMath::Clamp<BYTE>(static_cast<BYTE>(alpha * Other), minByte, maxByte);
	return temp;
}
ColorRGBA ColorRGBA::operator+(const ColorRGBA& Other) const
{
	ColorRGBA temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(red + Other.red), minByte, maxByte);
	temp.green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(green + Other.green), minByte, maxByte);
	temp.blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(blue + Other.blue), minByte, maxByte);
	temp.alpha = RenderMath::Clamp<BYTE>(static_cast<BYTE>(alpha + Other.alpha), minByte, maxByte);
	return temp;
}

ColorRGBA ColorRGBA::operator-(const ColorRGBA& Other) const
{
	ColorRGBA temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(red - Other.red), minByte, maxByte);
	temp.green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(green - Other.green), minByte, maxByte);
	temp.blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(blue - Other.blue), minByte, maxByte);
	temp.alpha = RenderMath::Clamp<BYTE>(static_cast<BYTE>(alpha - Other.alpha), minByte, maxByte);
	return temp;
}

ColorRGBA ColorRGBA::operator/(const float& Other) const
{
	ColorRGBA temp;
	BYTE minByte = 0;
	BYTE maxByte = 255;

	temp.red = RenderMath::Clamp<BYTE>(static_cast<BYTE>(red / Other), minByte, maxByte);
	temp.green = RenderMath::Clamp<BYTE>(static_cast<BYTE>(green / Other), minByte, maxByte);
	temp.blue = RenderMath::Clamp<BYTE>(static_cast<BYTE>(blue / Other), minByte, maxByte);
	temp.alpha = RenderMath::Clamp<BYTE>(static_cast<BYTE>(alpha / Other), minByte, maxByte);
	return temp;
}

void ColorRGBA::SetRGB(BYTE inRed, BYTE inGreen, BYTE inBlue, BYTE inAlpha)
{
	red = inRed; green = inGreen; blue = inBlue; alpha = inAlpha;
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

Matrix4x4 Matrix4x4::GetIdentity()
{
	Matrix4x4 temp = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	return temp;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& Other) const
{
	Matrix4x4 temp;

	temp.mat11 = mat11 + Other.mat11;
	temp.mat12 = mat12 + Other.mat12;
	temp.mat13 = mat13 + Other.mat13;
	temp.mat14 = mat14 + Other.mat14;
	temp.mat21 = mat21 + Other.mat21;
	temp.mat22 = mat22 + Other.mat22;
	temp.mat23 = mat23 + Other.mat23;
	temp.mat24 = mat24 + Other.mat24;
	temp.mat31 = mat31 + Other.mat31;
	temp.mat32 = mat32 + Other.mat32;
	temp.mat33 = mat33 + Other.mat33;
	temp.mat34 = mat34 + Other.mat34;
	temp.mat41 = mat41 + Other.mat41;
	temp.mat42 = mat42 + Other.mat42;
	temp.mat43 = mat43 + Other.mat43;
	temp.mat44 = mat44 + Other.mat44;

	return temp;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& Other) const
{
	Matrix4x4 temp;

	temp.mat11 = mat11 - Other.mat11;
	temp.mat12 = mat12 - Other.mat12;
	temp.mat13 = mat13 - Other.mat13;
	temp.mat14 = mat14 - Other.mat14;
	temp.mat21 = mat21 - Other.mat21;
	temp.mat22 = mat22 - Other.mat22;
	temp.mat23 = mat23 - Other.mat23;
	temp.mat24 = mat24 - Other.mat24;
	temp.mat31 = mat31 - Other.mat31;
	temp.mat32 = mat32 - Other.mat32;
	temp.mat33 = mat33 - Other.mat33;
	temp.mat34 = mat34 - Other.mat34;
	temp.mat41 = mat41 - Other.mat41;
	temp.mat42 = mat42 - Other.mat42;
	temp.mat43 = mat43 - Other.mat43;
	temp.mat44 = mat44 - Other.mat44;

	return temp;
}


