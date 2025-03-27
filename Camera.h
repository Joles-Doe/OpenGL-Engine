#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "EventManager.h"

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

	int GetPriority() { return mPriority; };
	glm::mat4 GetView() { return mView; };
protected:
	std::shared_ptr<EventManager> mEventManager;

	Preset mPreset;

	int mPriority;

	glm::mat4 mView;
	glm::vec3 mPosition;
	glm::vec3 mDirection;

	float mPitch;
	float mYaw;
};

