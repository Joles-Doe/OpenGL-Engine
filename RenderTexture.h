#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdexcept>

class RenderTexture
{
public:
	RenderTexture(int _w, int _h);
	~RenderTexture();

	void Bind();
	void Unbind();

	RenderTexture(const RenderTexture& _copy);
	RenderTexture& operator=(const RenderTexture& _other);
private:
	int mWidth;
	int mHeight;

	GLuint mFboID;
	GLuint mTexID;
	GLuint mRboID;
};

