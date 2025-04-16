#include "BallSpawner.h"

#include <iostream>

void BallSpawner::Start()
{
	mSpawnTimer = 1.0f;
	mSpawnDelay = 0.5f;
	mSpawnBall = false;

	mMoveLeft = false;
}

void BallSpawner::Update()
{
	if (mEventManager->GetKeyDown("space") && mSpawnTimer >= mSpawnDelay)
	{
		mSpawnBall = true;
		mSpawnTimer = 0.0f;
	}
	mSpawnTimer += mTimeManager->DeltaTime();

	if (mMoveLeft)
	{
		mTransform->Position(mTransform->Position() + glm::vec3(-2 * mTimeManager->DeltaTime(), 0.0f, 0.0f));
		if (mTransform->Position().x <= -8.0f)
		{
			mMoveLeft = false;
		}
	}
	else
	{
		mTransform->Position(mTransform->Position() + glm::vec3(2 * mTimeManager->DeltaTime(), 0.0f, 0.0f));
		if (mTransform->Position().x >= 8.0f)
		{
			mMoveLeft = true;
		}
	}
}

bool BallSpawner::GetSpawnBall()
{
	return mSpawnBall;
}

void BallSpawner::SetSpawnBall(bool _spawn)
{
	mSpawnBall = _spawn;
}

bool BallSpawner::GetMoveLeft()
{
	return mMoveLeft;
}
