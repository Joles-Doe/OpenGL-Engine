#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <memory>

#include "SharedStructs&Enums.h"

#include "Window.h"
#include "Camera.h"
#include "GameObject.h"

#undef main

int main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "test");

	std::shared_ptr<Camera> cam = std::make_shared<Camera>(Camera::ORBIT);
	cam->AttachTimeManager(window.GetTimeManager());
	cam->AttachEventManager(window.GetEventManager());
	window.AddCamera(cam);

	//std::shared_ptr<GameObject> testModel = std::make_shared<GameObject>("./data/models/curuthers/curuthers.obj", 
	//	"./data/models/curuthers/Whiskers_diffuse.png");
	//testModel->AttachEventManager(window.GetEventManager());

	//testModel->Move(glm::vec3(0.0f, 0.0f, -15.0f));

	//window.AddObject(testModel);

	//==============================

	glDisable(GL_CULL_FACE);
	std::shared_ptr<GameObject> testModel = std::make_shared<GameObject>("./data/models/primitives/sphere/Primitive_SPHERE.obj",
		"./data/models/primitives/colors/skybox.png");
	testModel->AttachTimeManager(window.GetTimeManager());
	testModel->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -5.0f));
	testModel->GetTransform()->Scale(glm::vec3(50.0f, 50.0f, 50.0f));

	window.AddObject(testModel);

	//==============================

	std::shared_ptr<GameObject> testModel2 = std::make_shared<GameObject>("./data/models/curuthers/curuthers.obj",
		"./data/models/curuthers/Whiskers_diffuse.png");
	testModel2->AttachEventManager(window.GetEventManager());
	testModel2->AttachTimeManager(window.GetTimeManager());

	testModel2->GetTransform()->Move(glm::vec3(5.0f, 0.0f, -15.0f));
	testModel2->GetTransform()->Rotate(glm::vec3(0.0f, 0.0f, 45.0f));

	window.AddObject(testModel2);

	//==============================

	std::shared_ptr<GameObject> testModel3 = std::make_shared<GameObject>(SPHERE, ORANGE);
	testModel3->GetTransform()->Move(glm::vec3(0.0f, 0.0f, -5.0f));
	testModel3->AttachTimeManager(window.GetTimeManager());
	testModel3->CreateCollider(SPHERE);
	testModel3->CreateRigidbody(DYNAMIC);

	window.AddObject(testModel3);
	window.EnableRigidbody(testModel3->GetRigidbody());

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