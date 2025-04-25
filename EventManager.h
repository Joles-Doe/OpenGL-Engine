#pragma once

#include <SDL2/SDL.h>
#include <string>

struct MouseAxis
{
	int x;
	int y;
};

/// <summary>
/// Event Manager - uses SDL to handle all window, key and mouse input events
/// <para> 
/// Queries the SDL Event Queue, and handles all events in one location.
/// </para>
/// </summary>
class EventManager
{
public:
	/// <summary>
	/// Poll function called by the Window once per frame, to handle SDL events.
	/// </summary>
	void PollEvents();

	/// <summary>
	/// Returns the Quit state.
	/// </summary>
	/// <returns> The value of mProgramQuit </returns>
	bool GetQuitState() const noexcept { return mProgramQuit; }

	/// <summary>
	/// Explicity sets the Quit state. Used to force quit the program.
	/// </summary>
	/// <param name="_input"> New value </param>
	void SetQuitState(bool _input) noexcept { mProgramQuit = _input; }

	/// <summary>
	/// Returns a value dependent on whether the specified key has been pressed.
	/// </summary>
	/// <param name="_key"> Key to check </param>
	/// <returns> True or False dependent on if _key is held down. Also returns False if parameter is invalid. </returns>
	bool GetKeyDown(const std::string& _key) const;
	
	/// <summary>
	/// Returns a value dependent on whether any key has been pressed.
	/// </summary>
	/// <returns> True or False dependent on if any key is held down. </returns>
	bool GetKeyDown() const noexcept { return mKeyDown; }

	/// <summary>
	/// Returns a value dependent on whether the specified mouse button has been pressed.
	/// </summary>
	/// <param name="_button"> Mouse button to check </param>
	/// <returns> True or False dependent on if _button is held down. Also returns False if parameter is invalid. </returns>
	bool GetMouseDown(const std::string& _button) const;

	/// <summary>
	/// Returns a value dependent on whether any mouse button has been pressed.
	/// </summary>
	/// <returns> True or False dependent on if any mouse button is held down. </returns>
	bool GetMouseDown() const noexcept { return mMouseDown; }

	/// <summary>
	/// Returns a value dependent on whether the mouse has been moved.
	/// </summary>
	/// <returns> True or False dependent on if the mouse has moved since last frame. </returns>
	bool GetMouseMove() const noexcept { return mMouseMove; }

	/// <summary>
	/// Returns the relative direction the mouse has moved since last frame.
	/// </summary>
	/// <returns> A struct containing the relative X and Y movements of the mouse. </returns>
	MouseAxis GetMouseAxis() const noexcept { return mMouseMovement; }
private:
	//Holds the event during the poll sequence
	SDL_Event mCurrentEvent;

	/// <summary>
	/// Resets all event variables at the start of the frame.
	/// </summary>
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
};

