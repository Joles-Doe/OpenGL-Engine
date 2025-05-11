#pragma once

#include "GameObject.h"

class Pipe : public GameObject
{
public:
	using GameObject::GameObject;

	void Update();

	void SetFreeze(bool _val) { mFreeze = _val; }
private:
	bool mFreeze;
};

