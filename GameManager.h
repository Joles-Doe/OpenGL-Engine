#pragma once

#include "GameObject.h"
#include "PipeSpawner.h"
#include "Player.h"

class GameManager : public GameObject
{
public:
	using GameObject::GameObject;

	void AttachPlayer(std::shared_ptr<Player> _p) { mPlayer = _p; }
	void AttachPipeSpawner(std::shared_ptr<PipeSpawner> _p) { mPipeSpawner = _p; }
	void AttachPipeSpawner(std::shared_ptr<GameObject> _b) { mTopBorder = _b; }
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<PipeSpawner> mPipeSpawner;
	std::shared_ptr<GameObject> mTopBorder;
};

