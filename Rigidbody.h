#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"

#include "Collider.h"
#include "Transform.h"
#include "DynamicBody.h"
#include "KinematicBody.h"

class GameObject;

class Rigidbody
{
public:
	Rigidbody(std::shared_ptr<GameObject> _parent, std::shared_ptr<Collider> _collider, RBTYPE _bodyType, std::shared_ptr<Transform> _transform);
	std::shared_ptr<GameObject> GetParent();
	std::shared_ptr<Transform> GetTransform();
	std::shared_ptr<Collider> GetCollider();

	bool RigidbodyAlreadyCollided(std::shared_ptr<Rigidbody> _other);
	void AddCollidedRigidbody(std::shared_ptr<Rigidbody> _other);
	void RemoveCollidedRigidbody(std::shared_ptr<Rigidbody> _other);

	bool IsDynamic();

	void Update(float _deltaTime);

	void AddForce(glm::vec3 _force);

	void Force(glm::vec3 _force);
	glm::vec3 Force();

	void Velocity(glm::vec3 _vel);
	glm::vec3 Velocity();

	void Acceleration(glm::vec3 _accel);
	glm::vec3 Acceleration();

	void Mass(float _mass);
	float Mass();
private:
	std::shared_ptr<GameObject> mParent;
	std::shared_ptr<Collider> mCollider;
	std::shared_ptr<Transform> mTransform;

	std::shared_ptr<DynamicBody> mDynamicBody;
	std::shared_ptr<KinematicBody> mKinematicBody;
	bool mUseDynamicBody;

	std::vector<std::shared_ptr<Rigidbody>> mCurrentlyCollidingRigidbodies;
};

