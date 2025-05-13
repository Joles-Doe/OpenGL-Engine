#include "Pipe.h"

void Pipe::Start()
{	
	mShaderStore->AddUniform("uTime");
	mTimer = 0.0f;
}

void Pipe::Update()
{
	if (!mFreeze)
	{
		mTransform->Move(glm::vec3(-2.0f * mTimeManager->DeltaTime(), 0.0f, 0.0f));
	}

	mTimer += mTimeManager->DeltaTime();
	if (mTimer > 100.0f)
	{
		mTimer = 0.0f;
	}
	mShaderStore->ChangeUniform("uTime", mTimer);
}