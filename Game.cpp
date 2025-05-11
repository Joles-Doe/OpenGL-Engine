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
	//// TEST
	//test = std::make_shared<GameObject>(CUBE, ORANGE);
	//test->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -12.0f));
	//test->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	//test->AttachTimeManager(mWindow->GetTimeManager());

	//test->CreateCollider(CUBE);
	//test->CreateRigidbody(KINEMATIC);

	//mWindow->AddObject(test);
	//mWindow->EnableRigidbody(test->GetRigidbody());

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
	
	//==============================
	// BORDER TOP
	mTopBorder = std::make_shared<GameObject>(CUBE, PURPLE);
	mTopBorder->GetTransform()->Position(glm::vec3(0.0f, 7.8f, -12.0f));
	mTopBorder->GetTransform()->Scale(glm::vec3(10.0f, 1.0f, 1.0f));

	mWindow->AddObject(mTopBorder);

	//==============================
	// BORDER BOTTOM
	mBottomBorder = std::make_shared<GameObject>(CUBE, PURPLE);
	mBottomBorder->GetTransform()->Position(glm::vec3(0.0f, -17.5f, -12.0f));
	mBottomBorder->GetTransform()->Scale(glm::vec3(50.0f, 1.0f, 1.0f));

	mBottomBorder->CreateCollider(CUBE);
	mBottomBorder->CreateRigidbody(KINEMATIC);

	mWindow->AddObject(mBottomBorder);
	mWindow->EnableRigidbody(mBottomBorder->GetRigidbody());

	//==============================
	// SPAWNER
	mSpawner = std::make_shared<PipeSpawner>(CUBE);
	mSpawner->GetTransform()->Position(glm::vec3(-30.0f, -30.0f, 0.0f));
	mSpawner->AttachWindow(mWindow);

	mWindow->AddObject(mSpawner);

	//==============================
	// PLAYER
	mPlayer = std::make_shared<Player>(CUBE);
	mPlayer->GetTransform()->Position(glm::vec3(-1.0f, 10.0f, -12.0f));
	mPlayer->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	mPlayer->AttachEventManager(mWindow->GetEventManager());
	mPlayer->AttachTimeManager(mWindow->GetTimeManager());
	
	mPlayer->CreateCollider(CUBE);
	mPlayer->CreateRigidbody(DYNAMIC);

	mPlayer->SetFreeze(false);
	mPlayer->SetJump(true);

	mWindow->AddObject(mPlayer);
	mWindow->EnableRigidbody(mPlayer->GetRigidbody());

	//==============================
	mGameManager = std::make_shared<GameManager>(CUBE);
	mGameManager->GetTransform()->Position(glm::vec3(-30.0f, -30.0f, 0.0f));

}