#include "GameManager.h"

void GameManager::Start()
{
	mStartGame = false;
	mEndGame = false;
	mPlayerOnScreen = false;
	mBorderMoved = false;
	mTimer = 5.0f;
}

void GameManager::Update()
{
	if (!mStartBG.expired())
	{
		// Check if the background is gone before starting
		if (mStartBG.lock()->IsKill())
		{
			mStartGame = true;
		}
	}
	else
	{
		mStartGame = true;
	}

	if (mStartGame)
	{
		if (!mPlayer->GetJump())
		{
			mPlayerOnScreen = (mPlayer->GetTransform()->Position().y < 5.0f);
		}
		if (!mPlayerOnScreen)
		{
			if (!mBorderMoved)
			{
				mBorderMoved = !mBorderMoved;
				mTopBorder->GetTransform()->Move(glm::vec3(-100.0f, 0.0f, 0.0f));
			}
		}
		else
		{
			// If the top border has moved, move it back
			if (mBorderMoved)
			{
				mBorderMoved = !mBorderMoved;
				mTopBorder->GetTransform()->Move(glm::vec3(100.0f, 0.0f, 0.0f));
			}
			mPlayer->SetFreeze(false);
			mPlayer->SetJump(true);

			mTimer += mTimeManager->DeltaTime();
			if (mTimer > 4.0f)
			{
				mTimer = 0.0f;
				mPipeSpawner->SpawnPipe();
			}

			if (mPlayer->GetDead())
			{
				mPlayer->SetFreeze(true);
				mPipeSpawner->FreezePipes();
				mStartGame = false;
				mEndGame = true;
			}
		}
	}
	if (mEndGame)
	{
		mEndScreen->SetVisible(true);
	}
}