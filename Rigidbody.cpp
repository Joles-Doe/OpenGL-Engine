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

std::shared_ptr<Transform> Rigidbody::GetTransform()
{
	return mTransform;
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

bool Rigidbody::IsDynamic()
{
	return mUseDynamicBody;
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

void Rigidbody::AddForce(glm::vec3 _force)
{
	if (mUseDynamicBody)
	{
		mDynamicBody->AddForce(_force);
	}
}

void Rigidbody::Force(glm::vec3 _force)
{
	if (mUseDynamicBody)
	{
		mDynamicBody->Force(_force);
	}
}

glm::vec3 Rigidbody::Force()
{
	glm::vec3 force(0.0f);
	if (mUseDynamicBody)
	{
		force = mDynamicBody->Force();
	}
	return force;
}

void Rigidbody::Velocity(glm::vec3 _vel)
{
	if (mUseDynamicBody)
	{
		mDynamicBody->Velocity(_vel);
	}
	else
	{
		mKinematicBody->Velocity(_vel);
	}
}

glm::vec3 Rigidbody::Velocity()
{
	glm::vec3 vel;
	if (mUseDynamicBody)
	{
		vel = mDynamicBody->Velocity();
	}
	else
	{
		vel = mKinematicBody->Velocity();
	}
	return vel;
}

void Rigidbody::Acceleration(glm::vec3 _accel)
{
	if (mUseDynamicBody)
	{
		mDynamicBody->Acceleration(_accel);
	}
	else
	{
		mKinematicBody->Acceleration(_accel);
	}
}

glm::vec3 Rigidbody::Acceleration()
{
	glm::vec3 accel;
	if (mUseDynamicBody)
	{
		accel = mDynamicBody->Acceleration();
	}
	else
	{
		accel = mKinematicBody->Acceleration();
	}
	return accel;
}

void Rigidbody::Mass(float _mass)
{
	if (mUseDynamicBody)
	{
		mDynamicBody->Mass(_mass);
	}
}

float Rigidbody::Mass()
{
	float mass = 0.0f;
	if (mUseDynamicBody)
	{
		mass = mDynamicBody->Mass();
	}
	return mass;
}

void Rigidbody::Elasticity(float _e)
{
	_e = glm::fclamp(_e, 0.0f, 1.0f);
	if (mUseDynamicBody)
	{
		mDynamicBody->Elasticity(_e);
	}
	else
	{
		mKinematicBody->Elasticity(_e);
	}
}

float Rigidbody::Elasticity()
{
	float elasticity = 0.0f;
	if (mUseDynamicBody)
	{
		elasticity = mDynamicBody->Elasticity();
	}
	else
	{
		elasticity = mKinematicBody->Elasticity();
	}
	return elasticity;
}
