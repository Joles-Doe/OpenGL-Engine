#include "GameObject.h"

GameObject::GameObject()
{
	mTransform = std::make_shared<Transform>();
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

	mTransform = std::make_shared<Transform>();
}

GameObject::GameObject(const char* _modelPath, const char* _texturePath) : mEventManager(nullptr)
{
	mModel = std::make_shared<Model>(_modelPath);
	mTexture = std::make_shared<Texture>(_texturePath);
	mTransform = std::make_shared<Transform>();
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (mCollider)
	{
		mCollider->Update();
	}
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

	// Order of operation goes Scale, Translation, and Rotation
	
	model = glm::translate(model, mTransform->Position());
	model = glm::scale(model, mTransform->Scale());

	model = glm::rotate(model, mTransform->Rotation().x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, mTransform->Rotation().y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, mTransform->Rotation().z, glm::vec3(0, 0, 1));

	_shader->SetUniform("uModel", model);

	// Draw shape
	glDrawArrays(GL_TRIANGLES, 0, mModel->VertexCount());

	// Reset the state
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void GameObject::CreateCollider(SHAPE _type)
{
	mCollider = std::make_shared<Collider>(_type, mModel->GetFaceVector(), mTransform);
}

void GameObject::CreateRigidbody(RBTYPE _type)
{
	if (mCollider)
	{
		mRigidbody = std::make_shared<Rigidbody>(shared_from_this(), mCollider, _type, mTransform);
	}
	else
	{
		printf("WARNING! Rigidbody cannot initialize without a collider\n");
	}
}

void GameObject::OnCollisionEnter(std::shared_ptr<Rigidbody> _other)
{

}

void GameObject::OnCollisionStay(std::shared_ptr<Rigidbody> _other)
{

}

void GameObject::OnCollisionExit(std::shared_ptr<Rigidbody> _other)
{

}
