#pragma once

#include <memory>

#include "TimeManager.h"
#include "GameObject.h"
#include "Rigidbody.h"

/// <summary>
/// Physics Manager - Handles the physics implementation of the engine
/// <para> 
/// Checks collision pairs of every passed Rigidbody, as well as updating them once a frame.
/// </para>
/// </summary>
class PhysicsManager
{
public:
	PhysicsManager(std::shared_ptr<TimeManager> _time);

	/// <summary>
	/// Update function called by the Window once per frame, to perform physics computation.
	/// </summary>
	void Update();

	/// <summary>
	/// Adds the passed Rigidbody to the Manager.
	/// </summary>
	/// <param name="_rb"> Rigidbody to pass through </param>
	void Add(std::shared_ptr<Rigidbody> _rb);
private:
	/// <summary>
	/// Removes Rigidbodies whose GameObject parent is no longer initialized.
	/// </summary>
	void CullDeletedRigidbodies();

	/// <summary>
	/// Impulse response for two Cube shaped Rigidbodies.
	/// </summary>
	/// <param name="_c1"> Cube Rigidbody 1 </param>
	/// <param name="_c2"> Cube Rigidbody 2 </param>
	void ResponseCubeToCube(std::shared_ptr<Rigidbody> _c1, std::shared_ptr<Rigidbody> _c2);

	/// <summary>
	/// Impulse response for two Rigidbodies, shaped Cube and Sphere respectively.
	/// </summary>
	/// <param name="_c1"> Cube Rigidbody </param>
	/// <param name="_s1"> Sphere Rigidbody </param>
	void ResponseCubeToSphere(std::shared_ptr<Rigidbody> _c1, std::shared_ptr<Rigidbody> _s1);

	/// <summary>
	/// Impulse response for two Sphere shaped Rigidbodies.
	/// </summary>
	/// <param name="_s1"> Sphere Rigidbody 1 </param>
	/// <param name="_s2"> Sphere Rigidbody 2 </param>
	void ResponseSphereToSphere(std::shared_ptr<Rigidbody> _s1, std::shared_ptr<Rigidbody> _s2);

	// Time Manager
	std::shared_ptr<TimeManager> mTimeManager;

	// Stored vector of Rigidbodies
	std::vector<std::shared_ptr<Rigidbody>> mRigidbodies;
};