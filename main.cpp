#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <memory>
#include <random>

#include "SharedStructs&Enums.h"

#include "Window.h"
#include "Camera.h"
#include "GameObject.h"

#include "BallSpawner.h"
#include "Ball.h"

#undef main

int main()
{
	srand(time(NULL));
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "test");

	std::shared_ptr<Camera> cam = std::make_shared<Camera>(Camera::ORBIT);
	cam->AttachTimeManager(window.GetTimeManager());
	cam->AttachEventManager(window.GetEventManager());

	cam->Position(glm::vec3(0.0f, 5.0f, 8.0f));
	cam->Pitch(-10.0f);

	window.AddCamera(cam);

	//==============================
	// BOUNDS RIGHT
	std::shared_ptr<GameObject> rightBounds = std::make_shared<GameObject>(CUBE, RED);
	rightBounds->GetTransform()->Move(glm::vec3(10.0f, 0.0f, -15.0f));
	rightBounds->GetTransform()->Scale(glm::vec3(1.0f, 20.0f, 11.0f));
	rightBounds->AttachTimeManager(window.GetTimeManager());
	rightBounds->CreateCollider(CUBE);
	rightBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(rightBounds);
	window.EnableRigidbody(rightBounds->GetRigidbody());

	//==============================
	// BOUNDS BOTTOM
	std::shared_ptr<GameObject> bottomBounds = std::make_shared<GameObject>(CUBE, GREEN);
	bottomBounds->GetTransform()->Move(glm::vec3(0.0f, -10.0f, -15.0f));
	bottomBounds->GetTransform()->Scale(glm::vec3(21.0f, 1.0f, 11.0f));
	bottomBounds->AttachTimeManager(window.GetTimeManager());
	bottomBounds->CreateCollider(CUBE);
	bottomBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(bottomBounds);
	window.EnableRigidbody(bottomBounds->GetRigidbody());

	//==============================
	// BOUNDS LEFT
	std::shared_ptr<GameObject> leftBounds = std::make_shared<GameObject>(CUBE, RED);
	leftBounds->GetTransform()->Move(glm::vec3(-10.0f, 0.0f, -15.0f));
	leftBounds->GetTransform()->Scale(glm::vec3(1.0f, 20.0f, 11.0f));
	leftBounds->AttachTimeManager(window.GetTimeManager());
	leftBounds->CreateCollider(CUBE);
	leftBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(leftBounds);
	window.EnableRigidbody(leftBounds->GetRigidbody());

	//==============================
	// BOUNDS TOP
	std::shared_ptr<GameObject> topBounds = std::make_shared<GameObject>(CUBE, GREEN);
	topBounds->GetTransform()->Move(glm::vec3(0.0f, 10.0f, -15.0f));
	topBounds->GetTransform()->Scale(glm::vec3(21.0f, 1.0f, 11.0f));
	topBounds->AttachTimeManager(window.GetTimeManager());
	topBounds->CreateCollider(CUBE);
	topBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(topBounds);
	window.EnableRigidbody(topBounds->GetRigidbody());

	//==============================
	// BOUNDS BACK
	std::shared_ptr<GameObject> backBounds = std::make_shared<GameObject>(CUBE, BLUE);
	backBounds->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -20.0f));
	backBounds->GetTransform()->Scale(glm::vec3(20.0f, 21.0f, 1.0f));
	backBounds->AttachTimeManager(window.GetTimeManager());
	backBounds->CreateCollider(CUBE);
	backBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(backBounds);
	window.EnableRigidbody(backBounds->GetRigidbody());

	////==============================
	//// OBJ 1
	//std::shared_ptr<GameObject> back1 = std::make_shared<GameObject>(CUBE, PURPLE);
	//back1->GetTransform()->Move(glm::vec3(0.0f, 5.0f, -15.0f));
	//back1->AttachTimeManager(window.GetTimeManager());
	//back1->CreateCollider(CUBE);
	//back1->CreateRigidbody(DYNAMIC);

	//back1->GetRigidbody()->AddForce(glm::vec3(-80.0f, 0.0f, 0.0f));

	//window.AddObject(back1);
	//window.EnableRigidbody(back1->GetRigidbody());

	//==============================
	//BALL SPAWNER
	std::shared_ptr<BallSpawner> spawner = std::make_shared<BallSpawner>(CUBE, PURPLE);
	spawner->GetTransform()->Move(glm::vec3(0.0f, 9.0f, -15.0f));
	spawner->GetTransform()->Scale(glm::vec3(3.0f, 1.0f, 1.0f));
	spawner->AttachTimeManager(window.GetTimeManager());
	spawner->AttachEventManager(window.GetEventManager());
	
	window.AddObject(spawner);

	//==============================

	// Create the pegs
	std::shared_ptr<GameObject> peg;
	bool offsetPeg = true;
	for (float y = -8.0f; y < 8.0f; y += 3.0f)
	{
		offsetPeg = !offsetPeg;
		for (float x = -9.0f; x < 10.0f; x += 2.5f)
		{
			x += offsetPeg ? 1.5f : 0;
			peg = std::make_shared<GameObject>(CUBE, static_cast<COLOR>(3 + rand() % 3));
			peg->GetTransform()->Position(glm::vec3(x, y, -15.0f));
			peg->GetTransform()->Scale(glm::vec3(0.5f, 0.5f, 11.0f));
			peg->AttachTimeManager(window.GetTimeManager());
			peg->CreateCollider(CUBE);
			peg->CreateRigidbody(KINEMATIC);

			window.AddObject(peg);
			window.EnableRigidbody(peg->GetRigidbody());
			peg.reset();
		}
	}
	std::shared_ptr<Ball> ball;

	bool quit = false;
	while (!quit)
	{
		if (window.GetQuitState())
		{
			quit = true;
			break;
		}
		window.Update();

		if (spawner->GetSpawnBall())
		{
			spawner->SetSpawnBall(false);
			ball = std::make_shared<Ball>(SPHERE, static_cast<COLOR>(ORANGE));
			ball->GetTransform()->Position(spawner->GetTransform()->Position());
			ball->GetTransform()->Scale(glm::vec3(0.75f));
			ball->AttachTimeManager(window.GetTimeManager());
			ball->CreateCollider(SPHERE);
			ball->CreateRigidbody(DYNAMIC);

			ball->GetRigidbody()->Elasticity(0.5f);

			window.AddObject(ball);
			window.EnableRigidbody(ball->GetRigidbody());
			ball.reset();
		}
	}

	return 0;
}