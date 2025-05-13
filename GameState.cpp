#include "GameState.h"

GameState::GameState(std::shared_ptr<Window> _win) : mEXIT(false), mRESET(false)
{
	mWindow = _win;
}