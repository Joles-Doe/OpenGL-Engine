#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	using GameObject::GameObject;

	void OnCollisionEnter(std::shared_ptr<Rigidbody> _other) override;
};
