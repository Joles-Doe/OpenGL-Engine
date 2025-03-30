#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "EventManager.h"
#include "TimeManager.h"

class Camera
{
public:
	enum Preset
	{
		STATIC,
		ORBIT,
		CUSTOM
	};

	Camera(Preset _preset);

	virtual void Update();

	void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }
	void AttachTimeManager(std::shared_ptr<TimeManager> _manager) { mTimeManager = _manager; }

	int GetPriority() { return mPriority; };
	glm::mat4 GetView() { return mView; };
protected:
	std::shared_ptr<EventManager> mEventManager;
	std::shared_ptr<TimeManager> mTimeManager;

	Preset mPreset;

	int mPriority;

	glm::mat4 mView;
	glm::vec3 mPosition;
	glm::vec3 mDirection;

	float mPitch;
	float mYaw;
};

