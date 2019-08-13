#pragma once


#include "Engine/Engine.h"


class ViewCamera
{
public:

	ViewCamera();
	~ViewCamera();

	bool Initialize();
	void Release();
	void SetLocation(struct Vector3& location);
	void SetRotation(float rotation);
	void CalculrateViewMatrix();

private:

	struct Matrix3x3* mViewMatrix;
	float mLocationX;
	float mLocationY;
	float mRotation;

public:

	inline Matrix3x3& GetViewMatrix() const { return *mViewMatrix; }

};
