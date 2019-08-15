#pragma once

#include <windows.h>


class TimeCounter
{
public:

	TimeCounter();
	~TimeCounter();

	bool Initialize();
	void Frame();

private:

	__int64 mFrequency;
	__int64 mStartTime;
	float mTickPerMs;
	float mFrameTime;
	float mFramePerSecond;

public:

	inline float GetFPS() { return mFramePerSecond; }
	inline float GetDeltaTime() { return mFrameTime; }

};