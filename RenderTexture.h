#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdexcept>

/// <summary>
/// RenderTexture - Stores the data from the current shader and displays it onto the texture
/// </summary>
class RenderTexture
{
public:
	RenderTexture(int _w, int _h);
	~RenderTexture();

	/// <summary>
	/// Make the RenderTexture the target for shader data
	/// </summary>
	void Bind();

	/// <summary>
	/// Unbind the RenderTexture
	/// </summary>
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

