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

	//window.AddObject(testModel2);

	////==============================

	//std::shared_ptr<GameObject> testModel3 = std::make_shared<GameObject>(CUBE, ORANGE);
	//testModel3->GetTransform()->Move(glm::vec3(0.0f, 50.0f, -5.0f));
	//testModel3->AttachTimeManager(window.GetTimeManager());
	//testModel3->CreateCollider(CUBE);
	//testModel3->CreateRigidbody(DYNAMIC);

	//window.AddObject(testModel3);
	//window.EnableRigidbody(testModel3->GetRigidbody());

	////==============================

	//std::shared_ptr<GameObject> testModel4 = std::make_shared<GameObject>(CUBE, RED);
	//testModel4->GetTransform()->Move(glm::vec3(0.5f, 0.0f, -5.0f));
	//testModel4->AttachTimeManager(window.GetTimeManager());
	//testModel4->CreateCollider(CUBE);
	//testModel4->CreateRigidbody(KINEMATIC);

	//window.AddObject(testModel4);
	//window.EnableRigidbody(testModel4->GetRigidbody());

	//==============================
	// BOUNDS RIGHT
	std::shared_ptr<GameObject> rightBounds = std::make_shared<GameObject>(CUBE, PURPLE);
	rightBounds->GetTransform()->Move(glm::vec3(5.0f, 0.0f, -15.0f));
	rightBounds->GetTransform()->Scale(glm::vec3(1.0f, 10.0f, 10.0f));
	rightBounds->AttachTimeManager(window.GetTimeManager());
	rightBounds->CreateCollider(CUBE);
	rightBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(rightBounds);
	window.EnableRigidbody(rightBounds->GetRigidbody());

	//==============================
	// BOUNDS BOTTOM
	std::shared_ptr<GameObject> bottomBounds = std::make_shared<GameObject>(CUBE, PURPLE);
	bottomBounds->GetTransform()->Move(glm::vec3(0.0f, -6.0f, -15.0f));
	bottomBounds->GetTransform()->Scale(glm::vec3(10.0f, 1.0f, 10.0f));
	bottomBounds->AttachTimeManager(window.GetTimeManager());
	bottomBounds->CreateCollider(CUBE);
	bottomBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(bottomBounds);
	window.EnableRigidbody(bottomBounds->GetRigidbody());

	//==============================
	// BOUNDS LEFT
	std::shared_ptr<GameObject> leftBounds = std::make_shared<GameObject>(CUBE, PURPLE);
	leftBounds->GetTransform()->Move(glm::vec3(-5.0f, 0.0f, -15.0f));
	leftBounds->GetTransform()->Scale(glm::vec3(1.0f, 10.0f, 10.0f));
	leftBounds->AttachTimeManager(window.GetTimeManager());
	leftBounds->CreateCollider(CUBE);
	leftBounds->CreateRigidbody(KINEMATIC);

	window.AddObject(leftBounds);
	window.EnableRigidbody(leftBounds->GetRigidbody());

	//==============================
	//==============================
	// OBJ 1
	std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>(SPHERE, ORANGE);
	obj1->GetTransform()->Move(glm::vec3(-2.0f, 0.0f, -15.0f));
	obj1->AttachTimeManager(window.GetTimeManager());
	obj1->CreateCollider(CUBE);
	obj1->CreateRigidbody(DYNAMIC);

	obj1->GetRigidbody()->AddForce(glm::vec3(20.0f, 0.0f, 0.0f));

	window.AddObject(obj1);
	window.EnableRigidbody(obj1->GetRigidbody());

	//==============================
	// OBJ 2
	std::shared_ptr<GameObject> obj2 = std::make_shared<GameObject>(SPHERE, BLUE);
	obj2->GetTransform()->Move(glm::vec3(2.0f, 0.0f, -15.0f));
	obj2->AttachTimeManager(window.GetTimeManager());
	obj2->CreateCollider(CUBE);
	obj2->CreateRigidbody(DYNAMIC);

	obj2->GetRigidbody()->AddForce(glm::vec3(-2.0f, 0.0f, 0.0f));

	window.AddObject(obj2);
	window.EnableRigidbody(obj2->GetRigidbody());





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