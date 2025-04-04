#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


class Transform
{
public:
	Transform();

	void Move(glm::vec3 _movement);
	void Rotate(glm::vec3 _rot);

	void Position(glm::vec3 _pos);
	glm::vec3 Position();

	void Rotation(glm::vec3 _rot);
	glm::vec3 Rotation();

	void Scale(glm::vec3 _scale);
	glm::vec3 Scale();
private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};