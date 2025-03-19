#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <vector>

#include "GameObject.h"
#include "ShaderProgram.h"


class Window
{
public:
	Window(int _w, int _h, const std::string& _name);
	~Window();

	void Update();
	void AddObject(GameObject* _obj);
private:
	SDL_Window* mWindow;
	ShaderProgram* mCurrentShader;

	glm::mat4 mProjection;
	glm::mat4 mView;
	glm::mat4 mModel;

	std::vector<std::shared_ptr<GameObject>> mObjects;
};