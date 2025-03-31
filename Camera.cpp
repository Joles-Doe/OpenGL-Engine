#include "Camera.h"
#include <iostream>
Camera::Camera(Preset _preset) : mPriority(0), mOrbitMouseLocked(SDL_FALSE)
{
    mPreset = _preset;

	mView = glm::mat4(1.0f);
    mPosition = glm::vec3(0.0f);
    mDirection = glm::vec3(0.0f);
	mPitch = 0.0f;
	mYaw = -90.0f;
}

void Camera::Update()
{
    switch (mPreset)
    {
    case ORBIT:
        if (mEventManager->GetMouseDown("2"))
        {
            if (!mOrbitMouseLocked)
            {
                mOrbitMouseLocked = SDL_TRUE;
                SDL_SetRelativeMouseMode(mOrbitMouseLocked);
            }

            MouseAxis mouseMovement = mEventManager->GetMouseAxis();
            mYaw += mouseMovement.x * 0.1;
            mPitch -= mouseMovement.y * 0.1;

            if (mPitch > 89.0f) mPitch = 89.0f;
            if (mPitch < -89.0f) mPitch = -89.0f;
        }
        else if (mOrbitMouseLocked)
        {
            mOrbitMouseLocked = SDL_FALSE;
            SDL_SetRelativeMouseMode(mOrbitMouseLocked);
        }

        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

        mDirection = glm::normalize(front);

        glm::vec3 rightVector = glm::normalize(glm::cross(mDirection, glm::vec3(0.0f, 1.0f, 0.0f)));

        if (mEventManager->GetKeyDown("w"))
        {
            mPosition += mDirection * mTimeManager->DeltaTime() * 5.0f;
        }
        if (mEventManager->GetKeyDown("a"))
        {
            mPosition -= rightVector * mTimeManager->DeltaTime() * 5.0f;
        }
        if (mEventManager->GetKeyDown("s"))
        {
            mPosition -= mDirection * mTimeManager->DeltaTime() * 5.0f;
        }
        if (mEventManager->GetKeyDown("d"))
        {
            mPosition += rightVector * mTimeManager->DeltaTime() * 5.0f;
        }
        if (mEventManager->GetKeyDown("q"))
        {
            mPosition += glm::vec3(0, 1, 0) * mTimeManager->DeltaTime() * 5.0f;
        }
        if (mEventManager->GetKeyDown("e"))
        {
            mPosition -= glm::vec3(0, 1, 0) * mTimeManager->DeltaTime() * 5.0f;
        }

        mView = glm::lookAt(mPosition, mPosition + mDirection, glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    }
}