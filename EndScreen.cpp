#include "EndScreen.h"

void EndScreen::Start()
{
	mShaderStore->AddUniform("uMousePos");
	mShaderStore->AddUniform("uRadius");

	mRadius = 1.0f;
	mShaderStore->ChangeUniform("uRadius", mRadius);

	mCanClose = false;
}

void EndScreen::Update()
{
	if (mVISIBLE)
	{
		float mouseNDC_X = (float)mEventManager->GetMousePos().x / 960;
		float mouseNDC_Y = (float)mEventManager->GetMousePos().y / 540;

		mShaderStore->ChangeUniform("uMousePos", glm::vec2(mouseNDC_X, mouseNDC_Y));

		if (mRadius > 0.0f)
		{
			mRadius -= mTimeManager->DeltaTime() * 0.5f;
		}
		if (mRadius <= 0.0f)
		{
			mRadius = 0.0f;
			mCanClose = true;
		}
		mShaderStore->ChangeUniform("uRadius", mRadius);
	}
}

void EndScreen::OnClick()
{
	if (mCanClose)
	{
		mGameState->SetExit(true);
	}
}
