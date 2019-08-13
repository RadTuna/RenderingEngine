

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

void ViewCamera::SetLocation(Vector3& location)
{
	mLocationX = location.X;
	mLocationY = location.Y;
}

void ViewCamera::SetRotation(float rotation)
{
	mRotation = rotation;
}

void ViewCamera::CalculrateViewMatrix()
{
	Vector3 location = RenderMath::Vector3Set(mLocationX, mLocationY, 0.0f);
	Matrix3x3 rotationMatrix = RenderMath::GetRotationMatrix3x3(mRotation);
	Matrix3x3 locationMatrix = RenderMath::GetLocationMatrix3x3(location);

	RenderMath::MatrixMul(&rotationMatrix, locationMatrix);

	*mViewMatrix = rotationMatrix;
}

