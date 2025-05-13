#include "Player.h"

void Player::Start()
{
	mFreeze = false;
	mCanJump = false;

	mFirstUnfroze = true;
	mDead = false;

	mRigidbody->Elasticity(0.0f);
}

void Player::Update()
{
	if (!mFreeze)
	{
		if (mRigidbody->Acceleration().y == 0.0f)
		{
			mRigidbody->Acceleration(glm::vec3(0.0f, -20.0f, 0.0f));
		}
		
		if (mEventManager->GetMouseDown("1") && mCanJump)
		{
			mRigidbody->Velocity(glm::vec3(0.0f, 8.0f, 0.0f));
		}

		// If player clips out of bounds, automatically end game
		if (mTransform->Position().y < -100.0f)
		{
			mDead = true;
		}
	}
	else
	{
		if (mRigidbody->Acceleration().y != 0.0f)
		{
			mRigidbody->Acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
			mRigidbody->Velocity(glm::vec3(0.0f));
		}
	}
}

void Player::OnCollisionEnter(std::shared_ptr<Rigidbody> _other)
{
	//Attempt to typecast other object into a pipe
	std::weak_ptr<GameObject> obj = _other->GetGameObject();
	std::shared_ptr<GameObject> objLocked = obj.lock();
	std::shared_ptr<Pipe> pipe = std::dynamic_pointer_cast<Pipe>(objLocked);

	// If typecast succeeds, player has collided with a pipe
	if (pipe)
	{
		mDead = true;
		mFreeze = true;
	}
}