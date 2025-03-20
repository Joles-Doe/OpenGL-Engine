#include "EventManager.h"

void EventManager::ResetVariables()
{
	mKeyDown = false;
	mMouseDown = false;
}

void EventManager::PollEvents()
{
	ResetVariables();
	while (SDL_PollEvent(&mCurrentEvent))
	{
		switch (mCurrentEvent.type)
		{
		//Application
		case SDL_QUIT:
			mProgramQuit = true;
			break;
		//Keyboard
		//Keydown
		case SDL_KEYDOWN:
			mKeyDown = true;
			switch (mCurrentEvent.key.keysym.sym)
			{
			case SDLK_w:
				mWDown = true;
				break;
			case SDLK_a:
				mADown = true;
				break;
			case SDLK_s:
				mSDown = true;
				break;
			case SDLK_d:
				mDDown = true;
				break;
			case SDLK_SPACE:
				mSpaceDown = true;
				break;
			case SDLK_UP:
				mUpArrowDown = true;
				break;
			case SDLK_LEFT:
				mLeftArrowDown = true;
				break;
			case SDLK_DOWN:
				mDownArrowDown = true;
				break;
			case SDLK_RIGHT:
				mRightArrowDown = true;
				break;
			}
			break;
		//Keyup
		case SDL_KEYUP:
			switch (mCurrentEvent.key.keysym.sym)
			{
			case SDLK_w:
				mWDown = false;
				break;
			case SDLK_a:
				mADown = false;
				break;
			case SDLK_s:
				mSDown = false;
				break;
			case SDLK_d:
				mDDown = false;
				break;
			case SDLK_SPACE:
				mSpaceDown = false;
				break;
			case SDLK_UP:
				mUpArrowDown = false;
				break;
			case SDLK_LEFT:
				mLeftArrowDown = false;
				break;
			case SDLK_DOWN:
				mDownArrowDown = false;
				break;
			case SDLK_RIGHT:
				mRightArrowDown = false;
				break;
			}
			break;
		//Mouse
		//Mousedown
		case SDL_MOUSEBUTTONDOWN:
			mMouseDown = true;
			switch (mCurrentEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				mMouse1Down = true;
				break;
			case SDL_BUTTON_RIGHT:
				mMouse2Down = true;
				break;
			}
			break;
		//Mouseup
		case SDL_MOUSEBUTTONUP:
			switch (mCurrentEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				mMouse1Down = false;
				break;
			case SDL_BUTTON_RIGHT:
				mMouse2Down = false;
				break;
			}
			break;
		}

	}
}

bool EventManager::GetKeyDown(const std::string& _key)
{
	bool isDown{ false };
	if (_key == "W" || _key == "w")
	{
		isDown = mWDown;
	}
	if (_key == "A" || _key == "a")
	{
		isDown = mADown;
	}
	if (_key == "S" || _key == "s")
	{
		isDown = mSDown;
	}
	if (_key == "D" || _key == "d")
	{
		isDown = mDDown;
	}
	if (_key == "SPACEBAR" || _key == "spacebar" || _key == "SPACE" || _key == "space")
	{
		isDown = mSpaceDown;
	}
	if (_key == "up" || _key == "UP")
	{
		isDown = mUpArrowDown;
	}
	if (_key == "left" || _key == "LEFT")
	{
		isDown = mLeftArrowDown;
	}
	if (_key == "down" || _key == "DOWN")
	{
		isDown = mDownArrowDown;
	}
	if (_key == "right" || _key == "RIGHT")
	{
		isDown = mRightArrowDown;
	}
	return isDown;
}

bool EventManager::GetMouseDown(const std::string& _button)
{
	bool isDown{ false };
	if (_button == "1" || _button == "left" || _button == "LEFT" || _button == "l" || _button == "L")
	{
		isDown = mMouse1Down;
	}
	if (_button == "2" || _button == "right" || _button == "RIGHT" || _button == "r" || _button == "R")
	{
		isDown = mMouse2Down;
	}
	return isDown;
}
