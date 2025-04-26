#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

/// <summary>
/// Transform component - Container for position, rotation, and scale.
/// </summary>
class Transform
{
public:
	Transform();

	/// <summary>
	/// Move the Object by the passed vector.
	/// </summary>
	/// <param name="_movement"> Movement vector </param>
	void Move(glm::vec3 _movement) noexcept { mPosition += _movement; }

	/// <summary>
	/// Rotate the Object by the passed rotation. (Degrees)
	/// </summary>
	/// <param name="_rot"> Degrees rotation vector</param>
	void Rotate(glm::vec3 _rot) noexcept { mRotation += _rot; }

	/// <summary>
	/// Sets the Object's position.
	/// </summary>
	/// <param name="_pos"> New vector position</param>
	void Position(glm::vec3 _pos) noexcept { mPosition = _pos; }

	/// <summary>
	/// Gets the Object's position.
	/// </summary>
	/// <returns> Vector Object position </returns>
	glm::vec3 Position() const noexcept { return mPosition; }

	/// <summary>
	/// Sets the Object's rotation. (Degrees)
	/// </summary>
	/// <param name="_rot"> New vector degrees rotation</param>
	void Rotation(glm::vec3 _rot) noexcept { mRotation = _rot; }

	/// <summary>
	/// Gets the Object's rotation. (Degrees)
	/// </summary>
	/// <returns> Vector Object degrees rotation </returns>
	glm::vec3 Rotation() { return mRotation; }

	/// <summary>
	/// Sets the Object's scale.
	/// </summary>
	/// <param name="_scale"> New vector scale </param>
	void Scale(glm::vec3 _scale) noexcept { mScale = _scale; }
	
	/// <summary>
	/// Gets the Object's scale.
	/// </summary>
	/// <returns> Vector Object scale </returns>
	glm::vec3 Scale() const noexcept { return mScale; }
private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};