#include "GameObject.h"

GameObject::GameObject()
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotation = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
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
	mRotation = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
}

GameObject::GameObject(const char* _modelPath, const char* _texturePath) : mEventManager(nullptr)
{
	mModel = std::make_shared<Model>(_modelPath);
	mTexture = std::make_shared<Texture>(_texturePath);

	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotation = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
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


	//========= PLACE IN A FUNCTION / CLASS EVENTUALLY ===============

	// Sets position of model
	glm::mat4 model = glm::mat4(1.0f);

	// Order of operation goes Scale, Translation, and Rotation
	

	model = glm::translate(model, mPosition);
	model = glm::scale(model, mScale);

	model = glm::rotate(model, mRotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, mRotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, mRotation.z, glm::vec3(0, 0, 1));

	//=================================================================

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
}

void GameObject::Rotate(glm::vec3 _rot)
{
	mRotation += _rot;
}

void GameObject::SetPosition(glm::vec3 _pos)
{
	mPosition = _pos;
}

void GameObject::SetRotation(glm::vec3 _rot)
{
	mRotation = _rot;
}

void GameObject::SetScale(glm::vec3 _scale)
{
	mScale = _scale;
}
