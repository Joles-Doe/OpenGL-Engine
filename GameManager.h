#pragma once

#include "GameObject.h"
#include "HUDObject.h"
#include "PipeSpawner.h"
#include "Player.h"
#include "EndScreen.h"

class GameManager : public GameObject
{
public:
	using GameObject::GameObject;

	void Start();
	void Update();

	void AttachPlayer(std::shared_ptr<Player> _p) { mPlayer = _p; }
	void AttachPipeSpawner(std::shared_ptr<PipeSpawner> _p) { mPipeSpawner = _p; }
	void AttachPipeSpawner(std::shared_ptr<GameObject> _b) { mTopBorder = _b; }
	void AttachBG(std::shared_ptr<HUDObject> _b) { mStartBG = _b; }
	void AttachEndScreen(std::shared_ptr<HUDObject> _e) { mEndScreen = _e; }
	void AttachTopBorder(std::shared_ptr<GameObject> _b) { mTopBorder = _b; }
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<PipeSpawner> mPipeSpawner;
	std::shared_ptr<GameObject> mTopBorder;
	std::weak_ptr<HUDObject> mStartBG;
	std::shared_ptr<HUDObject> mEndScreen;

	bool mStartGame;
	bool mEndGame;
	float mTimer;

	bool mBorderMoved;
	bool mPlayerOnScreen;
};