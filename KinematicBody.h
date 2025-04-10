#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Transform.h"

class KinematicBody
{
public:
	KinematicBody(std::shared_ptr<Transform> _transform);

	void Update(float _deltaTime);

	void Velocity(glm::vec3 _vel);
	glm::vec3 Velocity();

	void Acceleration(glm::vec3 _accel);
	glm::vec3 Acceleration();

	void Elasticity(float _e);
	float Elasticity();

private:
	std::shared_ptr<Transform> mTransform;

	glm::vec3 mVelocity;
	glm::vec3 mAcceleration;
	float mElasticity;
};

