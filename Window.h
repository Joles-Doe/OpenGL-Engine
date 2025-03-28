#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <vector>
#include <memory>

#include "EventManager.h"
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Camera.h"


class Window
{
public:
	Window(int _w, int _h, const std::string& _name);
	~Window();

	void Update();
	void AddObject(std::shared_ptr<GameObject> _obj);

	std::shared_ptr<Camera> GetActiveCamera();
	void AddCamera(std::shared_ptr<Camera> _cam);

	std::shared_ptr<EventManager> GetEventManager() { return mEventManager; }
	bool GetQuitState();
private:
	SDL_Window* mWindow;
	std::shared_ptr<EventManager> mEventManager;
	std::shared_ptr<ShaderProgram> mCurrentShader;

	SDL_bool mMouseLocked;

	glm::mat4 mProjection;

	std::vector<std::shared_ptr<Camera>> mCameras;
	std::vector<std::shared_ptr<GameObject>> mObjects;
};