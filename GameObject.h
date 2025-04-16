#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"

#include "EventManager.h"
#include "TimeManager.h"
#include "Model.h"
#include "Transform.h"
#include "Texture.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "ShaderProgram.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	GameObject(SHAPE _modelShape, COLOR _color = RED);
	GameObject(const char* _modelPath, const char* _texturePath);
	~GameObject();

	virtual void Start();
	virtual void Update();
	void Draw(std::shared_ptr<ShaderProgram> _shader);

	bool IsKill();

	void CreateCollider(SHAPE _type);
	void CreateRigidbody(RBTYPE _type);

	virtual void OnCollisionEnter(std::shared_ptr<Rigidbody> _other);
	virtual void OnCollisionStay(std::shared_ptr<Rigidbody> _other);
	virtual void OnCollisionExit(std::shared_ptr<Rigidbody> _other);

	std::shared_ptr<Transform> GetTransform() { return mTransform; }
	std::shared_ptr<Rigidbody> GetRigidbody() { return mRigidbody; }

	void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }
	void AttachTimeManager(std::shared_ptr<TimeManager> _manager) { mTimeManager = _manager; }
protected:
	bool mKILL;

	std::shared_ptr<EventManager> mEventManager;
	std::shared_ptr<TimeManager> mTimeManager;

	std::shared_ptr<Transform> mTransform;
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Collider> mCollider;
	std::shared_ptr<Rigidbody> mRigidbody;
};

