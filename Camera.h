#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "EventManager.h"

class Camera
{
public:
	Camera();

	void Update();

	void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }

	glm::mat4 GetView() { return mView; };
private:
	std::shared_ptr<EventManager> mEventManager;

	glm::mat4 mView;
	glm::vec3 mPosition;
	glm::vec3 mDirection;

	float mPitch;
	float mYaw;
};

