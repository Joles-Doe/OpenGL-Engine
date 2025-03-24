#include "Camera.h"

Camera::Camera()
{
	mView = glm::mat4(1.0f);
    mPosition = glm::vec3(0.0f);
	mPitch = 0.0f;
	mYaw = -90.0f;
}

void Camera::Update()
{
    MouseAxis mouseMovement = mEventManager->GetMouseAxis();
    mYaw += mouseMovement.x * 0.1;
    mPitch -= mouseMovement.y * 0.1;

    if (mPitch > 89.0f) mPitch = 89.0f;
    if (mPitch < -89.0f) mPitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mDirection = glm::normalize(front);

    mView = glm::lookAt(mPosition, mPosition + mDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}