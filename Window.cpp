#include "Window.h"

Window::Window(int _w, int _h, const std::string& _name) : 
	mWindow(nullptr),
	mCurrentShader(nullptr)
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

	mEventManager = new EventManager();

	mCurrentShader = new ShaderProgram();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	mProjection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	mView = glm::mat4(1.0f);
	
}

Window::~Window()
{
	delete mEventManager;
	delete mCurrentShader;

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

	// Instruct OpenGL to use our shader program, VAO and texture
	mCurrentShader->SetActive();

	mCurrentShader->SetUniform("uView", mView);
	mCurrentShader->SetUniform("uProjection", mProjection);

	mEventManager->PollEvents();

	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->Update();
		mObjects[i]->Draw(mCurrentShader);
	}

	glUseProgram(0);

	SDL_GL_SwapWindow(mWindow);
}

void Window::AddObject(GameObject* _obj)
{
	std::shared_ptr<GameObject> newPtr(_obj);
	mObjects.push_back(newPtr);
}

bool Window::GetQuitState()
{
	return mEventManager->GetQuitState();
}
