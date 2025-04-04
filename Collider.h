#pragma once

#include <glm/glm.hpp>

#include "SharedStructs&Enums.h"

#include "Model.h"
#include "Transform.h"

class Collider
{
public:
	Collider(SHAPE _type, std::vector<Model::Face>* _faces, std::shared_ptr<Transform> _transform);

	SHAPE GetShape();

	bool IsColliding(Collider &_other);
private:
	std::shared_ptr<Transform> mTransform;

	bool CubeToCube(Collider& _other);
	bool CubeToSphere(Collider& _cube, Collider& _sphere);
	bool SphereToSphere(Collider& _other);

	SHAPE mType;

	glm::vec3 mCenter;
	glm::vec3 mCenterOffset;

	float mWidth;
	float mHeight;
	float mDepth;

	float mRadius;
};

