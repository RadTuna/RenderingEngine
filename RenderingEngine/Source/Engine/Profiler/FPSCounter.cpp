
#include "Engine/Profiler/FPSCounter.h"


FPSCounter::FPSCounter()
{
}

FPSCounter::~FPSCounter()
{
}

bool FPSCounter::Initialize()
{
	// 현재 시스템이 QueryPerformanceCounter를 지원하는 지 확인
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
	if (mFrequency == 0)
	{
		return false;
	}

	mTickPerMs = static_cast<float>(mFrequency / 1000);

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mStartTime));

	return true;
}

void FPSCounter::Frame()
{
	__int64 CurrentTime;

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentTime));

	mCount++;

	if (CurrentTime >= mStartTime + mFrequency)
	{
		mFramePerSecond = mCount;
		mCount = 0;

		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mStartTime));
	}
}