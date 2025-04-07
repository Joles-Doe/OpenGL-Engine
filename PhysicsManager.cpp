#include "PhysicsManager.h"

#include <iostream>

PhysicsManager::PhysicsManager(std::shared_ptr<TimeManager> _time)
{
	mTimeManager = _time;
}

void PhysicsManager::Update()
{
	//implement spatial partitioning, eventually

	//Iterate through every pair to check for collision
	if (mRigidbodies.size() > 1)
	{
		for (int i = 0; i < mRigidbodies.size() - 1; i++)
		{
			for (int x = i + 1; x < mRigidbodies.size(); x++)
			{
				// If pair is colliding
				if (mRigidbodies[i]->GetCollider()->IsColliding(mRigidbodies[x]->GetCollider()))
				{
					// implement collision physics here


					// For each rigidbody, check if they've already collided, and call the appropriate Gameobject Collision function if they have
					if (mRigidbodies[i]->RigidbodyAlreadyCollided(mRigidbodies[x]))
					{
						mRigidbodies[i]->GetParent()->OnCollisionStay(mRigidbodies[x]);
					}
					else
					{
						mRigidbodies[i]->AddCollidedRigidbody(mRigidbodies[x]);
						mRigidbodies[i]->GetParent()->OnCollisionEnter(mRigidbodies[x]);
					}

					if (mRigidbodies[x]->RigidbodyAlreadyCollided(mRigidbodies[i]))
					{
						mRigidbodies[x]->GetParent()->OnCollisionStay(mRigidbodies[i]);
					}
					else
					{
						mRigidbodies[x]->AddCollidedRigidbody(mRigidbodies[i]);
						mRigidbodies[x]->GetParent()->OnCollisionEnter(mRigidbodies[i]);
					}
				}
				else
				{
					if (mRigidbodies[i]->RigidbodyAlreadyCollided(mRigidbodies[x]))
					{
						mRigidbodies[i]->RemoveCollidedRigidbody(mRigidbodies[x]);
						mRigidbodies[i]->GetParent()->OnCollisionExit(mRigidbodies[x]);
					}

					if (mRigidbodies[x]->RigidbodyAlreadyCollided(mRigidbodies[i]))
					{
						mRigidbodies[x]->RemoveCollidedRigidbody(mRigidbodies[i]);
						mRigidbodies[x]->GetParent()->OnCollisionExit(mRigidbodies[i]);
					}
				}
			}
		}
	}

	for (int i = 0; i < mRigidbodies.size(); i++)
	{
		mRigidbodies[i]->Update(mTimeManager->DeltaTime());
	}
}

void PhysicsManager::Add(std::shared_ptr<Rigidbody> _rb)
{
	mRigidbodies.push_back(_rb);
}