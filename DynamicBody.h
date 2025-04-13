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

	glm::vec3 Update(float _deltaTime, glm::vec3 _rot);

	void ChangeIntegration(RBINTEGRATION _mode);

	void AddForce(glm::vec3 _force);

	void Force(glm::vec3 _force);
	glm::vec3 Force();

	void Velocity(glm::vec3 _vel);
	glm::vec3 Velocity();

	void AngularVelocity(glm::vec3 _vel);
	glm::vec3 AngularVelocity();

	void Acceleration(glm::vec3 _accel);
	glm::vec3 Acceleration();

	void Mass(float _mass);
	float Mass();

	void Elasticity(float _e);
	float Elasticity();

	void InertiaTensorLocal(glm::mat3 _tensor);
	glm::mat3 InertiaTensorLocal();

	glm::mat3 InertiaTensorWorld();
private:
	std::shared_ptr<Transform> mTransform;
	glm::quat mOrientation; // Dynamic body handles it's own rotation and syncs every tick

	RBINTEGRATION mIntegration;
	void IntegrationEuler(float _deltaTime);
	void IntegrationRK2(float _deltaTime);
	void IntegrationRK4(float _deltaTime);
	void IntegrationVerlet(float _deltaTime);

	glm::vec3 mForce;
	glm::vec3 mVelocity;
	glm::vec3 mAngularVelocity;
	glm::vec3 mAcceleration;
	glm::vec3 mPreviousPosition;
	float mMass;
	float mElasticity;

	glm::mat3 mInertiaTensorLocal;
	glm::mat3 mInertiaTensorWorld;
};