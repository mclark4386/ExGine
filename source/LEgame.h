#ifndef __GAME_H__
#define __GAME_H__

#define MENU_DUPLICATE 1
#define MENU_INSTANCE 2
#define MENU_LOADMODEL 3
#define MENU_LOADLEVEL 4
#define MENU_SAVELEVEL 5
#define MENU_EXIT 6
#define MENU_MODEL_MOVE_X 7
#define MENU_MODEL_MOVE_Y 8
#define MENU_MODEL_MOVE_Z 9
#define MENU_MODEL_ROTATE_X 10
#define MENU_MODEL_ROTATE_Y 11
#define MENU_MODEL_ROTATE_Z 12
#define MENU_MODEL_SCALE 13
#define MENU_MODEL_SCALE_X 14
#define MENU_MODEL_SCALE_Y 15
#define MENU_MODEL_SCALE_Z 16
#define MENU_LIGHT_MOVE_X 17
#define MENU_LIGHT_MOVE_Y 18
#define MENU_LIGHT_MOVE_Z 19
#define MENU_LIGHT_ROTATE_X 20
#define MENU_LIGHT_ROTATE_Y 21
#define MENU_LIGHT_ROTATE_Z 22

#include "LEscene.h"

void touchme_display(void);
void touchme_reshape(int w, int h);
void touchme_keyboard(unsigned char key, int x, int y);
void touchme_specialKeyboard(int key, int x, int y);
void touchme_mouse(int button, int state, int x, int y);
void touchme_mouseMotion(int x, int y);
void touchme_PassiveMouseMotion(int x, int y);

class Game
{
public:
	static Game* getInstance();
	Game* operator=(const Game&){return singleton;};
	void delInstance();
	Game();
	~Game();
	void init(int argc, char** argv);
	void run();
	void reshape(int w, int h);
	void display(void);
	void keyboard(unsigned char key, int x, int y);
	void skeyboard(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void PassiveMouseMotion(int x, int y);
	
	void doMenu(int pick);
protected:
	void createMenu();
	void destroyMenu();
	void detachMenu();
	int menuID;
	
	ofstream log;

	GLsizei ww, hh;
	
	static Game* singleton;
	
	Scene* currentScene;
};

Game* Game::singleton = 0;
Game* Game::getInstance()
{
	if(singleton == 0)
		singleton = new Game();
	
	return singleton;
}

void Game::delInstance()
{
	Game* tmp = singleton;
	singleton = 0;
	delete tmp;
}

Game::Game()
{	
	currentScene = new Scene();
}

Game::~Game()
{
	delete currentScene;
}

void Game::reshape(int w, int h)
{
  ww=(GLsizei)w; hh=(GLsizei)h;
  glViewport(0,0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLsizei) w/ (GLsizei) h, 0.1, 120.0);
  glMatrixMode(GL_MODELVIEW);
  
  currentScene->Reshape(w,h);
}

void Game::init(int argc, char** argv)
{
	ww=640;
	hh=480;
	
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
  //glutGameModeString("1280x1024:32@54");
  //glutEnterGameMode();
  glutInitWindowSize(ww,hh);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);
  
  //glewInit();
//  
//  if(!glewIsSupported("GL_VERSION_2_0"))
//  {                                    
//      std::cout<<"Your graphics card or drivers do not support OpenGL 2.0 try updating your drivers"<<std::endl;
//      exit(1);
//  }
	
  reshape(ww,hh);
  
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_SMOOTH);

  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0};
  GLfloat flat = 5.0;
  GLfloat zero[] = {0.0, 0.0, 0.0, 1.0};
  
  	Light* light = new Light;
  Material* mat = new Material(white,white,flat,white,zero);
  
  Model* model;
if(argc>1)
{  
	for(int i=1;i<argc;i++)
	{
		model = new StaticModel(argv[i]);
  		currentScene->addModel(model, mat);//*/
  	}
}
else
{  
  model = new StaticModel("data/test-plane.em");
  currentScene->addModel(model, mat);
 }//*/
 
 	currentScene->addLight(light);
 	
 //init GUI
