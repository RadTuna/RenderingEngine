

#include "Engine/SoftRenderer/ViewCamera.h"
#include "Engine/Math/RenderMath.h"


ViewCamera::ViewCamera()
{
	mViewMatrix = nullptr;
	mLocationX = 0.0f;
	mLocationY = 0.0f;
	mLocationZ = 0.0f;
	mRotationX = 0.0f;
	mRotationY = 0.0f;
	mRotationZ = 0.0f;
}

ViewCamera::~ViewCamera()
{
	if (mProjectionMatrix != nullptr)
	{
		delete mProjectionMatrix;
		mProjectionMatrix = nullptr;
	}

	if (mViewMatrix != nullptr)
	{
		delete mViewMatrix;
		mViewMatrix = nullptr;
	}
}

bool ViewCamera::Initialize()
{
	mViewMatrix = new struct Matrix4x4;
	if (mViewMatrix == nullptr)
	{
		return false;
	}

	mProjectionMatrix = new struct Matrix4x4;
	if (mProjectionMatrix == nullptr)
	{
		delete mViewMatrix;
		mViewMatrix = nullptr;
		return false;
	}

	return true;
}

void ViewCamera::Release()
{
	if (mProjectionMatrix != nullptr)
	{
		delete mProjectionMatrix;
		mProjectionMatrix = nullptr;
	}

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
	Vector4 lookVector = RenderMath::Vector4Set(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4 upVector = RenderMath::Vector4Set(0.0f, 1.0f, 0.0f, 0.0f);

	Matrix4x4 rotationMatrix = RenderMath::GetRotationMatrix4x4(RenderMath::Vector4Set(-mRotationX, -mRotationY, -mRotationZ, 0.0f));

	Vector4 xVector = lookVector - position;
	RenderMath::MatrixMul(&xVector, rotationMatrix);
	RenderMath::MatrixMul(&upVector, rotationMatrix);
	RenderMath::Normalize(&xVector);

	Vector4 zVector = RenderMath::CrossProduct(xVector, upVector);
	RenderMath::Normalize(&zVector);

	Vector4 yVector = RenderMath::CrossProduct(xVector, zVector);
	RenderMath::Normalize(&yVector);

	*mViewMatrix = {
		xVector.X, yVector.X, zVector.X, 0.0f,
		xVector.Y, yVector.Y, zVector.Y, 0.0f,
		xVector.Z, yVector.Z, zVector.Z, 0.0f,
		position.X, position.Y, position.Z, 1.0f };

	return;
}

void ViewCamera::CalcularateProjectionMatrix(float fov, float screenWidth, float screenHeight, float nearDistance, float farDistance)
{
	fov = fov / RenderMath::GetConvertRadianValue();

	float screenAspect = screenWidth / screenHeight;

	float height = 1.0f / std::tanf(fov / 2.0f);
	float width = height / screenAspect;

	float zScale = farDistance / (farDistance - nearDistance);
	float zMove = -nearDistance * zScale;

	float zDenominator = farDistance - zMove;
	zScale /= zDenominator;
	zMove /= zDenominator;

	*mProjectionMatrix = {
		width, 0.0f, 0.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f,
		0.0f, 0.0f, zScale, 1.0f,
		0.0f, 0.0f, zMove, 0.0f };

	return;
}

