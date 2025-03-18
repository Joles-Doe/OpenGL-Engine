#pragma once

//#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <iostream>
#include <string>
#include <vector>

class Texture
{
public:
	Texture(const std::string& _path);
	Texture(glm::ivec2 _size);
	Texture(const Texture& _copy);
	Texture& operator=(const Texture& _assign);
	~Texture();

	void SetSize(glm::ivec2 _size);
	glm::ivec2 GetSize() const;

	void Load(const std::string& _path);

	void SetPixel(glm::ivec2 _position, const glm::vec4& _color);
	glm::vec4 GetPixel(glm::ivec2 _position) const;

	GLuint ID();

private:
	bool mDirty;
	std::vector<float> mData;
	glm::ivec2 mSize;
	GLuint mID;
};

