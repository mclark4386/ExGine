#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "tfile.h"

class Texture
{
public:
	Texture(){glGenTextures(1,&ID);loaded = false;mipmaps = false;};
	~Texture(){if(loaded)glDeleteTextures(1, &ID);};	
	int load(const char* filename);
	bool isLoaded(){return loaded;};
	bool applyToModel(GLuint textureUnit);
	void toggleMipmaps();
	void setMipmaps(bool enable);
	void genMipmaps(){/*maybe later*/};
protected:
	bool loaded;
	bool mipmaps;
	GLuint ID;
};

int Texture::load(const char* filename)
{
	//init the tga class
	tfile myTga;
	//load tga
	int tempReturn = myTga.load(filename);
	//if we successfully loaded the file
	if(tempReturn == TFILE_OPEN)
	{
		if(!(glIsEnabled(GL_TEXTURE_2D)))
		{
			glEnable(GL_TEXTURE_2D);
			//std::cout<<"enabling textures"<<std::endl;
		}
		//bind to this texture ID
		glBindTexture(GL_TEXTURE_2D, ID);
		//load our texture into video memory
		glTexImage2D(GL_TEXTURE_2D,0,myTga.getFormat(),myTga.getWidth(),myTga.getHeight(),0,myTga.getFormat(),GL_UNSIGNED_BYTE,myTga.getData());
		//set the texture parameters
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
		if(mipmaps)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);	
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);	
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		loaded = true;
	}
	return tempReturn;
}

bool Texture::applyToModel(GLuint textureUnit = 0)
{
	if(loaded)
	{
		glActiveTexture(GL_TEXTURE0+textureUnit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	return loaded;
}

void Texture::setMipmaps(bool enable)
{
	if(enable == mipmaps)
		return;
	mipmaps = enable;
	glBindTexture(GL_TEXTURE_2D, ID);
	if(mipmaps)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);	
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
}

void Texture::toggleMipmaps()
{
	mipmaps = !mipmaps;
	glBindTexture(GL_TEXTURE_2D, ID);
	if(mipmaps)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);	
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
}

#endif
