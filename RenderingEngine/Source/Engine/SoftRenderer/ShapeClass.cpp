
#include "Engine/SoftRenderer/ShapeClass.h"

ShapeClass::ShapeClass()
{
}

void Triangle::Initialize()
{
	mVectorU = point2.position - point1.position;
	mVectorV = point3.position - point1.position;

	mDotUU = RenderMath::DotProduct(mVectorU, mVectorU);
	mDotUV = RenderMath::DotProduct(mVectorU, mVectorV);

	mWeightDenominator = mDotUU * RenderMath::DotProduct(mVectorV, mVectorV) - mDotUV * mDotUV;
}

Vector3 Triangle::GetVertexWeight(Vector2& inPoint)
{
	Vector3 Result;

	mVectorW = inPoint - point1.position;

	Result.Y = (RenderMath::DotProduct(mVectorW, mVectorU) * RenderMath::DotProduct(mVectorV, mVectorV)
		- RenderMath::DotProduct(mVectorW, mVectorV) * RenderMath::DotProduct(mVectorV, mVectorU)) / mWeightDenominator;
	Result.Z = (RenderMath::DotProduct(mVectorW, mVectorV) * RenderMath::DotProduct(mVectorU, mVectorU)
		- RenderMath::DotProduct(mVectorW, mVectorU) * RenderMath::DotProduct(mVectorV, mVectorU)) / mWeightDenominator;
	Result.X = 1.0f - Result.Y - Result.Z;

	return Result;
}

void Quad::SetQuad(Vertex& point1, Vertex& point2, Vertex& point3, Vertex& point4)
{
	triangle1.point1 = point1;
	triangle1.point2 = point2;
	triangle1.point3 = point4;

	triangle2.point1 = point2;
	triangle2.point2 = point3;
	triangle2.point3 = point4;

	return;
}