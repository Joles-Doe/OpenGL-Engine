#include "Window.h"

Window::Window(int _w, int _h, const std::string& _name) :
	mWindow(nullptr),
	mCurrentShader(nullptr),
	mMouseLocked(SDL_FALSE),
	mPrevWidth(_w),
	mPrevHeight(_h),
	mFirstFrameRendered(false),
	mEnablePhysics(false)
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

	mTimeManager = std::make_shared<TimeManager>();

	mPhysicsManager = std::make_shared<PhysicsManager>(mTimeManager);

	mEventManager = std::make_shared<EventManager>();

	mCurrentShader = std::make_shared<ShaderProgram>();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	mProjection = glm::perspective(45.0f, ((float)_w / (float)_h), 0.1f, 100.0f);
}

Window::~Window()
{
	SDL_GL_DeleteContext(mWindow);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Window::Update()
{
	//Calculate DeltaTime
	mTimeManager->Update();

	//Handle inputs
	mEventManager->PollEvents();
	
	//Remove dead objects
	CullDeletedObjects();

	//Handle physics
	if (mEnablePhysics)
	{
		mPhysicsManager->Update();
	}

	//Update cameras
	for (int i = 0; i < mCameras.size(); i++)
	{
		mCameras[i]->Update();
	};

	//Update objects
	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->Update();
	}

	//Calculate window size in case of resize
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);

	if (windowWidth != mPrevWidth || windowHeight != mPrevHeight)
	{
		glViewport(0, 0, windowWidth, windowHeight);
		mProjection = glm::perspective(45.0f, ((float)windowWidth / (float)windowHeight), 0.1f, 100.0f);

		mPrevWidth = windowWidth;
		mPrevHeight = windowHeight;
	}

	//Clear buffers before rendering
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set active shader
	mCurrentShader->SetActive();

	//Upload matrices
	mCurrentShader->SetUniform("uView", GetActiveCamera()->GetView());
	mCurrentShader->SetUniform("uProjection", mProjection);

	//Render objects
	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->Draw(mCurrentShader);
	}

	//Reset program
	glUseProgram(0);

	if (!mFirstFrameRendered)
	{
		mFirstFrameRendered = true;
		mEnablePhysics = true;
	}

	//Swap buffers and wait until next frame
	SDL_GL_SwapWindow(mWindow);
	mTimeManager->Wait();
}

void Window::AddObject(std::shared_ptr<GameObject> _obj)
{
	mObjects.push_back(_obj);
	_obj->Start();
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

void Window::CullDeletedObjects()
{
	mObjects.erase(
		std::remove_if(mObjects.begin(), mObjects.end(),
			[](const std::shared_ptr<GameObject>& obj) {
				return obj->IsKill(); // true = remove it
			}),
		mObjects.end());
}