// Widget* label = new Label("test");
 
 //testGUI->addWidget(label);
 
  glutDisplayFunc(touchme_display);
  glutIdleFunc(touchme_display);
  glutReshapeFunc(touchme_reshape);
  glutKeyboardFunc(touchme_keyboard);
  glutSpecialFunc(touchme_specialKeyboard);
  glutMouseFunc(touchme_mouse);
  glutMotionFunc(touchme_mouseMotion);
  glutPassiveMotionFunc(touchme_PassiveMouseMotion);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  log.open("log.txt");
  
  if(log.is_open())
  	std::clog.rdbuf(log.rdbuf());
  
 #ifndef WIN32_NO_SO_LEAN
  createMenu();
 #endif
}

void Game::display(void)
{		
	currentScene->draw();
}

void Game::keyboard(unsigned char key, int x, int y)
{
	currentScene->KB(key,x,y);
}

void Game::skeyboard(int key, int x, int y)
{
	currentScene->SKB(key,x,y);
}

void Game::mouse(int button, int state, int x, int y)
{
	currentScene->Mouse(button,state,x,y);
}

void Game::MouseMotion(int x, int y)
{
	currentScene->MouseMotion(x,y);
}

void Game::PassiveMouseMotion(int x, int y)
{
	currentScene->PassMouseMotion(x,y);
}

void Game::run()
{
  glutMainLoop();
}

void touchme_display(void)
{
	Game* myGame = Game::getInstance();
	myGame->display();
}
void touchme_reshape(int w, int h)
{
	Game* myGame = Game::getInstance();
	myGame->reshape(w,h);	
}
void touchme_keyboard(unsigned char key, int x, int y)
{
	Game* myGame = Game::getInstance();
	myGame->keyboard(key,x,y);	
}
void touchme_specialKeyboard(int key, int x, int y)
{
	Game* myGame = Game::getInstance();
	myGame->skeyboard(key,x,y);	
}	
void touchme_mouse(int button, int state, int x, int y)
{
	Game* myGame = Game::getInstance();
	myGame->mouse(button,state,x,y);	
}

void touchme_mouseMotion(int x, int y)
{
	Game* myGame = Game::getInstance();
	myGame->MouseMotion(x,y);
}

void touchme_PassiveMouseMotion(int x, int y)
{
	Game* myGame = Game::getInstance();
	myGame->PassiveMouseMotion(x,y);
}

void touchme_menu(int value)
{
	Game* myGame = Game::getInstance();
	myGame->doMenu(value);
}

