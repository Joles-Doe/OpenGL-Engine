#include "Window.h"

Window::Window(int _w, int _h, const std::string& _name) :
	mWindow(nullptr),
	mCurrentShader(nullptr),
	mMouseLocked(SDL_FALSE),
	mCamera()
{
	mWindow = SDL_CreateWindow(_name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_w, _h,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(mWindow))
	{
		throw std::runtime_error("SDL GL context error");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("GLEW initialisation error");
	}

	mEventManager = std::make_shared<EventManager>();

	mCurrentShader = std::make_shared<ShaderProgram>();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	mProjection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	mCamera.AttachEventManager(mEventManager);
}

Window::~Window()
{
	SDL_GL_DeleteContext(mWindow);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Window::Update()
{
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Inputs
	mEventManager->PollEvents();

	mCamera.Update();

	if (mEventManager->GetKeyDown("right"))
	{
		if (mMouseLocked == SDL_TRUE)
		{
			mMouseLocked = SDL_FALSE;
		}
		else
		{
			mMouseLocked = SDL_TRUE;
		}
		SDL_SetRelativeMouseMode(mMouseLocked);
	}

	/*if (mEventManager->GetMouseMove())
	{
		MouseAxis currentAxis = mEventManager->GetMouseAxis();

		mView = glm::rotate(mView, glm::radians(((float)currentAxis.x) * 0.1f), glm::vec3(0, 1, 0));
	}*/

	/*if (mEventManager->GetMouseMove())
	{
		float angleX = 0;
		float angleY = 0;

		int x = 0;
		int y = 0;

		MouseAxis currentAxis = mEventManager->GetMouseAxis();
		if (currentAxis.x < 0)
		{
			angleX = -10;
			x = 1;
		}
		else if (currentAxis.x > 0)
		{
			angleX = 10;
			x = 1;
		}
		
		if (currentAxis.y < 0)
		{
			angleY = -10;
			y = 1;
		}
		else if (currentAxis.y > 0)
		{
			angleY = 10;
			y = 1;
		}
		mView = glm::rotate(mView, glm::radians(angleX), glm::vec3(1, 0, 0));
		mView = glm::rotate(mView, glm::radians(angleY), glm::vec3(0, 1, 0));
	}*/
	/*if (mEventManager->GetKeyDown("a"))
	{
		mView = glm::translate(mView, glm::vec3(1, 0, 0));
	}
	if (mEventManager->GetKeyDown("d"))
	{
		mView = glm::translate(mView, glm::vec3(-1, 0, 0));
	}*/

	mCurrentShader->SetActive();

	mCurrentShader->SetUniform("uView", mCamera.GetView());
	mCurrentShader->SetUniform("uProjection", mProjection);

	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->Update();
		mObjects[i]->Draw(mCurrentShader);
	}

	glUseProgram(0);

	SDL_GL_SwapWindow(mWindow);
}

void Window::AddObject(std::shared_ptr<GameObject> _obj)
{
	mObjects.push_back(_obj);
}

bool Window::GetQuitState()
{
	return mEventManager->GetQuitState();
}
