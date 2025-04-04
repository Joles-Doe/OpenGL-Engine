#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(std::shared_ptr<TimeManager> _time)
{
	mTimeManager = _time;
}

void PhysicsManager::Update()
{
	for (int i = 0; i < mRigidbodies.size(); i++)
	{
		mRigidbodies[i]->Update(mTimeManager->DeltaTime());
	}
}

void PhysicsManager::Add(std::shared_ptr<Rigidbody> _rb)
{
	mRigidbodies.push_back(_rb);
}