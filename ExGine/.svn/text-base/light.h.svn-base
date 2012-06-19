#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "object.h"

class Light:public Object
{
public:
	Light();
	~Light();
	void toggle(){glIsEnabled(lightID)?glDisable(lightID):glEnable(lightID);};
	void move(GLfloat pos[4]){light_position[0]=pos[0];light_position[1]=pos[1];light_position[2]=pos[2];light_position[3]=pos[3];};
	void move(GLfloat x, GLfloat y, GLfloat z, GLfloat w){light_position[0]=x;light_position[1]=y;light_position[2]=z;light_position[3]=w;};
	void draw(GLuint textureUnit); //function to callback
protected:
	GLfloat light_position[4];
	GLenum lightID;
};

Light::Light()
{
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	light_position[0] = 1.0;
	light_position[1] = 1.0;
	light_position[2] = 1.0;
	light_position[3] = 1.0;
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
	
	if(!glIsEnabled(GL_LIGHT0))
		lightID = GL_LIGHT0;
	else if(!glIsEnabled(GL_LIGHT1))
		lightID = GL_LIGHT1;
	else if(!glIsEnabled(GL_LIGHT2))
		lightID = GL_LIGHT2;
	else if(!glIsEnabled(GL_LIGHT3))
		lightID = GL_LIGHT3;
	else if(!glIsEnabled(GL_LIGHT4))
		lightID = GL_LIGHT4;
	else if(!glIsEnabled(GL_LIGHT5))
		lightID = GL_LIGHT5;
	else if(!glIsEnabled(GL_LIGHT6))
		lightID = GL_LIGHT6;
	else if(!glIsEnabled(GL_LIGHT7))
		lightID = GL_LIGHT7;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(lightID, GL_DIFFUSE, white_light);
	glLightfv(lightID, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//slows things down so may want to take this out later, if possible
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glEnable(GL_LIGHTING);
	
	glEnable(lightID);
	
	glEnable(GL_DEPTH_TEST);
}

Light::~Light(){}

void Light::draw(GLuint textureUnit = 0)
{
	glLightfv(lightID, GL_POSITION, light_position);
}

#endif
