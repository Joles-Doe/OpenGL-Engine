#pragma once

#include "Window.h"

class GameState
{
public:
	GameState(std::shared_ptr<Window> _win);

	virtual void Load() {};

	bool GetExit() const noexcept { return mEXIT; }
	bool GetReset() const noexcept { return mRESET; }
protected:
	std::shared_ptr<Window> mWindow;

	bool mEXIT;
	bool mRESET;
};