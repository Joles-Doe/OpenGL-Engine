#include "TimeManager.h"

void TimeManager::Update()
{
	mCurrentTime = SDL_GetTicks();
	mDeltaTime = (mCurrentTime - mLastTime) / 1000.0f;
	mLastTime = mCurrentTime;
}

void TimeManager::Wait()
{
	Uint32 endTime = SDL_GetTicks() - mCurrentTime;

	if (endTime < 1000 / mFrameRate)
	{
		SDL_Delay(static_cast<Uint32>((1000 / mFrameRate) - endTime));
	}
}

float TimeManager::DeltaTime() const
{
	return mDeltaTime;
}
