#pragma once

#include "HUDObject.h"
#include "GameState.h"

class EndScreen : public HUDObject
{
public:
	using HUDObject::HUDObject;

	void AttachGameState(std::shared_ptr<GameState> _state) { mGameState = _state; }

	void Start();

	void Update();

	void OnClick();

private:
	std::shared_ptr<GameState> mGameState;

	float mRadius;
	bool mCanClose;
};

