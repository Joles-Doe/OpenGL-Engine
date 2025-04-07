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
	std::shared_ptr<TimeManager> mTimeManager;

	std::vector<std::shared_ptr<Rigidbody>> mRigidbodies;
};