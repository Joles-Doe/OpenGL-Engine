#pragma once

#include "Window.h"

class GameState
{
public:
	GameState(std::shared_ptr<Window> _win);

	virtual void Load() {};
	virtual void Attach() {};

	bool GetExit() const noexcept { return mEXIT; }
	void SetExit(bool _val) noexcept { mEXIT = _val; }

	bool GetReset() const noexcept { return mRESET; }
protected:
	std::shared_ptr<Window> mWindow;

	bool mEXIT;
	bool mRESET;
};