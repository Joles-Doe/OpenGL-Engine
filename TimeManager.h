#pragma once

#include <SDL2/SDL.h>

/// <summary>
/// Time Manager - uses SDL to handle time used throughout the engine
/// <para> 
/// Calculates DeltaTime, and Delays program execution until next frame.
/// </para>
/// </summary>
class TimeManager
{
public:
	TimeManager() : mFrameRate(60), mCurrentTime(0), mLastTime(0), mDeltaTime(0) {}

	/// <summary>
	/// Update function called by the Window once per frame, to calculate DeltaTime.
	/// </summary>
	void Update();

	/// <summary>
	/// Wait function called by the Window at the end of it's execution cycle. Used to wait until the next frame, before resuming the execution cycle.
	/// </summary>
	void Wait();

	float DeltaTime() const noexcept { return mDeltaTime; };
private:
	int mFrameRate;

	Uint32 mCurrentTime;
	Uint32 mLastTime;

	float mDeltaTime;
};

