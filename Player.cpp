#include "Player.h"

void Player::Start()
{
	mFreeze = true;
	mFirstUnfroze = true;
	mCanJump = false;
	mDead = false;

	mRigidbody->Elasticity(0.0f);
}

void Player::Update()
{
	if (!mFreeze)
	{
		if (mRigidbody->Acceleration().y == 0.0f)
		{
			mRigidbody->Acceleration(glm::vec3(0.0f, -9.8f, 0.0f));
		}

		if (mEventManager->GetMouseDown("1") && mCanJump)
		{
			mRigidbody->AddForce(glm::vec3(0.0f, 4.0f, 0.0f));
		}
	}
	else
	{
		if (mRigidbody->Acceleration().y != 0.0f)
		{
			mRigidbody->Acceleration(glm::vec3(0.0f, -9.8f, 0.0f));
		}
	}
}

void Player::OnCollisionEnter(std::shared_ptr<Rigidbody> _other)
{
	// Attempt to typecast other object into a pipe
	std::weak_ptr<GameObject> obj = _other->GetGameObject();
	std::shared_ptr<Pipe> pipe = std::dynamic_pointer_cast<Pipe>(std::make_shared<GameObject>(obj.lock()));

	// If typecast succeeds, player has collided with a pipe
	if (pipe)
	{
		mDead = true;
		mFreeze = true;
	}
}