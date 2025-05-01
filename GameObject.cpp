#include "GameObject.h"

GameObject::GameObject() : mKILL(false), mUsingCustomShader(false)
{
	mTransform = std::make_shared<Transform>();
}

GameObject::GameObject(SHAPE _modelShape, COLOR _color) : mKILL(false), mUsingCustomShader(false)
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

GameObject::GameObject(const char* _modelPath, const char* _texturePath) : mEventManager(nullptr), mKILL(false), mUsingCustomShader(false)
{
	mModel = std::make_shared<Model>(_modelPath);
	mTexture = std::make_shared<Texture>(_texturePath);
	mTransform = std::make_shared<Transform>();
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
}

void GameObject::Update()
{
}

void GameObject::Draw(const glm::mat4& _viewMatrix, const glm::vec3& _viewPos, const glm::mat4& _projectionMatrix)
{
	// rewrite this so that unnecessary updating isnt done every draw call
	mCustomShader->SetActive();
	mCustomShader->SetUniform("uView", _viewMatrix);

	std::cout << _viewPos.x << std::endl;
	mCustomShader->SetUniform("uViewPos", _viewPos);

	mCustomShader->SetUniform("uProjection", _projectionMatrix);

	glBindVertexArray(mModel->ID());

	if (mTexture)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->ID());
	}

	// Sets position of model
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, mTransform->Position());
	
	model = glm::rotate(model, glm::radians(mTransform->Rotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(mTransform->Rotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(mTransform->Rotation().z), glm::vec3(0, 0, 1));

	model = glm::scale(model, mTransform->Scale());

	mCustomShader->SetUniform("uModel", model);

	// Draw shape
	glDrawArrays(GL_TRIANGLES, 0, mModel->VertexCount());

	// Reset the state
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
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

	model = glm::translate(model, mTransform->Position());

	model = glm::rotate(model, glm::radians(mTransform->Rotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(mTransform->Rotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(mTransform->Rotation().z), glm::vec3(0, 0, 1));

	model = glm::scale(model, mTransform->Scale());

	_shader->SetUniform("uModel", model);

	// Draw shape
	glDrawArrays(GL_TRIANGLES, 0, mModel->VertexCount());

	// Reset the state
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::CreateCollider(SHAPE _type)
{
	mCollider = std::make_shared<Collider>(_type, mModel->GetFaces(), mTransform);
}

void GameObject::CreateRigidbody(RBTYPE _type)
{
	if (mCollider)
	{
		std::weak_ptr<GameObject> weak = shared_from_this();
		mRigidbody = std::make_shared<Rigidbody>(weak, mCollider, _type, mTransform);
	}
	else
	{
		printf("WARNING! Rigidbody cannot initialize without a collider\n");
	}
}

void GameObject::OnCollisionEnter(std::shared_ptr<Rigidbody> _other)
{
	//std::cout << "COLLISION ENTER" << std::endl;
}

void GameObject::OnCollisionStay(std::shared_ptr<Rigidbody> _other)
{
	//std::cout << "COLLISION STAY" << std::endl;
}

void GameObject::OnCollisionExit(std::shared_ptr<Rigidbody> _other)
{
	//std::cout << "COLLISION EXIT" << std::endl;
}

void GameObject::UseCustomShader(const std::string& _key, const std::string& _generalPath)
{
	if (mShaderManager != nullptr)
	{
		if (mShaderManager->GetShader(_key) == nullptr)
		{
			mCustomShader = mShaderManager->AddShader(_key, _generalPath);
			mUsingCustomShader = true;
			if (mCustomShader == nullptr)
			{
				mUsingCustomShader = false;
				//warning?
			}
		}
		else
		{
			mCustomShader = mShaderManager->GetShader(_key);
			mUsingCustomShader = true;
		}
	}
	else
	{
		//warning?
	}
}

void GameObject::UseCustomShader(const std::string& _key, const std::string& _vertexPath, const std::string& _fragmentPath)
{
	if (mShaderManager != nullptr)
	{
		if (mShaderManager->GetShader(_key) == nullptr)
		{
			mCustomShader = mShaderManager->AddShader(_key, _vertexPath, _fragmentPath);
			mUsingCustomShader = true;
			if (mCustomShader == nullptr)
			{
				mUsingCustomShader = false;
				//warning?
			}
		}
		else
		{
			mCustomShader = mShaderManager->GetShader(_key);
			mUsingCustomShader = true;
		}
	}
	else
	{
		//warning?
	}
}
