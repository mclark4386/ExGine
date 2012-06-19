#ifndef __FBO_H__
#define __FBO_H__

#include "exogl.h"

#define MAX_MRTS 3

class FBO
{
public:
	FBO(int _width = 640, int _height = 480);
	~FBO();
	void setWidth(int _w){width = _w;reshape();};
	void setHeight(int _h){height = _h;reshape();};
	void setRes(int _width, int _height){width = _width;height = _height;reshape();};
	bool attach();
	bool detach();
	bool bindTextures();
protected:
	void reshape();
	int width, height;
	GLuint color, depth, IDs[MAX_MRTS];
	GLenum mrts[MAX_MRTS];
	bool loaded;
};

FBO::FBO(int _width, int _height)
{
	width = _width; height = _height;
	for(int i = 0; i<MAX_MRTS;i++)
		mrts[i] = GL_COLOR_ATTACHMENT0_EXT+i;
	
	glGenFramebuffersEXT(1, &color);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, color);
	
	glGenRenderbuffersEXT(1, &depth);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth);
	
	glGenTextures(MAX_MRTS, IDs);
	
	for(int i = 0; i<MAX_MRTS;i++)
	{
		glBindTexture(GL_TEXTURE_2D, IDs[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i,GL_TEXTURE_2D, IDs[i], 0);
	}
	
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		loaded = false;
		return;
	}
	loaded = true;
}

FBO::~FBO()
{
	if(loaded)
	{
		glDeleteTextures(MAX_MRTS, IDs);
		glDeleteRenderbuffersEXT(1, &depth);
		glDeleteFramebuffersEXT(1, &color);
	}
}

bool FBO::attach()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, color);
	glDrawBuffers(MAX_MRTS, mrts);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	return true;
}

bool FBO::detach()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	
	return true;
}

bool FBO::bindTextures()
{
	for(int i=0;i<MAX_MRTS;i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, IDs[i]);
	}
	
	return true;
}

void FBO::reshape()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, color);
	
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth);
	
	for(int i = 0; i<MAX_MRTS;i++)
	{
		glBindTexture(GL_TEXTURE_2D, IDs[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i,GL_TEXTURE_2D, IDs[i], 0);
	}
	
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		loaded = false;
		return;
	}
	loaded = true;
}
#endif
