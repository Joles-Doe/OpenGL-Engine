#pragma once

#include "GameObject.h"
#include "Pipe.h"

class Player : public GameObject
{
public:
	using GameObject::GameObject;

	void Start();
	void Update();

	void OnCollisionEnter(std::shared_ptr<Rigidbody> _other);

	bool GetFreeze() { return mFreeze; }
	void SetFreeze(bool _val) { mFreeze = _val; }
	bool GetJump() { return mCanJump; }
	void SetJump(bool _val) { mCanJump = _val; }
	bool GetDead() const { return mDead; }
private:
	bool mFreeze;
	bool mFirstUnfroze;
	bool mCanJump;
	bool mDead;
};

