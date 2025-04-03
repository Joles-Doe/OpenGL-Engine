#pragma once

#include <glm/glm.hpp>

#include "Model.h"

class Collider
{
public:
	enum SHAPE
	{
		CUBE,
		SPHERE
	};

	Collider(SHAPE _type, std::vector<Model::Face>* _faces);

	SHAPE GetShape() { return mType; }
private:
	SHAPE mType;

	glm::vec3 mBottomLeft;
	glm::vec3 mTopRight;

	glm::vec3 mCenter;

	float mWidth;
	float mHeight;

	float mRadius;
};

