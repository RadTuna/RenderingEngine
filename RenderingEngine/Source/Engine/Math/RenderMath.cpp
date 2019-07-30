
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


void RenderMath::MatrixMul(Vector2D* outVector, Matrix2x2 inMat)
{
	Vector2D tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat12;
	outVector->Y = tempVec.X * inMat.mat21 + tempVec.Y * inMat.mat22;
}

Vector2D RenderMath::VectorSum(Vector2D inVector1, Vector2D inVector2)
{
	Vector2D outVector;
	outVector.X = inVector1.X + inVector2.X;
	outVector.Y = inVector1.Y + inVector2.Y;

	return outVector;
}

Vector2D RenderMath::VectorSub(Vector2D inVector1, Vector2D inVector2)
{
	Vector2D outVector;
	outVector.X = inVector1.X - inVector2.X;
	outVector.Y = inVector1.Y - inVector2.Y;

	return outVector;
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

Vector2D RenderMath::Vector2DSet(float x, float y)
{
	Vector2D Temp = { x, y };
	return Temp;
}