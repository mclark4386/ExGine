#ifndef __GLSLPROGRAM_H__
#define __GLSLPROGRAM_H__

#include "glslShader.h"

#include <vector>

class glslProgram
{
public:
	glslProgram();
	glslProgram(const std::string &shader, unsigned int shaderType);
	glslProgram(const std::string &vertexShader, const std::string &fragShader);
	~glslProgram(){glDeleteProgram(handle);};
	
	void attach(glslShader &shader);
	void attach(glslShader *shader);
	void detach(glslShader &shader);
	void detach(glslShader *shader);
	
	void link();
	void use() const;
	void disable(GLuint _handle) const;
	
	void sendUniform(const std::string &name, float x);
	void sendUniform(const std::string &name, float x, float y);
	void sendUniform(const std::string &name, float x, float y, float z);
	void sendUniform(const std::string &name, float x, float y, float z, float w);
	void sendUniform(const std::string &name, int x);
	void sendUniform(const std::string &name, int x, int y);
	void sendUniform(const std::string &name, int x, int y, int z);
	void sendUniform(const std::string &name, int x, int y, int z, int w);
	void sendUniform(const std::string &name, float *m, bool transp, int size);
	
	void sendUniform(GLuint location, float x);
	void sendUniform(GLuint location, float x, float y);
	void sendUniform(GLuint location, float x, float y, float z);
	void sendUniform(GLuint location, float x, float y, float z, float w);
	void sendUniform(GLuint location, int x);
	void sendUniform(GLuint location, int x, int y);
	void sendUniform(GLuint location, int x, int y, int z);
	void sendUniform(GLuint location, int x, int y, int z, int w);
	void sendUniform(GLuint location, float *m, bool transp, int size);
	
	GLuint getUniformLocation(const std::string &name) const;
	void setAttributeLocation(const std::string &name, GLuint location);
	GLuint getAttributeLocation(const std::string &name) const;
	
	void GetProgramLog(std::string &log) const;
	void GetFullLog(std::string &log) const;
	GLuint getHandle() const;
	void getParameter(GLuint param, GLint *data) const;
	void validate() const;
	bool isValidProgram() const;
	void getAttributeInfo(GLuint location, std::string &name, GLenum &type, GLint &size) const;
	void getUniformInfo(GLuint location, std::string &name, GLenum &datatype, GLint &size) const;
	void getAttachedShaders(std::vector<GLuint> &shaderHandles);
	void getAttachedShaders(std::vector<glslShader> &shaders);
	
	string getName(){return names;};
	
protected:
	string names;
	GLuint handle;
	std::vector<glslShader> shaderVector;
};

glslProgram::glslProgram()
{
	handle = glCreateProgram();
}

glslProgram::glslProgram(const std::string &shader, unsigned int shaderType=GL_VERTEX_SHADER)
{
	names += ((shaderType==GL_VERTEX_SHADER)?"vs ":"fs ") + shader;
	glslShader temp(shader,shaderType);
	shaderVector.push_back(temp);
	
	handle = glCreateProgram();
	
	glAttachShader(handle, temp.getHandle());
	
	link();
}

glslProgram::glslProgram(const std::string &vertexShader, const std::string &fragShader)
{
	names += "vs "+vertexShader+" fs "+fragShader;
	glslShader tempVS(vertexShader);
	glslShader tempFS(fragShader,GL_FRAGMENT_SHADER);
	shaderVector.push_back(tempVS);
	shaderVector.push_back(tempFS);
	
	handle = glCreateProgram();
	
	glAttachShader(handle, tempVS.getHandle());
	glAttachShader(handle, tempFS.getHandle());
	
	link();
}

void glslProgram::link()
{
	glGetError();
	if(glIsProgram(handle) == GL_FALSE)
	{
		std::clog<<"not valid handle\n";
	}
	glLinkProgram(handle);
	if(glGetError() != GL_NO_ERROR)
	{
		std::clog<<"Shader fuck up: link error\n";
		 return (void)-1;
	 }
}

void glslProgram::attach(glslShader &shader)
{
	shaderVector.push_back(shader);
	glAttachShader(handle, shader.getHandle());
}

void glslProgram::attach(glslShader *shader)
{
	shaderVector.push_back(*shader);
	glAttachShader(handle, shader->getHandle());
}

void glslProgram::detach(glslShader &shader)
{
	std::vector<glslShader>::iterator temp;
	for( temp = shaderVector.begin(); temp != shaderVector.end()&&shader.getHandle() != temp->getHandle(); temp++ ) 
		if(shader.getHandle() == temp->getHandle())break;
	
	shaderVector.erase(temp);
	
	glDetachShader(handle, shader.getHandle());
}

void glslProgram::detach(glslShader *shader)
{
	std::vector<glslShader>::iterator temp;
	for( temp = shaderVector.begin(); temp != shaderVector.end()&&shader->getHandle() != temp->getHandle(); temp++ ) 
		if(shader->getHandle() == temp->getHandle())break;
	
	shaderVector.erase(temp);
	
	glDetachShader(handle, shader->getHandle());
}

void glslProgram::use() const
{
	glGetError();
	if(glIsProgram(handle) == GL_FALSE)
	{
		std::clog<<"not valid handle\n";
	}
	GLint test;
	getParameter(GL_LINK_STATUS, &test);
	if(test == GL_FALSE)
	{
		//std::clog<<"not linked\n";
	}
	glUseProgram(handle);
	GLuint error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::clog<<"Shader fuck up: USE error:"<<error<<"\n";
		 return (void)-1;
	 }
}

