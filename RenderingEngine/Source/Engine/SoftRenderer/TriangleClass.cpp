
#include "TriangleClass.h"


TriangleClass::TriangleClass()
{
}

TriangleClass::~TriangleClass()
{
}

Vector3 TriangleClass::GetVertexWeight(Vector2& inPoint)
{
	Vector3 Result;

	float TotalArea = RenderMath::GetTriangleArea(
		RenderMath::GetVectorLength(point2.position - point1.position),
		RenderMath::GetVectorLength(point3.position - point1.position),
		std::acosf(RenderMath::Clamp<float>(RenderMath::DotProduct(RenderMath::Normalize(point2.position - point1.position), RenderMath::Normalize(point3.position - point1.position)), -1.0f, 1.0f)));
	
	float point1Weight = RenderMath::GetTriangleArea(
		RenderMath::GetVectorLength(point2.position - inPoint),
		RenderMath::GetVectorLength(point3.position - inPoint),
		std::acosf(RenderMath::Clamp<float>(RenderMath::DotProduct(RenderMath::Normalize(point2.position - inPoint), RenderMath::Normalize(point3.position - inPoint)), -1.0f, 1.0f)));
	float point2Weight = RenderMath::GetTriangleArea(
		RenderMath::GetVectorLength(point1.position - inPoint),
		RenderMath::GetVectorLength(point3.position - inPoint),
		std::acosf(RenderMath::Clamp<float>(RenderMath::DotProduct(RenderMath::Normalize(point1.position - inPoint), RenderMath::Normalize(point3.position - inPoint)), -1.0f, 1.0f)));
	float point3Weight = RenderMath::GetTriangleArea(
		RenderMath::GetVectorLength(point1.position - inPoint),
		RenderMath::GetVectorLength(point2.position - inPoint),
		std::acosf(RenderMath::Clamp<float>(RenderMath::DotProduct(RenderMath::Normalize(point1.position - inPoint), RenderMath::Normalize(point2.position - inPoint)), -1.0f, 1.0f)));

	Result.X = point1Weight / TotalArea;
	Result.Y = point2Weight / TotalArea;
	Result.Z = point3Weight / TotalArea;

	return Result;
}