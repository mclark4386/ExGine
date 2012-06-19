#ifndef __GUI_H__
#define __GUI_H__

#include <string>
#include "label.h"


class Gui:public Widget
{
public:
	Gui(int _screenw=640, int _screenh=480);
	~Gui();
	void addWidget(Widget* _widget);
	int reshape(int _w, int _h);
	void draw(GLuint textureUnit = 0);
	void drawSelect(void){};
protected:
	void enterOverlayMode();
	void leaveOverlayMode();
	
	int screenw;
	int screenh;
		
	struct WidgeNode
	{
		Widget* widget;
		WidgeNode* next;
	};
	
	int widgetCount;
	
	WidgeNode* root;
	WidgeNode* current;
		
};

Gui::Gui(int _screenw, int _screenh)
{
	screenw=_screenw;
	screenh=_screenh;	
	widgetCount=0;
	root=current=0;
	
	//testing
	widgetCount++;
	root = new WidgeNode;
	current = root; 
	root->widget = new Label(0.0,0.0,-1.0,"Label\0");//*/
}

Gui::~Gui()
{
	if(root==0)return;
	current=root;
	for(int i=0;i<widgetCount;i++)
	{
		delete current->widget;
		WidgeNode*temp; 
		temp = current;
		current=current->next;
	}
}

int Gui::reshape(int _w, int _h)
{
	screenw=_w;
	screenh=_h;
	return 0;
}

void Gui::draw(GLuint textureUnit)
{	
	enterOverlayMode();
	
	current=root;
	for(int i=0; i<widgetCount; i++)
	{
		current->widget->draw();
		current=current->next;
	}
	
	leaveOverlayMode();
}

void Gui::enterOverlayMode()
{	
	glPushMatrix();
  	glTranslatef(0.0, 0.0, -5.0);
  
	glPushMatrix();
	
	float matrix[16];
	
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	
	matrix[0]=matrix[5]=matrix[10]=matrix[15]=1.0f;
	matrix[1]=matrix[2]=matrix[3]=matrix[4]=0.0f;
	matrix[6]=matrix[7]=matrix[8]=matrix[9]=matrix[11]=0.0f;
	
	glLoadMatrixf(matrix);
	/*
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,screenw,0,screenh);
	glScalef(1,-1,1);
	glTranslatef(0,0,0);
	glMatrixMode(GL_MODELVIEW);
	return;*/
}

void Gui::leaveOverlayMode()
{
	glPopMatrix();
	glPopMatrix();
	/*
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	*/
}

void Gui::addWidget(Widget* _widget)
{
	if(root==0)
	{
		root = current = new WidgeNode;
		widgetCount++;
		current->widget = _widget;
		current->next = 0;
	}
	else
	{
		current =root;
		for(int i=0; i<widgetCount;i++)
			current=current->next;
		current->next = new WidgeNode;
		current->next->widget = _widget;
		current->next->next = 0;
		widgetCount++;
	}
}

#endif
