#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>

#include "Transform.h"
#include "EventManager.h"
#include "TimeManager.h"

/// <summary>
/// Camera - Virtual representation of what will be drawn to the window.
/// </summary>
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

	/// <summary>
	/// Update function - called once a frame by the Window.
	/// </summary>
	virtual void Update();

	/// <summary>
	/// Attaches the Event Manager component to the Camera.
	/// </summary>
	/// <param name="_manager"> Event Manager </param>
	void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }

	/// <summary>
	/// Attaches the Time Manager component to the Camera.
	/// </summary>
	/// <param name="_manager"> Time Manager </param>
	void AttachTimeManager(std::shared_ptr<TimeManager> _manager) { mTimeManager = _manager; }

	/// <summary>
	/// Sets the position of the Camera.
	/// </summary>
	/// <param name="_pos"> Vector position to set </param>
	void Position(glm::vec3 _pos) noexcept { mPosition = _pos; }

	/// <summary>
	/// Gets the position of the Camera.
	/// </summary>
	/// <returns> Vector position </returns>
	glm::vec3 Position() const noexcept { return mPosition; }
	
	/// <summary>
	/// Returns the pitch of the Camera.
	/// </summary>
	/// <returns> Float pitch </returns>
	float Pitch() const noexcept { return mPitch; }

	/// <summary>
	/// Sets the pitch of the Camera.
	/// </summary>
	/// <param name="_pitch"> Pitch to set </param>
	void Pitch(float _pitch) noexcept { mPitch = _pitch; }

	/// <summary>
	/// Returns the priority of the camera.
	/// <para>
	/// The camera with the lowest priority will be set as the active camera.
	/// </para>
	/// </summary>
	/// <returns> Int priority </returns>
	int GetPriority() const noexcept { return mPriority; }

	/// <summary>
	/// Returns the view matrix of the Camera.
	/// </summary>
	/// <returns> Mat view matrix </returns>
	glm::mat4 GetView() const noexcept { return mView; }
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

private:
	SDL_bool mOrbitMouseLocked;
};

