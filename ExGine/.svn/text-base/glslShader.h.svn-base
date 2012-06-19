#ifndef __GLSLSHADER_H__
#define __GLSLSHADER_H__

#include "exogl.h"
#include <string>
#include <fstream>

#include <iostream>

class glslShader
{
public:
	glslShader(const std::string &filename, GLenum shaderType);
	glslShader(GLenum shaderType = GL_VERTEX_SHADER){handle = glCreateShader(shaderType);};
	~glslShader(){glDeleteShader(handle);};
	void compile();
	bool isCompiled() const;
	void getShaderLog(std::string &log) const;
	void getShaderSource(std::string &shader) const;
	void setShaderSource(std::string &code);
	GLuint getHandle() const;
	void getParameter(GLenum param, GLint *data) const;
protected:
	GLuint handle;
	
};

glslShader::glslShader(const std::string &filename, GLenum shaderType = GL_VERTEX_SHADER)
{
	glGetError();//clear error messages
	handle = glCreateShader(shaderType);
	
	fstream file;
	file.open(filename.c_str(), ios::in);//open file for input
	
	if(!file.is_open())//if that doesn't work
	{
		std::clog<<"couldn't open shader\n";
		return;//return our shame
	}
	
	GLuint count =0;
	
	file.seekg(0, ios::end);
	count = file.tellg();
	file.seekg(0, ios::beg);

	GLchar* shaderCode = (GLchar*) new GLchar[count+1];
	file.read((char*)shaderCode, count);
	
	file.close();
	
	/*std::clog<<"SHADER"<<handle<<":\n"<<
	"---------------------------------------------\n"<<
	shaderCode<<"\n";//*/
	
	std::string temp;
	glShaderSource(handle, 1, (const GLchar**)&shaderCode, NULL);
	int error = glGetError();
	if(error != GL_NO_ERROR) 
	{
		if(shaderType == GL_VERTEX_SHADER)
			temp = "vertex";
		if(shaderType == GL_FRAGMENT_SHADER)
			temp = "fragment";
		std::clog<<"Shader fuck up:"<<handle<<" type "<<temp<<" with error code "<<error<<"\n";
	}
	
	compile();
	if(!isCompiled())
	{
		std::clog<<"shader not compiled:"<<filename<<"\n";
		string log;
		getShaderLog(log);
		std::clog<<"Shader Log:\n"<<log<<"\n";
	}
}

void glslShader::compile()
{
	glGetError();//clear
	if(!isCompiled())
	{
		glCompileShader(handle);
		GLuint error = glGetError();
		if(error != GL_NO_ERROR) 
		{
			std::clog<<"Shader fuck up:compile: "<<error<<"\n";
		}
	}
}

bool glslShader::isCompiled() const
{
	GLint compiled = 0;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	if(compiled == GL_TRUE)
		return true;
	return false;
}

GLuint glslShader::getHandle() const
{
	return handle;
}

void glslShader::getParameter(GLenum param, GLint *data) const
{
	glGetShaderiv(handle, param, data);
}

void glslShader::getShaderLog(std::string &log) const
{
	GLint length;
	
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	glGetShaderInfoLog(handle, length+1, NULL, (GLchar*)log.c_str());
}

void glslShader::getShaderSource(std::string &shader) const
{
	GLint length;
	
	glGetShaderiv(handle, GL_SHADER_SOURCE_LENGTH, &length);
	glGetShaderSource(handle, (GLsizei)length+1, NULL, (GLchar*)shader.c_str());
}

void glslShader::setShaderSource(std::string &code)
{
	glShaderSource(handle, 1, (const GLchar**)&code, NULL);
}

#endif
