#ifndef __WIDGETS_H__
#define __WIDGETS_H__

#include <string>
#include <list>
#include "exogl.h"
#include "object.h"

class Widget:public Object
{
public:
	Widget(){};
	virtual ~Widget(){};
	virtual void draw(GLuint textureUnit=0)=0;
	void changeFont(void* _font){glutFont = _font;};
protected:	
	//void renderString(float x, float y, float z, void* glutFont, string string);
	string filename;
	void* glutFont;
};

//void Widget::renderString(float x, float y, float z, void* glutFont, string string)
//{
	////glLineWidth(2);
	//char* c = (char*)string.c_str();
	//glPushMatrix();
	//glTranslatef(x,y,z);
	//for(;(*c!='\0');c++)
		//glutStrokeCharacter(glutFont,*c);
	//glPopMatrix();
//}

#endif
