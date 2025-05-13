#pragma once

#include "GameState.h"

#include "TitleText.h"
#include "TitleTextBG.h"
#include "EndScreen.h"
#include "Background.h"
#include "PipeSpawner.h"
#include "Player.h"
#include "GameManager.h"

class Game : public GameState, public std::enable_shared_from_this<Game>
{
public:
	Game(std::shared_ptr<Window> _win);

	void Load();
	void LoadNoStart();

	void Attach();
private:
	std::shared_ptr<TitleTextBG> mStartBG;
	std::shared_ptr<TitleText> mStartText;
	std::shared_ptr<EndScreen> mEndScreen;

	std::shared_ptr<Background> mBackground;
	std::shared_ptr<PipeSpawner> mSpawner;
	std::shared_ptr<GameManager> mGameManager;
	std::shared_ptr<Player> mPlayer;

	std::shared_ptr<GameObject> mTopBorder;
	std::shared_ptr<GameObject> mBottomBorder;
};