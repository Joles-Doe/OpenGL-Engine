#include "Window.h"

Window::Window(int _w, int _h, const std::string& _name) :
	mWindow(nullptr),
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

	mShaderManager = std::make_shared<ShaderManager>();
	mDefaultShader = mShaderManager->GetShader("DEFAULT");

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	mPerspectiveProjection = glm::perspective(45.0f, ((float)_w / (float)_h), 0.1f, 100.0f);
	mOrthoProjection = glm::ortho(0.0f, (float)_w, 0.0f, (float)_h);
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
	CullDeletedCanvases();

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
		mPerspectiveProjection = glm::perspective(45.0f, ((float)windowWidth / (float)windowHeight), 0.1f, 100.0f);
		mOrthoProjection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f);

		mPrevWidth = windowWidth;
		mPrevHeight = windowHeight;
	}

	//Clear buffers before rendering
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set active shader
	mDefaultShader->SetActive();

	//Upload uniforms { TURN INTO A UNIFORM BUFFER OBJECT EVENTUALLY }
	mDefaultShader->SetUniform("uView", GetActiveCamera()->GetView());
	mDefaultShader->SetUniform("uViewPos", GetActiveCamera()->Position());
	mDefaultShader->SetUniform("uProjection", mPerspectiveProjection);

	//Render objects
	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i]->HasCustomShader())
		{
			//std::cout << i << " custom" << std::endl;
			mObjects[i]->Draw(GetActiveCamera()->GetView(), GetActiveCamera()->Position(), mPerspectiveProjection);
		}
		else
		{
			//std::cout << i << " default" << std::endl;
			mDefaultShader->SetActive();
			mObjects[i]->Draw(mDefaultShader);
		}
	}

	mDefaultShader->SetActive();
	mDefaultShader->SetUniform("uView", glm::mat4(1.0f));
	mDefaultShader->SetUniform("uProjection", mOrthoProjection);
	//Render HUD
	for (int i = 0; i < mCanvases.size(); i++)
	{
		mCanvases[i]->Draw(mDefaultShader);
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

void Window::AddCanvas(std::shared_ptr<Canvas> _obj)
{
	mCanvases.push_back(_obj);
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
				return (obj->IsKill() || obj.unique()); // true = remove it
			}),
		mObjects.end());
}

void Window::CullDeletedCanvases()
{
	mCanvases.erase(
		std::remove_if(mCanvases.begin(), mCanvases.end(),
			[](const std::shared_ptr<Canvas>& obj) {
				return (obj->IsKill() || obj.unique()); // true = remove it
			}),
		mCanvases.end());
}
