#pragma once

#include <SDL2/SDL.h>

class TimeManager
{
public:
	TimeManager() : mFrameRate(60), mCurrentTime(0), mLastTime(0), mDeltaTime(0) {}

	void Update();
	void Wait();

	float DeltaTime() const;
private:
	int mFrameRate;

	Uint32 mCurrentTime;
	Uint32 mLastTime;

	float mDeltaTime;
};

