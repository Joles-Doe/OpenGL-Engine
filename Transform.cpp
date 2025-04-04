#include "Transform.h"

Transform::Transform()
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotation = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
}

void Transform::Move(glm::vec3 _movement)
{
	mPosition += _movement;
}

void Transform::Rotate(glm::vec3 _rot)
{
	mRotation += _rot;
}

void Transform::Position(glm::vec3 _pos)
{
	mPosition = _pos;
}

glm::vec3 Transform::Position()
{
	return mPosition;
}

void Transform::Rotation(glm::vec3 _rot)
{
	mRotation = _rot;
}

glm::vec3 Transform::Rotation()
{
	return mRotation;
}

void Transform::Scale(glm::vec3 _scale)
{
	mScale = _scale;
}

glm::vec3 Transform::Scale()
{
	return mScale;
}
