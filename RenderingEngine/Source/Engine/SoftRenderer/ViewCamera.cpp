

#include "Engine/SoftRenderer/ViewCamera.h"
#include "Engine/Math/RenderMath.h"


ViewCamera::ViewCamera()
{
	mViewMatrix = nullptr;
	mLocationX = 0.0f;
	mLocationY = 0.0f;
	mRotation = 0.0f;
}

ViewCamera::~ViewCamera()
{
	if (mViewMatrix != nullptr)
	{
		delete mViewMatrix;
		mViewMatrix = nullptr;
	}
}

bool ViewCamera::Initialize()
{
	mViewMatrix = new struct Matrix3x3;
	if (mViewMatrix == nullptr)
	{
		return false;
	}

	return true;
}

void ViewCamera::Release()
{
	if (mViewMatrix != nullptr)
	{
		delete mViewMatrix;
		mViewMatrix = nullptr;
	}
}

void ViewCamera::SetLocation(Vector4& location)
{
	mLocationX = location.X;
	mLocationY = location.Y;
	mLocationZ = location.Z;
}

void ViewCamera::SetRotation(Vector4& rotation)
{
	mRotationX = rotation.X;
	mRotationY = rotation.Y;
	mRotationZ = rotation.Z;
}

void ViewCamera::CalculrateViewMatrix()
{
	Vector4 position = RenderMath::Vector4Set(-mLocationX, -mLocationY, -mLocationZ, 1.0f);
	Vector4 lookVector = RenderMath::Vector4Set(0.0f, 0.0f, 1.0f, 0.0f);
	Vector4 upVector = RenderMath::Vector4Set(0.0f, 1.0f, 0.0f, 0.0f);

	Matrix4x4 rotationMatrix = RenderMath::GetRotationMatrix4x4(RenderMath::Vector4Set(-mRotationX, -mRotationY, -mRotationZ, 0.0f));

	RenderMath::MatrixMul(&lookVector, rotationMatrix);
	RenderMath::MatrixMul(&upVector, rotationMatrix);

	Vector4 xVector = lookVector - position;
	RenderMath::Normalize(&xVector);

	Vector4 zVector = RenderMath::CrossProduct(xVector, upVector);
	RenderMath::Normalize(&zVector);

	Vector4 yVector = RenderMath::CrossProduct(xVector, zVector);
	RenderMath::Normalize(&yVector);

	*mViewMatrix = {
		xVector.X, yVector.X, zVector.X, 0.0f,
		xVector.Y, yVector.Y, zVector.Y, 0.0f,
		xVector.Z, yVector.Z, zVector.Z, 0.0f,
		RenderMath::DotProduct(position, xVector), RenderMath::DotProduct(position, yVector), RenderMath::DotProduct(position, zVector), 1.0f };
}

void ViewCamera::CalcularateProjectionMatrix(float screenWidth, float screenHeight, float nearDistance, float farDistance)
{
	float screenAspect = screenWidth / screenHeight;
}

