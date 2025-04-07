#include "Rigidbody.h"
#include "GameObject.h"

Rigidbody::Rigidbody(std::shared_ptr<GameObject> _parent, std::shared_ptr<Collider> _collider, RBTYPE _bodyType, std::shared_ptr<Transform> _transform)
{
	mParent = _parent;
	mCollider = _collider;

	switch (_bodyType)
	{
	case DYNAMIC:
		mDynamicBody = std::make_shared<DynamicBody>(_transform);
		mUseDynamicBody = true;
		break;
	case KINEMATIC:
		mKinematicBody = std::make_shared<KinematicBody>(_transform);
		mUseDynamicBody = false;
		break;
	}
	mTransform = _transform;
}

std::shared_ptr<GameObject> Rigidbody::GetParent()
{
	return mParent;
}

std::shared_ptr<Collider> Rigidbody::GetCollider()
{
	return mCollider;
}

bool Rigidbody::RigidbodyAlreadyCollided(std::shared_ptr<Rigidbody> _other)
{
	bool alreadyCollided = false;
	for (int x = 0; x < mCurrentlyCollidingRigidbodies.size(); x++)
	{
		if (mCurrentlyCollidingRigidbodies[x] == _other)
		{
			alreadyCollided = true;
			break;
		}
	}
	return alreadyCollided;
}

void Rigidbody::AddCollidedRigidbody(std::shared_ptr<Rigidbody> _other)
{
	mCurrentlyCollidingRigidbodies.push_back(_other);
}

void Rigidbody::RemoveCollidedRigidbody(std::shared_ptr<Rigidbody> _other)
{
	for (int x = 0; x < mCurrentlyCollidingRigidbodies.size(); x++)
	{
		if (mCurrentlyCollidingRigidbodies[x] == _other)
		{
			mCurrentlyCollidingRigidbodies.erase(mCurrentlyCollidingRigidbodies.begin() + x);
			break;
		}
	}
}

void Rigidbody::Update(float _deltaTime)
{
	switch (mUseDynamicBody)
	{
	case true:
		mDynamicBody->Update(_deltaTime);
		break;
	case false:
		mKinematicBody->Update(_deltaTime);
		break;
	}
	mCollider->Update();
}
