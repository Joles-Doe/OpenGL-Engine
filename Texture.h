#pragma once

//#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <string>
#include <stdexcept>
#include <vector>

/// <summary>
/// Texture - used with a model to give it a texture
/// </summary>
class Texture
{
public:
	Texture(const std::string& _path);
	Texture(glm::ivec2 _size);
	Texture(const Texture& _copy);
	Texture& operator=(const Texture& _assign);
	~Texture();

	/// <summary>
	/// Sets the size of the texture buffer.
	/// </summary>
	/// <param name="_size"> New buffer size </param>
	void SetSize(glm::ivec2 _size) noexcept { mSize = _size; }

	/// <summary>
	/// Returns the size of the texture buffer.
	/// </summary>
	/// <returns> Value of mSize </returns>
	glm::ivec2 GetSize() const noexcept { return mSize; }

	/// <summary>
	/// Loads the texture with the specified path.
	/// </summary>
	/// <param name="_path"> Path of the texture to load </param>
	void Load(const std::string& _path);

	/// <summary>
	/// Returns the ID of the Texture buffer used by the Texture. 
	/// Utilizes dirty loading, so calling this function inexplicitly initializes the buffer if none are present.
	/// </summary>
	/// <returns> The OpenGL Texture buffer ID </returns>
	GLuint ID();

private:
	bool mDirty;
	std::vector<unsigned char> mData;
	glm::ivec2 mSize;
	GLuint mID;

	// These are kept private for now, I'm unsure these are actually needed
	void SetPixel(glm::ivec2 _position, const glm::vec4& _color);
	glm::vec4 GetPixel(glm::ivec2 _position) const;
};