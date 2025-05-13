#pragma once

#include "GameObject.h"

class Pipe : public GameObject
{
public:
	using GameObject::GameObject;

	void Start();
	void Update();

	void SetFreeze(bool _val) { mFreeze = _val; }
private:
	bool mFreeze;

	float mTimer;
};

