#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SharedStructs&Enums.h"

#include "EventManager.h"
#include "TimeManager.h"
#include "ShaderManager.h"
#include "ShaderStore.h"
#include "Model.h"
#include "Transform.h"
#include "Texture.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "ShaderProgram.h"

/// <summary>
/// GameObject - Base class for every object drawn and updated by the Window.
/// </summary>
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	GameObject(SHAPE _modelShape, COLOR _color = RED);
	GameObject(const char* _modelPath, const char* _texturePath);
	~GameObject();

	/// <summary>
	/// Start function - called once by the Window when the GameObject gets initialized. Use this as your constructor to initialize all of your variables.
	/// </summary>
	virtual void Start();

	/// <summary>
	/// Update function - called once a frame by the Window.
	/// </summary>
	virtual void Update();

	/// <summary>
	/// Draw function - called by the Window to draw the Model. Uses a custom shader.
	/// </summary>
	void Draw(const glm::mat4& _viewMatrix, const glm::vec3& _viewPos, const glm::mat4& _projectionMatrix);

	/// <summary>
	/// Draw function - called by the Window to draw the Model. Uses the default shader.
	/// </summary>
	void Draw(std::shared_ptr<ShaderProgram> _shader);

	/// <summary>
	/// Returns true or false dependent on if the GameObject is dead and will be culled.
	/// </summary>
	/// <returns> Returns true or false dependent on if the GameObject needs culling </returns>
	bool IsKill() const noexcept { return mKILL; }

	/// <summary>
	/// Factory function that initializes a Collider object.
	/// </summary>
	/// <param name="_type"> Collider shape </param>
	void CreateCollider(SHAPE _type);

	/// <summary>
	/// Factory function that initializes a Rigidbody. Requires a Collider before allowing Rigidbody creation.
	/// </summary>
	/// <param name="_type"> Rigidbody type </param>
	void CreateRigidbody(RBTYPE _type);

	/// <summary>
	/// Virtual collision function. Called when two Rigidbodies collide for the first time.
	/// </summary>
	/// <param name="_other"> Collided Rigidbody </param>
	virtual void OnCollisionEnter(std::shared_ptr<Rigidbody> _other);

	/// <summary>
	/// Virtual collision function. Called when two Rigidbodies have collided last frame and are colliding in the current frame.
	/// </summary>
	/// <param name="_other"> Collided Rigidbody </param>
	virtual void OnCollisionStay(std::shared_ptr<Rigidbody> _other);

	/// <summary>
	/// Virtual collision function. Called when two Rigidbodies have collided last frame and are no longer colliding.
	/// </summary>
	/// <param name="_other"> Collided Rigidbody </param>
	virtual void OnCollisionExit(std::shared_ptr<Rigidbody> _other);

	/// <summary>
	/// Returns the GameObject's Transform component.
	/// </summary>
	/// <returns> Transform component </returns>
	std::shared_ptr<Transform> GetTransform() { return mTransform; }

	/// <summary>
	/// Returns the GameObject's Rigidbody component.
	/// </summary>
	/// <returns> Rigidbody component </returns>
	std::shared_ptr<Rigidbody> GetRigidbody() { return mRigidbody; }

	/// <summary>
	/// Attaches the Event Manager component to the GameObject.
	/// </summary>
	/// <param name="_manager"> Event Manager </param>
	void AttachEventManager(std::shared_ptr<EventManager> _manager) { mEventManager = _manager; }

	/// <summary>
	/// Attaches the Time Manager component to the GameObject.
	/// </summary>
	/// <param name="_manager"> Time Manager </param>
	void AttachTimeManager(std::shared_ptr<TimeManager> _manager) { mTimeManager = _manager; }

	/// <summary>
	/// Attaches the Shader Manager component to the GameObject.
	/// </summary>
	/// <param name="_manager"> Shader Manager </param>
	void AttachShaderManager(std::shared_ptr<ShaderManager> _manager) { mShaderManager = _manager; }

	void UseCustomShader(const std::string& _key, const std::string& _generalPath);

	void UseCustomShader(const std::string& _key, const std::string& _vertexPath, const std::string& _fragmentPath);

	bool HasCustomShader() const noexcept { return mUsingCustomShader; }
protected:
	bool mKILL;

	std::shared_ptr<EventManager> mEventManager;
	std::shared_ptr<TimeManager> mTimeManager;
	std::shared_ptr<ShaderManager> mShaderManager;
	std::shared_ptr<ShaderProgram> mCustomShader;
	std::unique_ptr<ShaderStore> mShaderStore;

	std::shared_ptr<Transform> mTransform;
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Collider> mCollider;
	std::shared_ptr<Rigidbody> mRigidbody;
	
private:
	bool mUsingCustomShader;
};

