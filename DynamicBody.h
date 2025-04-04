#pragma once

#include <memory>

#include "Transform.h"

class DynamicBody
{
public:
	DynamicBody(std::shared_ptr<Transform> _transform);

	void Update(float _deltaTime);

private:
	std::shared_ptr<Transform> mTransform;
};