#pragma once

#include <memory>

#include "TimeManager.h"
#include "GameObject.h"
#include "Rigidbody.h"

class PhysicsManager
{
public:
	PhysicsManager(std::shared_ptr<TimeManager> _time);

	void Update();

	void Add(std::shared_ptr<Rigidbody> _rb);
private:
	void ResponseCubeToCube(std::shared_ptr<Rigidbody> _c1, std::shared_ptr<Rigidbody> _c2);
	void ResponseCubeToSphere(std::shared_ptr<Rigidbody> _c1, std::shared_ptr<Rigidbody> _s1);
	void ResponseSphereToSphere(std::shared_ptr<Rigidbody> _s1, std::shared_ptr<Rigidbody> _s2);

	std::shared_ptr<TimeManager> mTimeManager;

	std::vector<std::shared_ptr<Rigidbody>> mRigidbodies;
};