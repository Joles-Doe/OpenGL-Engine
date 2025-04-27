#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Transform.h"

/// <summary>
/// KinematicBody - provides a finer control over the physics-based system DynamicBody uses.
/// <para>
/// Won't move by the physics-based system, but will still handle collision with other Rigidbodies.
/// </para>
/// </summary>
class KinematicBody
{
public:
	KinematicBody(std::shared_ptr<Transform> _transform);

	/// <summary>
	/// Update function called by the Rigidbody once per frame, to perform physics computation.
	/// </summary>
	/// <param name="_deltaTime"> DeltaTime </param>
	void Update(float _deltaTime);

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
	/// Changes the Rigidbody's elasticity.
	/// </summary>
	/// <param name="_e"> Elasticity to set </param>
	void Elasticity(float _e) noexcept { mElasticity = _e; }

	/// <summary>
	/// Returns the Rigidbody's elasticity.
	/// </summary>
	/// <returns> Float elasticity </returns>
	float Elasticity() const noexcept { return mElasticity; }

private:
	std::shared_ptr<Transform> mTransform;

	glm::vec3 mVelocity;
	glm::vec3 mAcceleration;
	float mElasticity;
};

