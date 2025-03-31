#pragma once

#include <SDL2/SDL.h>
#include <string>

struct MouseAxis
{
	int x;
	int y;
};

class EventManager
{
private:
	//Holds the event during the poll sequence
	SDL_Event mCurrentEvent;

	//Resets all event variables
	void ResetVariables();

	//Event variables
	//Application
	bool mProgramQuit{ false };
	//Keyboard
	bool mKeyDown{ false };
	//Keyboard specific
	bool mWDown{ false };
	bool mADown{ false };
	bool mSDown{ false };
	bool mDDown{ false };
	bool mEDown{ false };
	bool mQDown{ false };
	bool mUpArrowDown{ false };
	bool mLeftArrowDown{ false };
	bool mDownArrowDown{ false };
	bool mRightArrowDown{ false };
	bool mSpaceDown{ false };
	//Mouse
	bool mMouseDown{ false };
	bool mMouseMove{ false };
	//Mouse specific
	bool mMouse1Down{ false };
	bool mMouse2Down{ false };
	MouseAxis mMouseMovement;

public:
	//Polls all events
	void PollEvents();

	//Getters and Setters for the mProgramQuit variable	
	bool GetQuitState() { return mProgramQuit; }
	void SetQuitState(bool _input) { mProgramQuit = _input; }

	//Returns true or false if specific key has been pressed
	bool GetKeyDown(const std::string& _key);
	//Returns true or false if any key has been pressed
	bool GetKeyDown() { return mKeyDown; }

	//Returns true or false if specific mouse button has been pressed
	bool GetMouseDown(const std::string& _button);
	//Returns true or false if any mouse button has been pressed
	bool GetMouseDown() { return mMouseDown; }

	bool GetMouseMove() { return mMouseMove; }
	MouseAxis GetMouseAxis() { return mMouseMovement; }
};

