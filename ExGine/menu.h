#ifndef __MENU_H__
#define __MENU_H__

class Menu
{
public:
	Menu();
	~Menu();
	void draw();
protected:
};


/*
void processMenuEvents(int option) {

	switch (option) {
		case RED : red = 1.0; green = 0.0; blue = 0.0; break;
		case GREEN : red = 0.0; green = 1.0; blue = 0.0; break;
		case BLUE : red = 0.0; green = 0.0; blue = 1.0; break;
		case WHITE : red = 1.0; green = 1.0; blue = 1.0; break;
	}
}

void createGLUTMenus() {

	int menu,submenu;

	submenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Green",GREEN);

	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("White",WHITE);
	glutAddSubMenu("RGB Menu",submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

glutDetachMenu(GLUT_RIGHT_BUTTON);//*/

#endif
