#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#include <memory>
#include <random>

#include "SharedStructs&Enums.h"

#include "Window.h"
#include "Camera.h"
#include "GameObject.h"
#include "HUDObject.h"

#include "TitleText.h"
#include "TitleTextBG.h"

#undef main

int main()
{
	srand(time(NULL));

	std::shared_ptr<Window> window = std::make_shared<Window>(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
	window->Init();

	std::shared_ptr<Camera> cam = std::make_shared<Camera>(Camera::STATIC);
	cam->AttachTimeManager(window->GetTimeManager());
	cam->AttachEventManager(window->GetEventManager());

	cam->Position(glm::vec3(0.0f, 0.0f, 8.0f));
	cam->Pitch(-10.0f);

	window->AddCamera(cam);

	////==============================
	//// TEST
	//std::shared_ptr<GameObject> test = std::make_shared<GameObject>(CUBE, ORANGE);
	//test->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -15.0f));
	//test->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	//test->AttachTimeManager(window.GetTimeManager());

	//window.AddObject(test);

	////==============================
	//// TEST 2 CUSTOM SHADER
	//std::shared_ptr<GameObject> testShader = std::make_shared<GameObject>(CUBE, ORANGE);
	//testShader->GetTransform()->Move(glm::vec3(7.0f, 0.0f, -15.0f));
	//testShader->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	//testShader->AttachTimeManager(window.GetTimeManager());
	//testShader->AttachShaderManager(window.GetShaderManager());

	//testShader->UseCustomShader("DISTANCE", "./data/shaders/DistanceHeat");

	//window.AddObject(testShader);

	////==============================
	//// TEST 3 LIGHTING DIFFUSE
	//std::shared_ptr<GameObject> testLightingD = std::make_shared<GameObject>("./data/models/curuthers/curuthers.obj", "./data/models/curuthers/Whiskers_diffuse.png");
	//testLightingD->GetTransform()->Move(glm::vec3(-5.0f, 0.0f, -15.0f));
	//testLightingD->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	//testLightingD->AttachTimeManager(window.GetTimeManager());
	//testLightingD->AttachShaderManager(window.GetShaderManager());

	//testLightingD->UseCustomShader("LIGHTd", "./data/shaders/LightDiffuse");

	//window.AddObject(testLightingD);

	////==============================
	//// TEST 4 LIGHTING SPECULAR
	//std::shared_ptr<GameObject> testLightingS = std::make_shared<GameObject>(SPHERE, GREEN);
	//testLightingS->GetTransform()->Move(glm::vec3(-10.0f, 0.0f, -15.0f));
	//testLightingS->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	//testLightingS->AttachTimeManager(window.GetTimeManager());
	//testLightingS->AttachShaderManager(window.GetShaderManager());

	//testLightingS->UseCustomShader("LIGHTs", "./data/shaders/LightSpecular");

	//window.AddObject(testLightingS);

	////==============================

	bool quit = false;
	while (!quit)
	{
		if (window->GetQuitState())
		{
			quit = true;
			break;
		}
		window->Update();
	}

	return 0;
}