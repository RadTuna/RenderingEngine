
#include "Engine/Profiler/FPSCounter.h"


FPSCounter::FPSCounter()
{
	mFrequency = 0;
	mStartTime = 0;
	mTickPerMs = 0.0f;
	mFrameTime = 0.0f;
	mFramePerSecond = 0;
	mCount = 0;
}

FPSCounter::~FPSCounter()
{
}

bool FPSCounter::Initialize()
{
	// ���� �ý����� QueryPerformanceCounter�� �����ϴ� �� Ȯ��
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