#include "Game.h"

Game::Game(std::shared_ptr<Window> _win) : GameState(_win)
{
	Load();
}

void Game::Load()
{
	//==============================
	// START SCREEN BG
	mStartBG = std::make_shared<TitleTextBG>(glm::vec2(0, 0), mWindow->GetWindowSize().x, mWindow->GetWindowSize().y);
	mStartBG->AttachEventManager(mWindow->GetEventManager());
	mStartBG->AttachTimeManager(mWindow->GetTimeManager());
	mStartBG->AttachShaderManager(mWindow->GetShaderManager());
	mStartBG->UseCustomShader("HUDBG", "./data/shaders/TitleHUD");

	mStartBG->SetFillColor(RED);

	mWindow->AddHUDObject(mStartBG);

	//==============================
	// START SCREEN TEXT
	mStartText = std::make_shared<TitleText>(glm::vec2(0, 0), mWindow->GetWindowSize().x, mWindow->GetWindowSize().y);
	mStartText->SetImage("./data/hud/Title Text.png");

	mWindow->AddHUDObject(mStartText);


	// Load GameObjects
	LoadNoStart();
}

void Game::LoadNoStart()
{
	////==============================
	//// TEST 2 CUSTOM SHADER
	//std::shared_ptr<GameObject> testShader = std::make_shared<GameObject>(CUBE, ORANGE);
	//testShader->GetTransform()->Move(glm::vec3(7.0f, 0.0f, -15.0f));
	//testShader->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	//testShader->AttachTimeManager(window.GetTimeManager());
	//testShader->AttachShaderManager(window.GetShaderManager());

	//testShader->UseCustomShader("DISTANCE", "./data/shaders/DistanceHeat");

	//window.AddObject(testShader);

	//==============================
	// BACKGROUND
	mBackground = std::make_shared<Background>(CUBE, GREEN);
	mBackground->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -15.0f));
	mBackground->GetTransform()->Scale(glm::vec3(50.0f, 50.0f, 1.0f));
	mBackground->AttachTimeManager(mWindow->GetTimeManager());
	mBackground->AttachShaderManager(mWindow->GetShaderManager());

	mBackground->UseCustomShader("BACKGROUND", "./data/shaders/Plasma");

	mWindow->AddObject(mBackground);

}
