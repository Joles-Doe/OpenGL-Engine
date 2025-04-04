#include "Rigidbody.h"

Rigidbody::Rigidbody(std::shared_ptr<Collider> _collider, RBTYPE _bodyType, std::shared_ptr<Transform> _transform)
{
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
}