void glslProgram::disable(GLuint _handle=0) const
{
	glUseProgram(_handle);
}

void glslProgram::sendUniform(const std::string &name, float x)
{
	glUniform1f(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x);
}

void glslProgram::sendUniform(const std::string &name, int x)
{
	glUniform1i(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x);
}

void glslProgram::sendUniform(const std::string &name, float x, float y)
{
	glUniform2f(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x, y);
}

void glslProgram::sendUniform(const std::string &name, int x, int y)
{
	glUniform2i(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x, y);
}

void glslProgram::sendUniform(const std::string &name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x, y, z);
}

void glslProgram::sendUniform(const std::string &name, int x, int y, int z)
{
	glUniform3i(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x, y, z);
}

void glslProgram::sendUniform(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x, y, z, w);
}

void glslProgram::sendUniform(const std::string &name, int x, int y, int z, int w)
{
	glUniform4i(glGetUniformLocation(handle,(const GLchar*)name.c_str()), x, y, z, w);
}

void glslProgram::sendUniform(const std::string &name, float *m, bool transp=false, int size=1)
{
	//modified for animation... probably should find a smarter way to do this... maybe a flag or something
	//switch(size)
	//{
		//case 2:
			//glUniformMatrix2fv(glGetUniformLocation(handle,(const GLchar*)name.c_str()), 1, transp, m);
			//break;
		//case 3:
			//glUniformMatrix3fv(glGetUniformLocation(handle,(const GLchar*)name.c_str()), 1, transp, m);
			//break;
		//case 4:
			glUniformMatrix4fv(glGetUniformLocation(handle,(const GLchar*)name.c_str()), size, transp, m);
			//break;
	//}
}

void glslProgram::sendUniform(GLuint location, float x)
{
	glUniform1f(location, x);
}

void glslProgram::sendUniform(GLuint location, int x)
{
	glUniform1i(location, x);
}

void glslProgram::sendUniform(GLuint location, float x, float y)
{
	glUniform2f(location, x, y);
}

void glslProgram::sendUniform(GLuint location, int x, int y)
{
	glUniform2i(location, x, y);
}

void glslProgram::sendUniform(GLuint location, float x, float y, float z)
{
	glUniform3f(location, x, y, z);
}

void glslProgram::sendUniform(GLuint location, int x, int y, int z)
{
	glUniform3i(location, x, y, z);
}

void glslProgram::sendUniform(GLuint location, float x, float y, float z, float w)
{
	glUniform4f(location, x, y, z, w);
}

void glslProgram::sendUniform(GLuint location, int x, int y, int z, int w)
{
	glUniform4i(location, x, y, z, w);
}

void glslProgram::sendUniform(GLuint location, float *m, bool transp=false, int size=4)
{
	switch(size)
	{
		case 2:
			glUniformMatrix2fv(location, 1, transp, m);
			break;
		case 3:
			glUniformMatrix3fv(location, 1, transp, m);
			break;
		case 4:
			glUniformMatrix4fv(location, 1, transp, m);
			break;
	}
}

GLuint glslProgram::getUniformLocation(const std::string &name) const
{
	return glGetUniformLocation(handle,(const GLchar*)name.c_str());
}

void glslProgram::setAttributeLocation(const std::string &name, GLuint location)
{
	glBindAttribLocation(handle,location, (const GLchar*)name.c_str());
}

GLuint glslProgram::getAttributeLocation(const std::string &name) const
{
	return glGetAttribLocation(handle,(const GLchar*)name.c_str());
}

void glslProgram::GetProgramLog(std::string &log) const
{
	GLint length;
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
	glGetProgramInfoLog(handle, length+1, NULL, (GLchar*)log.c_str());
}

void glslProgram::GetFullLog(std::string &log) const
{
	string temp1, temp2, temp3;
	shaderVector[0].getShaderLog(temp1);
	shaderVector[1].getShaderLog(temp2);
	GLint length;
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
	glGetProgramInfoLog(handle, length+1, NULL, (GLchar*)temp3.c_str());
	
	log = "\nShader1: \n" + temp1 + "\nShader2: \n" + temp2 + "\nProgram: \n" + temp3 + "\n";
}

GLuint glslProgram::getHandle() const
{
	return handle;
}

void glslProgram::getParameter(GLuint param, GLint *data) const
{
	//GL_DELETE_STATUS					GLboolean
	//GL_LINK_STATUS					GLboolean
	//GL_VALIDATE_STATUS				GLboolean
	//GL_INFO_LOG_LENGTH				GLuint
	//GL_ATTACHED_SHADERS				
	//GL_ACTIVE_ATTRIBUTES				
	//GL_ACTIVE_ATTRIBUTE_MAX_LENGTH	
	//GL_ACTIVE_UNIFORMS				
	//GL_ACTIVE_UNIFORM_MAX_LENGTH		
	glGetProgramiv(handle, param, data);
}

void glslProgram::validate() const
{
	glValidateProgram(handle);
}

bool glslProgram::isValidProgram() const
{
	GLint valid;
	glGetProgramiv(handle, GL_VALIDATE_STATUS, &valid);
	if(valid == GL_TRUE)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void glslProgram::getAttributeInfo(GLuint location, std::string &name, GLenum &type, GLint &size) const
{
	
}

void glslProgram::getUniformInfo(GLuint location, std::string &name, GLenum &datatype, GLint &size) const
{
	
}

void glslProgram::getAttachedShaders(std::vector<GLuint> &shaderHandles)
{
	
}

void glslProgram::getAttachedShaders(std::vector<glslShader> &shaders)
{
	shaders = shaderVector;
}

#endif
