#pragma once

#include <vector>
#include <memory>

#include "CanvasObject.h"
#include "ShaderProgram.h"

class Canvas
{
public:
	bool IsKill();

	void Draw(std::shared_ptr<ShaderProgram> _shader);

	void AddCanvasObject(std::shared_ptr<CanvasObject> _obj) { mObjects.push_back(_obj); }
private:
	std::vector<std::shared_ptr<CanvasObject>> mObjects;
};