#include "TitleTextBG.h"

void TitleTextBG::Start()
{
	mShaderStore->AddUniform("uMousePos");
	mShaderStore->AddUniform("uRadius");

	mOpen = false;

	mRadius = 0.1f;
	mShaderStore->ChangeUniform("uRadius", mRadius);
}

void TitleTextBG::Update()
{
	if (!mOpen)
	{
		float mouseNDC_X = (float)mEventManager->GetMousePos().x / 960;
		float mouseNDC_Y = (float)mEventManager->GetMousePos().y / 540;

		mShaderStore->ChangeUniform("uMousePos", glm::vec2(mouseNDC_X, mouseNDC_Y));
	}
	else
	{
		mRadius += mTimeManager->DeltaTime() * 0.5f;
		mShaderStore->ChangeUniform("uRadius", mRadius);

		if (mRadius >= 1.5f)
		{
			mKILL = true;
		}
	}
}

void TitleTextBG::OnClick()
{
	mOpen = true;
}