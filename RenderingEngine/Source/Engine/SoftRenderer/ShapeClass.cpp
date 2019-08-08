
#include "Engine/SoftRenderer/ShapeClass.h"

ShapeClass::ShapeClass()
{
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