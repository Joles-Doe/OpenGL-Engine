#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Model.h"
#include "Texture.h"
#include "ShaderProgram.h"

class GameObject
{
public:
	GameObject(const char* _modelPath, const char* _texturePath);
	~GameObject();

	void Draw(ShaderProgram* _shader);
	void Move(glm::vec3 _movement);

private:
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Texture> mTexture;

	glm::mat4 mMatrixCoords;
	glm::vec3 mPosition;
};

