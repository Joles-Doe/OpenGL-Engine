#include "GameObject.h"

GameObject::GameObject(const char* _modelPath, const char* _texturePath) : mEventManager(nullptr)
{
	mModel = std::make_shared<Model>(_modelPath);
	mTexture = std::make_shared<Texture>(_texturePath);

	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mMatrixCoords = glm::mat4(1.0f);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Draw(std::shared_ptr<ShaderProgram> _shader)
{
	glBindVertexArray(mModel->ID());
	glBindTexture(GL_TEXTURE_2D, mTexture->ID());

	// Sets position of model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, mPosition);

	_shader->SetUniform("uModel", model);

	// Draw shape
	glDrawArrays(GL_TRIANGLES, 0, mModel->VertexCount());

	// Reset the state
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::Move(glm::vec3 _movement)
{
	mPosition += _movement;

	mMatrixCoords = glm::translate(mMatrixCoords, _movement);
}