void Game::createMenu()
{	
	int modelMoveMenuID = glutCreateMenu(touchme_menu);
	glutAddMenuEntry("X", MENU_MODEL_MOVE_X);
	glutAddMenuEntry("Y", MENU_MODEL_MOVE_Y);
	glutAddMenuEntry("Z", MENU_MODEL_MOVE_Z);
	
	int modelRotateMenuID = glutCreateMenu(touchme_menu);
	glutAddMenuEntry("X", MENU_MODEL_ROTATE_X);
	glutAddMenuEntry("Y", MENU_MODEL_ROTATE_Y);
	glutAddMenuEntry("Z", MENU_MODEL_ROTATE_Z);
	
	int modelScaleMenuID = glutCreateMenu(touchme_menu);
	glutAddMenuEntry("Uniform", MENU_MODEL_SCALE);
	glutAddMenuEntry("X", MENU_MODEL_SCALE_X);
	glutAddMenuEntry("Y", MENU_MODEL_SCALE_Y);
	glutAddMenuEntry("Z", MENU_MODEL_SCALE_Z);
	
	int modelMenuID = glutCreateMenu(touchme_menu);
	glutAddSubMenu("Move", modelMoveMenuID);
	glutAddSubMenu("Rotate", modelRotateMenuID);
	glutAddSubMenu("Scale", modelScaleMenuID);
	glutAddMenuEntry("Duplicate", MENU_DUPLICATE);
	glutAddMenuEntry("Instance", MENU_INSTANCE);
	
	int lightMoveMenuID = glutCreateMenu(touchme_menu);
	glutAddMenuEntry("X", MENU_LIGHT_MOVE_X);
	glutAddMenuEntry("Y", MENU_LIGHT_MOVE_Y);
	glutAddMenuEntry("Z", MENU_LIGHT_MOVE_Z);
	
	int lightRotateMenuID = glutCreateMenu(touchme_menu);
	glutAddMenuEntry("X", MENU_LIGHT_ROTATE_X);
	glutAddMenuEntry("Y", MENU_LIGHT_ROTATE_Y);
	glutAddMenuEntry("Z", MENU_LIGHT_ROTATE_Z);
	
	int lightMenuID = glutCreateMenu(touchme_menu);
	glutAddSubMenu("Move", lightMoveMenuID);
	glutAddSubMenu("Rotate", lightRotateMenuID);
	
	
	menuID = glutCreateMenu(touchme_menu);
	
	glutAddSubMenu("Model Menu", modelMenuID);
	glutAddSubMenu("Light Menu", lightMenuID);
	glutAddMenuEntry("Load Model", MENU_LOADMODEL);
	glutAddMenuEntry("Save Level", MENU_SAVELEVEL);
	glutAddMenuEntry("Load Level", MENU_LOADLEVEL);
	glutAddMenuEntry("Exit", MENU_EXIT);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Game::detachMenu()
{
	glutDetachMenu(GLUT_RIGHT_BUTTON);
}

void Game::destroyMenu()
{
	glutDestroyMenu(menuID);
}

void Game::doMenu(int pick)
{	
	switch(pick)
	{
		case MENU_INSTANCE:
			currentScene->instanceModel(currentScene->getCurrentSelection());
			break;
		case MENU_DUPLICATE:
			currentScene->duplicateModel(currentScene->getCurrentSelection());
			break;
		case MENU_LOADMODEL:
			currentScene->KB(0,LOADMODEL_MODE,0);
			break;
		case MENU_SAVELEVEL:
			currentScene->KB(0,SAVELEVEL_MODE,0);
			break;
		case MENU_LOADLEVEL:
			currentScene->KB(0,LOADLEVEL_MODE,0);
			break;
		case MENU_EXIT:
			exit(0);
			break;
		case MENU_MODEL_MOVE_X: 
			currentScene->KB(0,KEY_MODEL_MOVE_X,0);
			break;
		case MENU_MODEL_MOVE_Y:
			currentScene->KB(0,KEY_MODEL_MOVE_Y,0);
			break;
		case MENU_MODEL_MOVE_Z: 
			currentScene->KB(0,KEY_MODEL_MOVE_Z,0);
			break;
		case MENU_MODEL_ROTATE_X: 
			currentScene->KB(0,KEY_MODEL_ROTATE_X,0);
			break;
		case MENU_MODEL_ROTATE_Y: 
			currentScene->KB(0,KEY_MODEL_ROTATE_Y,0);
			break;
		case MENU_MODEL_ROTATE_Z: 
			currentScene->KB(0,KEY_MODEL_ROTATE_Z,0);
			break;
		case MENU_MODEL_SCALE: 
			currentScene->KB(0,KEY_MODEL_SCALE,0);
			break;
		case MENU_MODEL_SCALE_X: 
			currentScene->KB(0,KEY_MODEL_SCALE_X,0);
			break;
		case MENU_MODEL_SCALE_Y: 
			currentScene->KB(0,KEY_MODEL_SCALE_Y,0);
			break;
		case MENU_MODEL_SCALE_Z: 
			currentScene->KB(0,KEY_MODEL_SCALE_Z,0);
			break;
		case MENU_LIGHT_MOVE_X: 
			currentScene->KB(0,KEY_LIGHT_MOVE_X,0);
			break;
		case MENU_LIGHT_MOVE_Y: 
			currentScene->KB(0,KEY_LIGHT_MOVE_Y,0);
			break;
		case MENU_LIGHT_MOVE_Z: 
			currentScene->KB(0,KEY_LIGHT_MOVE_Z,0);
			break;
		case MENU_LIGHT_ROTATE_X: 
			currentScene->KB(0,KEY_LIGHT_ROTATE_X,0);
			break;
		case MENU_LIGHT_ROTATE_Y: 
			currentScene->KB(0,KEY_LIGHT_ROTATE_Y,0);
			break;
		case MENU_LIGHT_ROTATE_Z:
			currentScene->KB(0,KEY_LIGHT_ROTATE_Z,0); 
			break;
	}
}

#endif
