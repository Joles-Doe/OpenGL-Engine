#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"
#include "Transform.h"

class DynamicBody
{
public:
	DynamicBody(std::shared_ptr<Transform> _transform);

	void Update(float _deltaTime);

	void ChangeIntegration(RBINTEGRATION _mode);

	void AddForce(glm::vec3 _force);
	//void ClearForces();

	void Force(glm::vec3 _force);
	glm::vec3 Force();

	void Velocity(glm::vec3 _vel);
	glm::vec3 Velocity();

	void Acceleration(glm::vec3 _accel);
	glm::vec3 Acceleration();

	void Mass(float _mass);
	float Mass();
private:
	std::shared_ptr<Transform> mTransform;

	RBINTEGRATION mIntegration;
	void IntegrationEuler(float _deltaTime);
	void IntegrationRK2(float _deltaTime);
	void IntegrationRK4(float _deltaTime);
	void IntegrationVerlet(float _deltaTime);

	glm::vec3 mForce;
	glm::vec3 mVelocity;
	glm::vec3 mAcceleration;
	glm::vec3 mPreviousPosition;
	float mMass;
};