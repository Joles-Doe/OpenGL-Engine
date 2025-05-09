#include "Background.h"

void Background::Start()
{
	mShaderStore->AddUniform("uTime");
	mTimer = 1.0f;
}

void Background::Update()
{
	mTimer += mTimeManager->DeltaTime();
	if (mTimer > 100.0)
	{
		mTimer = 1.0f;
	}

	mShaderStore->ChangeUniform("uTime", mTimer);
}