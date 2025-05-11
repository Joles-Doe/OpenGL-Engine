#include "PipeSpawner.h"

void PipeSpawner::SpawnPipe()
{
	float randY = 1 + rand() % 15;

	std::shared_ptr<Pipe> pipeTop = std::make_shared<Pipe>(CUBE);
	pipeTop->GetTransform()->Position(glm::vec3(25.0f, randY, -12.0f)); // max top 15 with 17 y scale (gap of 24)
	pipeTop->GetTransform()->Scale(glm::vec3(2.0f, 17.0f, 2.0f)); // min bottom 1 with 17 y scale

	pipeTop->AttachTimeManager(mWindow->GetTimeManager());
	pipeTop->AttachShaderManager(mWindow->GetShaderManager());
	pipeTop->UseCustomShader("DISTANCE", "./data/shaders/DistanceHeat");

	pipeTop->CreateCollider(CUBE);
	pipeTop->CreateRigidbody(KINEMATIC);

	pipeTop->SetFreeze(false);

	std::shared_ptr<Pipe> pipeBottom = std::make_shared<Pipe>(CUBE);
	pipeBottom->GetTransform()->Position(glm::vec3(25.0f, pipeTop->GetTransform()->Position().y - 24, -12.0f)); // max top -9 with 17 y scale
	pipeBottom->GetTransform()->Scale(glm::vec3(2.0f, 17.0f, 2.0f));

	pipeBottom->AttachTimeManager(mWindow->GetTimeManager());
	pipeBottom->AttachShaderManager(mWindow->GetShaderManager());
	pipeBottom->UseCustomShader("DISTANCE", "./data/shaders/DistanceHeat");

	pipeBottom->CreateCollider(CUBE);
	pipeBottom->CreateRigidbody(KINEMATIC);

	pipeBottom->SetFreeze(false);

	mPipes.push_back(pipeTop);
	mWindow->AddObject(pipeTop);
	mWindow->EnableRigidbody(pipeTop->GetRigidbody());

	mPipes.push_back(pipeBottom);
	mWindow->AddObject(pipeBottom);
	mWindow->EnableRigidbody(pipeBottom->GetRigidbody());
}

void PipeSpawner::Update()
{
	CullPipes();
}

void PipeSpawner::FreezePipes()
{
	for (int i = 0; i < mPipes.size(); i++)
	{
		mPipes[i]->SetFreeze(true);
	}
}

void PipeSpawner::CullPipes()
{
	mPipes.erase(
		std::remove_if(mPipes.begin(), mPipes.end(),
			[](const std::shared_ptr<Pipe>& obj)
			{
				return obj->GetTransform()->Position().x < -25.0f;
			}),
			mPipes.end());
}