
#include "Engine/SoftRenderer/Object.h"

Object::Object()
{
	mMesh = nullptr;
	mVerticesCount = 0;
}

Object::~Object()
{
	if (mMesh != nullptr)
	{
		delete[] mMesh;
		mMesh = nullptr;
	}
}

bool Object::Initialize(Triangle* triangleList, int verticesCount)
{
	mMesh = new Triangle[verticesCount];
	if (mMesh == nullptr)
	{
		return false;
	}

	for (int i = 0; i < verticesCount; ++i)
	{
		mMesh[i] = triangleList[i];
	}

	mVerticesCount = verticesCount;

	return true;
}

void Object::Release()
{
	if (mMesh != nullptr)
	{
		delete[] mMesh;
		mMesh = nullptr;
	}
}

void Object::SetLocation(const Vector4& location)
{
	mLocation = location;
}

void Object::SetRotation(const Vector4& rotation)
{
	mRotation = rotation;
}

void Object::SetScale(const Vector4& scale)
{
	mScale = scale;
}

void Object::SetTransform(const Vector4& location, const Vector4& rotation, const Vector4& scale)
{
	SetLocation(location);
	SetRotation(rotation);
	SetScale(scale);
}

void Object::DeepCopy(Object* target)
{
	if (target->GetTriangleList() != nullptr)
	{
		target->Release();
	}

	target->Initialize(mMesh, mVerticesCount);

	target->SetLocation(mLocation);
	target->SetRotation(mRotation);
	target->SetScale(mScale);
}

Triangle::Triangle(const Triangle& Other)
{
	point1 = Other.point1;
	point2 = Other.point2;
	point3 = Other.point3;
}

void Triangle::Initialize()
{
	mVectorU = RenderMath::Vector4toVector2(point2.position - point1.position);
	mVectorV = RenderMath::Vector4toVector2(point3.position - point1.position);

	mDotUU = RenderMath::DotProduct(mVectorU, mVectorU);
	mDotUV = RenderMath::DotProduct(mVectorU, mVectorV);
	mDotVV = RenderMath::DotProduct(mVectorV, mVectorV);

	mWeightDenominator = mDotUU * RenderMath::DotProduct(mVectorV, mVectorV) - mDotUV * mDotUV;

	// 투영보정보간을 위한 전처리 작업.
	point1.Color = point1.Color / point1.position.W;
	point2.Color = point2.Color / point2.position.W;
	point3.Color = point3.Color / point3.position.W;

	point1.UV = point1.UV / point1.position.W;
	point2.UV = point2.UV / point2.position.W;
	point3.UV = point3.UV / point3.position.W;
	
}

Vector3 Triangle::GetVertexWeight(Vector2& inPoint)
{
	Vector3 Result;

	mVectorW = inPoint - RenderMath::Vector4toVector2(point1.position);

	Result.Y = (RenderMath::DotProduct(mVectorW, mVectorU) * mDotVV
		- RenderMath::DotProduct(mVectorW, mVectorV) * mDotUV) / mWeightDenominator;
	Result.Z = (RenderMath::DotProduct(mVectorW, mVectorV) * mDotUU
		- RenderMath::DotProduct(mVectorW, mVectorU) * mDotUV) / mWeightDenominator;
	Result.X = 1.0f - Result.Y - Result.Z;

	return Result;
}

