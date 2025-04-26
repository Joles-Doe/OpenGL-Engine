#include "Texture.h"

Texture::Texture(const std::string& _path) : mDirty(true), mID(0)
{
	Load(_path);
}

Texture::Texture(glm::ivec2 _size) : mDirty(true), mSize(_size), mID(0)
{
	mData.resize(_size.x * _size.y * 4);
}

Texture::~Texture()
{
	if (mID)
	{
		glDeleteTextures(1, &mID);
	}
}

void Texture::Load(const std::string& _path)
{
	unsigned char* textureData = stbi_load(_path.c_str(), &mSize.x, &mSize.y, NULL, 4);

	if (!textureData)
	{
		throw std::runtime_error("Failed to Load Texture");
	}

	for (int x = 0; x < (mSize.x * mSize.y * 4); x++)
	{
		mData.push_back(textureData[x]);
	}
	free(textureData);
}

void Texture::SetPixel(glm::ivec2 _position, const glm::vec4& _color)
{
	int index = _position.x * _position.y * 4;
	for (int x = 0; x < 4; x++)
	{
		mData[index + x] = _color[x];
	}
}

GLuint Texture::ID()
{
	if (mID == 0)
	{
		glGenTextures(1, &mID);

		if (!mID)
		{
			throw std::runtime_error("Failed to Initialize Texture");
		}
	}

	if (mDirty == true)
	{
		glBindTexture(GL_TEXTURE_2D, mID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData.data());

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		mDirty = false;
	}

	return mID;
}

glm::vec4 Texture::GetPixel(glm::ivec2 _position) const
{
	glm::vec4 pixel;
	int index = _position.x * _position.y * 4;
	for (int x = 0; x < 4; x++)
	{
		pixel[x] = mData[index + x];
	}

	return glm::vec4();
}
