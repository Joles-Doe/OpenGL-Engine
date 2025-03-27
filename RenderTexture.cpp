#include "RenderTexture.h"

RenderTexture::RenderTexture(int _w, int _h)
	: mWidth(_w), mHeight(_h), mFboID(0), mTexID(0), mRboID(0)
{
}

RenderTexture::~RenderTexture()
{
	glDeleteFramebuffers(1, &mFboID);
	glDeleteTextures(1, &mTexID);
	glDeleteRenderbuffers(1, &mRboID);
}

void RenderTexture::Bind()
{
	if (!mFboID)
	{
		glGenFramebuffers(1, &mFboID);
		if (!mFboID)
		{
			throw std::runtime_error("Render texture frame buffer error");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, mFboID);

		glGenTextures(1, &mTexID);
		glBindTexture(GL_TEXTURE_2D, mTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexID, 0);

		glGenRenderbuffers(1, &mRboID);
		glBindRenderbuffer(GL_RENDERBUFFER, mRboID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRboID);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, mFboID);
}

void RenderTexture::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
