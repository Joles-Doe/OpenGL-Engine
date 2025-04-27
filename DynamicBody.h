#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"
#include "Transform.h"

/// <summary>
/// DynamicBody - provides a physics-based way to control the movement and position.
/// <para>
/// Uses simulated physics forces and torque to move the Rigidbody.
/// </para>
/// </summary>
class DynamicBody
{
public:
	DynamicBody(std::shared_ptr<Transform> _transform);

	/// <summary>
	/// Update function called by the Rigidbody once per frame, to perform physics computation.
	/// </summary>
	/// <param name="_deltaTime"> DeltaTime </param>
	/// <param name="_rot"> GameObject rotation </param>
	/// <returns> Degrees rotation vector </returns>
	glm::vec3 Update(float _deltaTime, glm::vec3 _rot);

	/// <summary>
	/// Changes the Integration mode called during the update function.
	/// </summary>
	/// <param name="_mode"> New Integration Mode </param>
	void ChangeIntegration(RBINTEGRATION _mode) noexcept { mIntegration = _mode; }

	/// <summary>
	/// Adds the current force on top of the Rigidbody's acting forces.
	/// </summary>
	/// <param name="_force"> Force to add </param>
	void AddForce(glm::vec3 _force) { mForce += _force; }

	/// <summary>
	/// Changes the Rigidbody's acting force.
	/// </summary>
	/// <param name="_force"> Force to set </param>
	void Force(glm::vec3 _force) noexcept { mForce = _force; }

	/// <summary>
	/// Returns the current acting force.
	/// </summary>
	/// <returns> Vector Rigidbody force </returns>
	glm::vec3 Force() const noexcept { return mForce; }

	/// <summary>
	/// Changes the Rigidbody's current linear velocity.
	/// </summary>
	/// <param name="_vel"> Velocity to set </param>
	void Velocity(glm::vec3 _vel) noexcept { mVelocity = _vel; }
	
	/// <summary>
	/// Returns the current linear velocity.
	/// </summary>
	/// <returns> Vector Rigidbody velocity </returns>
	glm::vec3 Velocity() const noexcept { return mVelocity; }

	/// <summary>
	/// Changes the Rigidbody's current angular velocity.
	/// </summary>
	/// <param name="_vel"> Velocity to set </param>
	void AngularVelocity(glm::vec3 _vel) noexcept { mAngularVelocity = _vel; }

	/// <summary>
	/// Returns the current angular velocity.
	/// </summary>
	/// <returns> Vector Rigidbody velocity </returns>
	glm::vec3 AngularVelocity() const noexcept { return mAngularVelocity; }

	/// <summary>
	/// Changes the Rigidbody's current acceleration
	/// </summary>
	/// <param name="_accel"> Acceleration to set </param>
	void Acceleration(glm::vec3 _accel) noexcept { mAcceleration = _accel; }

	/// <summary>
	/// Returns the current acceleration.
	/// </summary>
	/// <returns> Vector Rigidbody acceleration </returns>
	glm::vec3 Acceleration() const noexcept { return mAcceleration; }

	/// <summary>
	/// Changes the Rigidbody's mass.
	/// </summary>
	/// <param name="_mass"> Mass to set </param>
	void Mass(float _mass) noexcept { mMass = _mass; }

	/// <summary>
	/// Returns the current mass.
	/// </summary>
	/// <returns> Float mass </returns>
	float Mass() const noexcept { return mMass; }

	/// <summary>
	/// Changes the Rigidbody's elasticity.
	/// </summary>
	/// <param name="_e"> Elasticity to set </param>
	void Elasticity(float _e) noexcept { mElasticity = _e; }

	/// <summary>
	/// Returns the Rigidbody's elasticity.
	/// </summary>
	/// <returns> Float elasticity </returns>
	float Elasticity() const noexcept { return mElasticity; }

	/// <summary>
	/// Changes the Rigidbody's local Inertia tensor.
	/// </summary>
	/// <param name="_tensor"> Inertia tensor to set </param>
	void InertiaTensorLocal(glm::mat3 _tensor) noexcept { mInertiaTensorLocal = _tensor; }

	/// <summary>
	/// Returns the Rigidbody's local Inertia tensor.
	/// </summary>
	/// <returns> Mat3 local inertia tensor </returns>
	glm::mat3 InertiaTensorLocal() const noexcept { return mInertiaTensorLocal; }

	/// <summary>
	/// Returns the Rigidbody's world Inertia tensor.
	/// </summary>
	/// <returns> Mat3 world inertia tensor. </returns>
	glm::mat3 InertiaTensorWorld() const noexcept { return mInertiaTensorWorld; }
private:
	std::shared_ptr<Transform> mTransform;
	glm::quat mOrientation; // Dynamic body handles it's own rotation and syncs every tick

	RBINTEGRATION mIntegration;

	/// <summary>
	/// Euler integration method
	/// </summary>
	/// <param name="_deltaTime"> Deltatime </param>
	void IntegrationEuler(float _deltaTime);

	/// <summary>
	/// Runge-Kutta 2 integration method
	/// </summary>
	/// <param name="_deltaTime"> Deltatime </param>
	void IntegrationRK2(float _deltaTime);

	/// <summary>
	/// Runge-Kutta 4 integration method
	/// </summary>
	/// <param name="_deltaTime"> Deltatime </param>
	void IntegrationRK4(float _deltaTime);

	/// <summary>
	/// Verlet integration method
	/// </summary>
	/// <param name="_deltaTime"> Deltatime </param>
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