#pragma once

#include "GameObject.h"

class BallSpawner : public GameObject
{
public:
	using GameObject::GameObject;

	void Start();
	void Update();

	bool GetSpawnBall();
	void SetSpawnBall(bool _spawn);

	bool GetMoveLeft();
private:
	float mSpawnTimer;
	float mSpawnDelay;
	bool mSpawnBall;

	bool mMoveLeft;
};

