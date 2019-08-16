#pragma once


#include "Engine/Engine.h"


class ViewCamera
{
public:

	ViewCamera();
	~ViewCamera();

	bool Initialize();
	void Release();
	void SetLocation(struct Vector4& location);
	void SetRotation(struct Vector4& rotation);
	void CalculrateViewMatrix();
	void CalcularateProjectionMatrix(float fov, float screenWidth, float screenHeight, float nearDistance, float farDistance);

private:

	struct Matrix4x4* mViewMatrix;
	struct Matrix4x4* mProjectionMatrix;
	float mLocationX;
	float mLocationY;
	float mLocationZ;
	float mRotationX;
	float mRotationY;
	float mRotationZ;

public:

	inline Matrix4x4& GetViewMatrix() const { return *mViewMatrix; }
	inline Matrix4x4& GetProjectionMatrix() const { return *mProjectionMatrix; }

};
