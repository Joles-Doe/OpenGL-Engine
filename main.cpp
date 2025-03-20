#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include "Window.h"
#include "GameObject.h"

#undef main

int main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "test");

	GameObject testModel("./data/models/curuthers/curuthers.obj", 
		"./data/models/curuthers/Whiskers_diffuse.png");
	testModel.AttachEventManager(window.GetEventManager());

	window.AddObject(&testModel);

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