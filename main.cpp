#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <memory>
#include <random>

#include "SharedStructs&Enums.h"

#include "Window.h"
#include "Camera.h"
#include "GameObject.h"
#include "Canvas.h"

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
	// TEST
	std::shared_ptr<GameObject> test = std::make_shared<GameObject>(CUBE, ORANGE);
	test->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -15.0f));
	test->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	test->AttachTimeManager(window.GetTimeManager());

	window.AddObject(test);

	//==============================
	// TEST 2 CUSTOM SHADER
	std::shared_ptr<GameObject> testShader = std::make_shared<GameObject>(CUBE, ORANGE);
	testShader->GetTransform()->Move(glm::vec3(7.0f, 0.0f, -15.0f));
	testShader->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	testShader->AttachTimeManager(window.GetTimeManager());
	testShader->AttachShaderManager(window.GetShaderManager());

	testShader->UseCustomShader("TEST", "./data/shaders/TestVertexShader.vs", "./data/shaders/TestFragmentShader.fs");

	window.AddObject(testShader);

	//==============================
	// TEST 3 LIGHTING DIFFUSE
	std::shared_ptr<GameObject> testLightingD = std::make_shared<GameObject>("./data/models/curuthers/curuthers.obj", "./data/models/curuthers/Whiskers_diffuse.png");
	testLightingD->GetTransform()->Move(glm::vec3(-5.0f, 0.0f, -15.0f));
	testLightingD->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	testLightingD->AttachTimeManager(window.GetTimeManager());
	testLightingD->AttachShaderManager(window.GetShaderManager());

	testLightingD->UseCustomShader("LIGHTd", "./data/shaders/LightDiffuse");

	window.AddObject(testLightingD);

	//==============================
	// TEST 4 LIGHTING SPECULAR
	std::shared_ptr<GameObject> testLightingS = std::make_shared<GameObject>(SPHERE, GREEN);
	testLightingS->GetTransform()->Move(glm::vec3(-10.0f, 0.0f, -15.0f));
	testLightingS->GetTransform()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	testLightingS->AttachTimeManager(window.GetTimeManager());
	testLightingS->AttachShaderManager(window.GetShaderManager());

	testLightingS->UseCustomShader("LIGHTs", "./data/shaders/LightSpecular");

	window.AddObject(testLightingS);

	//==============================
	// TEST 4 HUD
	std::shared_ptr<Canvas> testCanvas = std::make_shared<Canvas>();
	std::shared_ptr<CanvasObject> testCanvasObject = std::make_shared<CanvasObject>(glm::vec2(0.0f, 0.0f), 300.0f, 300.0f);

	testCanvasObject->SetFillColor(PURPLE);
	
	testCanvas->AddCanvasObject(testCanvasObject);

	window.AddCanvas(testCanvas);

	//==============================

	bool quit = false;
	while (!quit)
	{
		if (window.GetQuitState())
		{
			quit = true;
			break;
		}
		window.Update();
	}

	return 0;
}