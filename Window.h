#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <vector>
#include <memory>

#include "PhysicsManager.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "ShaderManager.h"
#include "GameObject.h"
#include "HUDObject.h"
#include "Rigidbody.h"
#include "ShaderProgram.h"
#include "Camera.h"

/// <summary>
/// Window - Main class managing the engine. Holds references to the SDL window, and all relevant components.
/// </summary>
class Window
{
public:
	Window(int _w, int _h, const std::string& _name);
	~Window();

	/// <summary>
	/// Main update function. Called by the main gameplay loop once per frame and updates, and draws, every stored object.
	/// </summary>
	void Update();

	/// <summary>
	/// Adds an object to the window.
	/// </summary>
	/// <param name="_obj"> Object to add </param>
	void AddObject(std::shared_ptr<GameObject> _obj);

	/// <summary>
	/// Adds an object to the HUD.
	/// </summary>
	/// <param name="_obj"> Object to add </param>
	void AddHUDObject(std::shared_ptr<HUDObject> _obj);

	/// <summary>
	/// Returns the camera with the highest priority.
	/// </summary>
	/// <returns> Reference to the active camera </returns>
	std::shared_ptr<Camera> GetActiveCamera();

	/// <summary>
	/// Adds a camera to the window.
	/// </summary>
	/// <param name="_cam"></param>
	void AddCamera(std::shared_ptr<Camera> _cam);

	/// <summary>
	/// Returns the TimeManager.
	/// </summary>
	/// <returns> Reference to the TimeManager </returns>
	std::shared_ptr<TimeManager> GetTimeManager() { return mTimeManager; }

	/// <summary>
	/// Returns the EventManager.
	/// </summary>
	/// <returns> Reference to the EventManager </returns>
	std::shared_ptr<EventManager> GetEventManager() { return mEventManager; }

	/// <summary>
	/// Returns the ShaderManager.
	/// </summary>
	/// <returns> Reference to the ShaderManager </returns>
	std::shared_ptr<ShaderManager> GetShaderManager() { return mShaderManager; }

	/// <summary>
	/// Enables a Rigidbody, and sends it to the PhysicsManager for physics computation.
	/// </summary>
	/// <param name="_rb"> Rigidbody to add </param>
	void EnableRigidbody(std::shared_ptr<Rigidbody> _rb) { mPhysicsManager->Add(_rb); }

	/// <summary>
	/// Returns True or False dependent on if the close button has been pressed, or if the engine wants to exit.
	/// </summary>
	/// <returns> True or False dependent on if the program needs to close </returns>
	bool GetQuitState();
private:
	SDL_Window* mWindow;
	std::shared_ptr<TimeManager> mTimeManager;
	std::shared_ptr<PhysicsManager> mPhysicsManager;
	std::shared_ptr<EventManager> mEventManager;
	std::shared_ptr<ShaderManager> mShaderManager;
	std::shared_ptr<ShaderProgram> mDefaultShader;
	std::shared_ptr<ShaderProgram> mDefaultHUDShader;
	std::shared_ptr<ShaderProgram> mDefaultHUDImageShader;

	SDL_bool mMouseLocked;

	glm::mat4 mPerspectiveProjection;
	glm::mat4 mOrthoProjection;

	std::vector<std::shared_ptr<Camera>> mCameras;
	std::vector<std::shared_ptr<GameObject>> mObjects;
	std::vector<std::shared_ptr<HUDObject>> mHUDObjects;

	/// <summary>
	/// Removes GameObjects who are no longer initialized.
	/// </summary>
	void CullDeletedObjects();

	/// <summary>
	/// Removes HUDObjects who are no longer initialized.
	/// </summary>
	void CullDeletedHUDObjects();

	int mPrevWidth;
	int mPrevHeight;

	bool mFirstFrameRendered;
	bool mEnablePhysics;
};