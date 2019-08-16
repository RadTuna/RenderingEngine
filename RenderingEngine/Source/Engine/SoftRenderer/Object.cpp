
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

void Object::SetRotation(const float rotation)
{
	mRotation = rotation;
}

void Object::SetScale(const Vector4& scale)
{
	mScale = scale;
}

void Object::SetTransform(const Vector4& location, const float rotation, const Vector4& scale)
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

void Triangle2D::Initialize()
{
	mVectorU = point2.position - point1.position;
	mVectorV = point3.position - point1.position;

	mDotUU = RenderMath::DotProduct(mVectorU, mVectorU);
	mDotUV = RenderMath::DotProduct(mVectorU, mVectorV);
	mDotVV = RenderMath::DotProduct(mVectorV, mVectorV);

	mWeightDenominator = mDotUU * RenderMath::DotProduct(mVectorV, mVectorV) - mDotUV * mDotUV;
}

Vector3 Triangle2D::GetVertexWeight(Vector2& inPoint)
{
	Vector3 Result;

	mVectorW = inPoint - point1.position;

	Result.Y = (RenderMath::DotProduct(mVectorW, mVectorU) * mDotVV
		- RenderMath::DotProduct(mVectorW, mVectorV) * mDotUV) / mWeightDenominator;
	Result.Z = (RenderMath::DotProduct(mVectorW, mVectorV) * mDotUU
		- RenderMath::DotProduct(mVectorW, mVectorU) * mDotUV) / mWeightDenominator;
	Result.X = 1.0f - Result.Y - Result.Z;

	return Result;
}
