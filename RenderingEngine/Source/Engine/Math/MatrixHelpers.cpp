
#include "MatrixHelpers.h"


void MatrixHelpers::MatrixMul(Matrix2x2* outMat, Matrix2x2 inMat)
{
	Matrix2x2 tempMat = *outMat;

	outMat->mat11 = tempMat.mat11 * inMat.mat11 + tempMat.mat12 * inMat.mat21;
	outMat->mat12 = tempMat.mat11 * inMat.mat12 + tempMat.mat12 * inMat.mat22;
	outMat->mat21 = tempMat.mat21 * inMat.mat11 + tempMat.mat22 * inMat.mat21;
	outMat->mat22 = tempMat.mat21 * inMat.mat12 + tempMat.mat22 * inMat.mat22;
}


void MatrixHelpers::MatrixMul(Vector2D* outVector, Matrix2x2 inMat)
{
	Vector2D tempVec = *outVector;

	outVector->X = tempVec.X * inMat.mat11 + tempVec.Y * inMat.mat12;
	outVector->Y = tempVec.X * inMat.mat21 + tempVec.Y * inMat.mat22;
}

Vector2D MatrixHelpers::VectorSum(Vector2D inVector1, Vector2D inVector2)
{
	Vector2D outVector;
	outVector.X = inVector1.X + inVector2.X;
	outVector.Y = inVector1.Y + inVector2.Y;

	return outVector;
}

Vector2D MatrixHelpers::VectorSub(Vector2D inVector1, Vector2D inVector2)
{
	Vector2D outVector;
	outVector.X = inVector1.X - inVector2.X;
	outVector.Y = inVector1.Y - inVector2.Y;

	return outVector;
}

void MatrixHelpers::SortVecticesByY(TriangleVertices* vertices)
{
	if (!(vertices->firstVertex.Y > vertices->secondVertex.Y) && (vertices->firstVertex.Y > vertices->thirdVertex.Y))
	{
		if (vertices->secondVertex.Y > vertices->thirdVertex.Y)
		{
			std::swap(vertices->firstVertex, vertices->secondVertex);
		}
		else
		{
			std::swap(vertices->firstVertex, vertices->thirdVertex);
		}
	}

	if (!vertices->secondVertex.Y > vertices->thirdVertex.Y)
	{
		std::swap(vertices->secondVertex, vertices->thirdVertex);
	}

	return;
}