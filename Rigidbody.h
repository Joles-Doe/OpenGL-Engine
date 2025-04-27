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

/// <summary>
/// Rigidbody - provides a physics-based way to control the movement and position.
/// <para>
/// Uses simulated physics forces, dependent on the sub-body.
/// </para>
/// </summary>
class Rigidbody
{
public:
	Rigidbody(std::weak_ptr<GameObject> _parent, std::shared_ptr<Collider> _collider, RBTYPE _bodyType, std::shared_ptr<Transform> _transform);

	// <summary>
	/// Returns the Rigidbody's parent GameObject component.
	/// </summary>
	/// <returns> GameObject parent </returns>
	std::weak_ptr<GameObject> GetGameObject() { return mParent; }

	/// <summary>
	/// Returns the GameObject's Transform component.
	/// </summary>
	/// <returns> Transform component </returns>
	std::shared_ptr<Transform> GetTransform() { return mTransform; }

	/// <summary>
	/// Returns the GameObject's Collider component.
	/// </summary>
	/// <returns> Rigidbody component </returns>
	std::shared_ptr<Collider> GetCollider() { return mCollider; }

	/// <summary>
	/// Checks if the passed Rigidbody has already been collided with last frame.
	/// </summary>
	/// <param name="_other"> Rigidbody to check </param>
	/// <returns> True or False dependent on if collision also happened last frame /returns>
	bool RigidbodyAlreadyCollided(std::shared_ptr<Rigidbody> _other);

	/// <summary>
	/// Adds a currently colliding Rigidbody to memory.
	/// </summary>
	/// <param name="_other"> Rigidbody to add </param>
	void AddCollidedRigidbody(std::shared_ptr<Rigidbody> _other);

	/// <summary>
	/// Removes a previously collided Rigidbody from memory.
	/// </summary>
	/// <param name="_other"> Rigidbody to remove </param>
	void RemoveCollidedRigidbody(std::shared_ptr<Rigidbody> _other);

	/// <summary>
	/// Returns a value dependent on if the current sub-body is a DynamicBody
	/// </summary>
	/// <returns> True if the sub-body is a DynamicBody</returns>
	bool IsDynamic() const noexcept { return mUseDynamicBody; }

	/// <summary>
	/// Update function called by the PhysicsManager once per frame, to perform physics computation.
	/// </summary>
	/// <param name="_deltaTime"> DeltaTime </param>
	void Update(float _deltaTime);

	/// <summary>
	/// Changes the Rigidbody's Integration mode. [DYNAMIC ONLY]
	/// </summary>
	/// <param name="_mode"> New Integration Mode </param>
	void ChangePhysicsIntegration(RBINTEGRATION _mode);

	/// <summary>
	/// Adds the current force to the DynamicBody.
	/// </summary>
	/// <param name="_force"> Force to add </param>
	void AddForce(glm::vec3 _force) noexcept;
	
	/// <summary>
	/// Changes the Rigidbody's acting force. [DYNAMIC ONLY]
	/// </summary>
	/// <param name="_force"> Force to set </param>
	void Force(glm::vec3 _force) noexcept;

	/// <summary>
	/// Returns the current acting force.
	/// </summary>
	/// <returns> Vector Rigidbody force </returns>
	glm::vec3 Force() const noexcept;

	/// <summary>
	/// Changes the Rigidbody's current linear velocity. [DYNAMIC and KINEMATIC]
	/// </summary>
	/// <param name="_vel"> Velocity to set </param>
	void Velocity(glm::vec3 _vel) noexcept;

	/// <summary>
	/// Returns the current linear velocity. [DYNAMIC and KINEMATIC]
	/// </summary>
	/// <returns> Vector Rigidbody velocity </returns>
	glm::vec3 Velocity() const noexcept;

	/// <summary>
	/// Changes the Rigidbody's current angular velocity. [DYNAMIC ONLY]
	/// </summary>
	/// <param name="_vel"> Velocity to set </param>
	void AngularVelocity(glm::vec3 _vel) noexcept;

	/// <summary>
	/// Returns the current angular velocity. [DYNAMIC ONLY]
	/// </summary>
	/// <returns> Vector Rigidbody velocity </returns>
	glm::vec3 AngularVelocity() const noexcept;

	/// <summary>
	/// Changes the Rigidbody's current acceleration [DYNAMIC and KINEMATIC]
	/// </summary>
	/// <param name="_accel"> Acceleration to set </param>
	void Acceleration(glm::vec3 _accel) noexcept;

	/// <summary>
	/// Returns the current acceleration. [DYNAMIC and KINEMATIC]
	/// </summary>
	/// <returns> Vector Rigidbody acceleration </returns>
	glm::vec3 Acceleration() const noexcept;

	/// <summary>
	/// Changes the Rigidbody's mass. [DYNAMIC ONLY]
	/// </summary>
	/// <param name="_mass"> Mass to set </param>
	void Mass(float _mass) noexcept;

	/// <summary>
	/// Returns the current mass. [DYNAMIC ONLY]
	/// </summary>
	/// <returns> Float mass </returns>
	float Mass() const noexcept;

	/// <summary>
	/// Changes the Rigidbody's elasticity. [DYNAMIC and KINEMATIC]
	/// </summary>
	/// <param name="_e"> Elasticity to set </param>
	void Elasticity(float _e) noexcept;

	/// <summary>
	/// Returns the Rigidbody's elasticity. [DYNAMIC and KINEMATIC]
	/// </summary>
	/// <returns> Float elasticity </returns>
	float Elasticity() const noexcept;

	/// <summary>
	/// Changes the Rigidbody's local Inertia tensor. [DYNAMIC ONLY]
	/// </summary>
	/// <param name="_tensor"> Inertia tensor to set </param>
	void InertiaTensorLocal(glm::mat3 _tensor) noexcept;

	/// <summary>
	/// Returns the Rigidbody's local Inertia tensor. [DYNAMIC ONLY]
	/// </summary>
	/// <returns> Mat3 local inertia tensor </returns>
	glm::mat3 InertiaTensorLocal() const noexcept;

	/// <summary>
	/// Returns the Rigidbody's world Inertia tensor. [DYNAMIC ONLY]
	/// </summary>
	/// <returns> Mat3 world inertia tensor. </returns>
	glm::mat3 InertiaTensorWorld() const noexcept;
private:
	std::weak_ptr<GameObject> mParent;
	std::shared_ptr<Collider> mCollider;
	std::shared_ptr<Transform> mTransform;

	std::shared_ptr<DynamicBody> mDynamicBody;
	std::shared_ptr<KinematicBody> mKinematicBody;
	bool mUseDynamicBody;

	std::vector<std::shared_ptr<Rigidbody>> mCurrentlyCollidingRigidbodies;

	/// <summary>
	/// Calculates the local inertia tensor for the Rigidbody [DYNAMIC ONLY]
	/// </summary>
	void CalculateInertiaTensor();
};

