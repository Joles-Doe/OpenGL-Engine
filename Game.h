#pragma once

#include "GameState.h"

#include "TitleText.h"
#include "TitleTextBG.h"
#include "Background.h"

class Game : public GameState
{
public:
	Game(std::shared_ptr<Window> _win);

	void Load();
	void LoadNoStart();

private:
	std::shared_ptr<TitleTextBG> mStartBG;
	std::shared_ptr<TitleText> mStartText;

	std::shared_ptr<Background> mBackground;
};