#include "Pipe.h"

void Pipe::Update()
{
	if (!mFreeze)
	{
		mTransform->Move(glm::vec3(-2.0f * mTimeManager->DeltaTime(), 0.0f, 0.0f));
	}
}