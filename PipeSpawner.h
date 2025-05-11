#pragma once

#include "Window.h"
#include "GameObject.h"
#include "Pipe.h"

class PipeSpawner : public GameObject
{
public:
	using GameObject::GameObject;

	void AttachWindow(std::shared_ptr<Window> _win) { mWindow = _win; }

	void SpawnPipe();

	void Update();

	void FreezePipes();
	void CullPipes();
private:
	std::shared_ptr<Window> mWindow;

	std::vector<std::shared_ptr<Pipe>> mPipes;
};

