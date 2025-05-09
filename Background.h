#pragma once

#include "GameObject.h"

class Background : public GameObject
{
public:
	using GameObject::GameObject;

	void Start();
	void Update();

private:
	float mTimer;
};

