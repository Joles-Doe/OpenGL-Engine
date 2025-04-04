#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"

#include "Collider.h"
#include "Transform.h"
#include "DynamicBody.h"
#include "KinematicBody.h"

class Rigidbody
{
public:
	Rigidbody(std::shared_ptr<Collider> _collider, RBTYPE _bodyType, std::shared_ptr<Transform> _transform);

	void Update(float _deltaTime);

	void AddForce(glm::vec3 _force);
private:
	std::shared_ptr<Collider> mCollider;
	std::shared_ptr<Transform> mTransform;

	std::shared_ptr<DynamicBody> mDynamicBody;
	std::shared_ptr<KinematicBody> mKinematicBody;
	bool mUseDynamicBody;
};

