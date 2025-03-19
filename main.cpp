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

	window.AddObject(&testModel);

	bool quit = false;
	SDL_Event e{ 0 };
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		window.Update();
	}

	return 0;
}