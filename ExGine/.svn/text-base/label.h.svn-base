#ifndef __LABEL_H__
#define __LABEL_H__

#include "widgets.h"
#include "glslProgram.h"
#include "glslShader.h"
#include "prim.h"
#include "texture.h"

class Label:public Widget
{
public:
	Label(float _x=0.0, float _y=0.0, float _z=0.0, string _s="default\0"){x=_x;y=_y;z=_z;str=_s;textShader = new glslProgram("data/shaders/text.vs","data/shaders/text.fs"); panel = new Plane(); font = new Texture(); font->load("data/font.tga");};
	~Label(){delete panel; delete font;};
	void draw(GLuint textureUnit = 0);
	void changeString(string s){str = s;};
	void move(float _x, float _y, float _z){x=_x;y=_y;z=_z;};
protected:
	void renderString(float x, float y, float z, string string);
	void textureChar(char character);
	string str;
	float x, y, z;
	glslProgram* textShader;
	Plane* panel;
	Texture* font;
};

void Label::draw(GLuint textureUnit)
{
	renderString(x,y,z,str);
}


void Label::renderString(float x, float y, float z, string string)
{
	//glLineWidth(2);
	char* c = (char*)string.c_str();
	glPushMatrix();
	glTranslatef(x,y,z);
	for(;(*c!='\0');c++)
		textureChar(*c);
	glPopMatrix();
}

void Label::textureChar(char character)
{
	textShader->use();
	font->applyToModel();
	textShader->sendUniform("tex",0);	
	textShader->sendUniform("char", (int)character);
	panel->draw();
	textShader->disable();
}

#endif
