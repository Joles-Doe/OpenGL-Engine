#include "DynamicBody.h"

DynamicBody::DynamicBody(std::shared_ptr<Transform> _transform)
{
	mTransform = _transform;
	mOrientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	mIntegration = EULER;
	mForce = glm::vec3(0.0f);
	mVelocity = glm::vec3(0.0f);
	mAngularVelocity = glm::vec3(0.0f);
	mAcceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	mPreviousPosition = mTransform->Position();
	mMass = 1.0f;
	mElasticity = 1.0f;

	mInertiaTensorLocal = glm::mat3(1.0f);
	mInertiaTensorWorld = glm::mat3(1.0f);
}

glm::vec3 DynamicBody::Update(float _deltaTime, glm::vec3 _rot)
{
	// Sync rotation
	mOrientation = glm::quat(glm::radians(_rot));

	mInertiaTensorWorld = glm::mat3_cast(mOrientation) * glm::inverse(mInertiaTensorLocal) * glm::transpose(glm::mat3_cast(mOrientation));

	switch (mIntegration)
	{
	case EULER:
		IntegrationEuler(_deltaTime);
		break;
	case RK2:
		IntegrationRK2(_deltaTime);
		break;
	case RK4:
		IntegrationRK4(_deltaTime);
		break;
	case VERLET:
		IntegrationVerlet(_deltaTime);
		break;
	}

	glm::quat deltaRotation = glm::quat(0, mAngularVelocity.x, mAngularVelocity.y, mAngularVelocity.z) * mOrientation * 0.5f;
	mOrientation += deltaRotation * _deltaTime;
	mOrientation = glm::normalize(mOrientation);

	mForce = mMass * mAcceleration;

	return glm::degrees(glm::eulerAngles(mOrientation));
}

void DynamicBody::ChangeIntegration(RBINTEGRATION _mode)
{
	mIntegration = _mode;
}

void DynamicBody::AddForce(glm::vec3 _force)
{
	mForce += _force;
}

void DynamicBody::Force(glm::vec3 _force)
{
	mForce = _force;
}

glm::vec3 DynamicBody::Force()
{
	return mForce;
}

void DynamicBody::Velocity(glm::vec3 _vel)
{
	mVelocity = _vel;
}

glm::vec3 DynamicBody::Velocity()
{
	return mVelocity;
}

void DynamicBody::AngularVelocity(glm::vec3 _vel)
{
	mAngularVelocity = _vel;
}

glm::vec3 DynamicBody::AngularVelocity()
{
	return mAngularVelocity;
}

void DynamicBody::Acceleration(glm::vec3 _accel)
{
	mAcceleration = _accel;
}

glm::vec3 DynamicBody::Acceleration()
{
	return mAcceleration;
}

void DynamicBody::Mass(float _mass)
{
	mMass = _mass;
}

float DynamicBody::Mass()
{
	return mMass;
}

void DynamicBody::Elasticity(float _e)
{
	mElasticity = _e;
}

float DynamicBody::Elasticity()
{
	return mElasticity;
}

void DynamicBody::InertiaTensorLocal(glm::mat3 _tensor)
{
	mInertiaTensorLocal = _tensor;
}

glm::mat3 DynamicBody::InertiaTensorLocal()
{
	return mInertiaTensorLocal;
}

glm::mat3 DynamicBody::InertiaTensorWorld()
{
	return mInertiaTensorWorld;
}

void DynamicBody::IntegrationEuler(float _deltaTime)
{
	float oneOverMass = 1 / mMass;
	mVelocity += (mForce * oneOverMass) * _deltaTime;
	mTransform->Position(mTransform->Position() += mVelocity * _deltaTime);
}

void DynamicBody::IntegrationRK2(float _deltaTime)
{
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1;

	force = mForce;
	acceleration = force / mMass;
	k0 = acceleration;

	force = mForce + k0 / 2.0f;
	acceleration = force / mMass;
	k1 = acceleration;

	mVelocity += k1 * _deltaTime;
	mTransform->Position(mTransform->Position() += mVelocity * _deltaTime);
}

void DynamicBody::IntegrationRK4(float _deltaTime)
{
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1;
	glm::vec3 k2;
	glm::vec3 k3;

	// Evaluate once at t0 to find k0
	force = mForce;
	acceleration = force / mMass;
	//k0 = dt * acceleration;
	k0 = acceleration;

	// Evaluate twice at t0 + deltaT/2.0 using half of k0 and half of k1
	force = mForce + k0 / 2.0f;
	acceleration = force / mMass;
	//k1 = dt * acceleration;
	k1 = acceleration;

	force = mForce + k1 / 2.0f;
	acceleration = force / mMass;
	//k2 = dt * acceleration;
	k2 = acceleration;

	// Evaluate once at t0 + deltaT using k2
	force = mForce + k2;
	acceleration = force / mMass;
	//k3 = dt * acceleration;
	k3 = acceleration;

	// Evaluate at t0 + deltaT using weighted sum of k0, k1, k2, and k3
	mVelocity += _deltaTime * (k0 + 2.0f * k1 + 2.0f * k2 + k3) / 6.0f;

	mTransform->Position(mTransform->Position() += mVelocity * _deltaTime);
}

void DynamicBody::IntegrationVerlet(float _deltaTime)
{
	glm::vec3 acceleration = mForce / mMass;
	mPreviousPosition = mTransform->Position() - mVelocity * _deltaTime + 0.5f * acceleration * (_deltaTime * _deltaTime);
	mTransform->Position(2.0f * mTransform->Position() - mPreviousPosition + acceleration * (_deltaTime * _deltaTime));
	mVelocity = (mTransform->Position() - mPreviousPosition) / (2.0f * _deltaTime);
	mVelocity += acceleration * _deltaTime;
}