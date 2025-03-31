#include "GameObject.h"

GameObject::GameObject()
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mMatrixCoords = glm::mat4(1.0f);
}

GameObject::GameObject(SHAPE _modelShape, COLOR _color)
{
	switch (_modelShape)
	{
	case CUBE:
		mModel = std::make_shared<Model>("./data/models/primitives/cube/Primitive_CUBE.obj");
		break;
	case SPHERE:
		mModel = std::make_shared<Model>("./data/models/primitives/sphere/Primitive_SPHERE.obj");
		break;
	default:
		mModel = std::make_shared<Model>();
		break;
	}

	switch (_color)
	{
	case RED:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/red.png");
		break;
	case BLUE:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/blue.png");
		break;
	case GREEN:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/green.png");
		break;
	case ORANGE:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/orange.png");
		break;
	case PURPLE:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/purple.png");
		break;
	case YELLOW:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/yellow.png");
		break;
	case WHITE:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/white.png");
		break;
	default:
	case BLACK:
		mTexture = std::make_shared<Texture>("./data/models/primitives/colors/black.png");
		break;
	}

	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mMatrixCoords = glm::mat4(1.0f);
}

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

	if (mTexture)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->ID());
	}

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