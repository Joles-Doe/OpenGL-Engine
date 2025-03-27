#include "Window.h"

Window::Window(int _w, int _h, const std::string& _name) :
	mWindow(nullptr),
	mCurrentShader(nullptr),
	mMouseLocked(SDL_FALSE)
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

	for (int i = 0; i < mCameras.size(); i++)
	{
		mCameras[i]->Update();
	};

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

	/*if (mEventManager->GetKeyDown("a"))
	{
		mView = glm::translate(mView, glm::vec3(1, 0, 0));
	}
	if (mEventManager->GetKeyDown("d"))
	{
		mView = glm::translate(mView, glm::vec3(-1, 0, 0));
	}*/

	mCurrentShader->SetActive();

	mCurrentShader->SetUniform("uView", GetActiveCamera()->GetView());
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

std::shared_ptr<Camera> Window::GetActiveCamera()
{
	std::shared_ptr<Camera> topCam = mCameras[0];
	for (int i = 0; i < mCameras.size(); i++)
	{
		if (topCam->GetPriority() < mCameras[i]->GetPriority())
		{
			topCam = mCameras[i];
		}
	}
	return topCam;
}

void Window::AddCamera(std::shared_ptr<Camera> _cam)
{
	mCameras.push_back(_cam);
}

bool Window::GetQuitState()
{
	return mEventManager->GetQuitState();
}
