#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "EventManager.h"
#include "TimeManager.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderProgram.h"

class GameObject
{
public:
	enum SHAPE
	{
		CUBE,
		SPHERE
	};
	enum COLOR
	{
		RED,
		BLUE,
		GREEN,
		ORANGE,
		PURPLE,
		YELLOW,
		BLACK,
		WHITE
	};

	GameObject();
	GameObject(SHAPE _modelShape, COLOR _color = RED);
	GameObject(const char* _modelPath, const char* _texturePath);
	~GameObject();

	virtual void Update();
	void Draw(std::shared_ptr<ShaderProgram> _shader);
	
	void Move(glm::vec3 _movement);
	void Rotate(glm::vec3 _rot);

	void SetPosition(glm::vec3 _pos);
	void SetRotation(glm::vec3 _rot);
	void SetScale(glm::vec3 _scale);

	void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }
	void AttachTimeManager(std::shared_ptr<TimeManager> _manager) { mTimeManager = _manager; }
private:
	std::shared_ptr<EventManager> mEventManager;
	std::shared_ptr<TimeManager> mTimeManager;

	std::shared_ptr<Model> mModel;
	std::shared_ptr<Texture> mTexture;

	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};

