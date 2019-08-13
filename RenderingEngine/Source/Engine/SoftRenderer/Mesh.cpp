
#include "Engine/SoftRenderer/Mesh.h"

Mesh::Mesh()
{
	mTriangleList = nullptr;
	mVerticesCount = 0;
}

Mesh::~Mesh()
{
	if (mTriangleList != nullptr)
	{
		delete[] mTriangleList;
		mTriangleList = nullptr;
	}
}

bool Mesh::Initialize(Triangle* triangleList, int verticesCount)
{
	mTriangleList = new Triangle[verticesCount];
	if (mTriangleList == nullptr)
	{
		return false;
	}

	for (int i = 0; i < verticesCount; ++i)
	{
		mTriangleList[i] = triangleList[i];
	}

	mVerticesCount = verticesCount;

	return true;
}

void Mesh::Release()
{
	if (mTriangleList != nullptr)
	{
		delete[] mTriangleList;
		mTriangleList = nullptr;
	}
}

void Mesh::SetLocation(const Vector3& location)
{
	mLocation = location;
}

void Mesh::SetRotation(const float rotation)
{
	mRotation = rotation;
}

void Mesh::SetScale(const Vector3& scale)
{
	mScale = scale;
}

void Mesh::SetTransform(const Vector3& location, const float rotation, const Vector3& scale)
{
	SetLocation(location);
	SetRotation(rotation);
	SetScale(scale);
}

void Triangle::Initialize()
{
	mVectorU = point2.position - point1.position;
	mVectorV = point3.position - point1.position;

	mDotUU = RenderMath::HomoDotProduct(mVectorU, mVectorU);
	mDotUV = RenderMath::HomoDotProduct(mVectorU, mVectorV);
	mDotVV = RenderMath::HomoDotProduct(mVectorV, mVectorV);

	mWeightDenominator = mDotUU * RenderMath::HomoDotProduct(mVectorV, mVectorV) - mDotUV * mDotUV;
}

Vector3 Triangle::GetVertexWeight(Vector3& inPoint)
{
	Vector3 Result;

	mVectorW = inPoint - point1.position;

	Result.Y = (RenderMath::HomoDotProduct(mVectorW, mVectorU) * mDotVV
		- RenderMath::HomoDotProduct(mVectorW, mVectorV) * mDotUV) / mWeightDenominator;
	Result.Z = (RenderMath::HomoDotProduct(mVectorW, mVectorV) * mDotUU
		- RenderMath::HomoDotProduct(mVectorW, mVectorU) * mDotUV) / mWeightDenominator;
	Result.X = 1.0f - Result.Y - Result.Z;

	return Result;
}
