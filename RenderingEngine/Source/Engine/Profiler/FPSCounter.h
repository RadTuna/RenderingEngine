#pragma once

#include <windows.h>


class FPSCounter
{
public:

	FPSCounter();
	~FPSCounter();

	bool Initialize();
	void Frame();

private:

	__int64 mFrequency;
	__int64 mStartTime;
	float mTickPerMs;
	float mFrameTime;
	int mFramePerSecond;
	int mCount;

public:

	inline int GetFPS() { return mFramePerSecond; }

};