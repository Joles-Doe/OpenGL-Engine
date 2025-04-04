#include "DynamicBody.h"

DynamicBody::DynamicBody(std::shared_ptr<Transform> _transform)
{
	mTransform = _transform;
}

void DynamicBody::Update(float _deltaTime)
{
}
