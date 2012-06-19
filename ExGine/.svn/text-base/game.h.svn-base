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

#include "plistener.h"
#include "scene.h"

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
	bool loadScene(const char* filename);
	void saveScene(string filename);
	
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
	PListener* physics;
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
	delete physics;
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
  log.open("log.txt");
  
  if(log.is_open())
  	std::clog.rdbuf(log.rdbuf());
  	
  	
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
  mFile* file;
  
  Model* model;
if(argc>1)
{  
	#pragma omp parallel for
	for(int i=1;i<argc;i++)
	{
		file = new mFile(argv[i]);
		if (file->isStatic())
			model = new Model(file);
		else
			model = new AModel(file);
  		currentScene->addModel(model, mat);//*/
  	}
}
else
{  
  model = new Model("data/ship.em");
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
  
  
 #ifndef WIN32_NO_SO_LEAN
  createMenu();
 #endif
 
  physics = new PListener(); 
  physics->setScene(currentScene);
  PObject* initp = new POSphere();
  PObject* ground = new POPlane();
  //PObject* Z1Wall = new POPlane();
  vector<Scalar> temp;
  Vector<Scalar> tempVec;
  temp.push_back(0.4);//garbage
  temp.push_back(1.0);//radius of bounding sphere
  Vector<Scalar> tempPos = currentScene->getModelPos(1);
  std::clog<<"setting model to "<<currentScene->getModelPos(1).x<<", "<<currentScene->getModelPos(1).y<<", "<<currentScene->getModelPos(1).z<<std::endl;
  initp->setPoM(tempPos);
  initp->setStats(temp);
  
  temp.clear();
  temp.push_back(0.3);//garbage
  temp.push_back(0.0);//x of normal
  temp.push_back(1.0);//y of normal
  temp.push_back(0.0);//z of normal
  temp.push_back(40.0);//length
  temp.push_back(40.0);//width
  ground->setStats(temp);
  tempVec.x = 0.0;
  tempVec.y = -1.0;
  tempVec.z = 0.0;
  ground->setPoM(tempVec);
  
  //temp.clear();
  //temp.push_back(0.3);//garbage
  //temp.push_back(0.0);//x of normal
  //temp.push_back(0.0);//y of normal
  //temp.push_back(1.0);//z of normal
  //temp.push_back(40.0);//length
  //temp.push_back(40.0);//width
  //Z1Wall->setStats(temp);
  //tempVec.x = 0.0;
  //tempVec.y = 0.0;
  //tempVec.z = -2.0;
  //Z1Wall->setPoM(tempVec);
  
  Vector<Scalar> gravity;
  gravity.x=0.0;
  gravity.y=-9.80665;
  gravity.z=0.0;
  initp->addForce(gravity);
  physics->addModel(-1, ground);
  physics->addModel(0,initp);
  //physics->addModel(-1, Z1Wall);
}

void Game::display(void)
{		
	physics->update();
	currentScene->draw();
}

void Game::keyboard(unsigned char key, int x, int y)
{
	physics->handleKeys(key,x,y);
	currentScene->KB(key,x,y);
}

void Game::skeyboard(int key, int x, int y)
{
	physics->handleSKeys(key,x,y);
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

bool Game::loadScene(const char* filename)
{   
	bool results = false;
	GLfloat diffuse[4];
    GLfloat spec[4];
    GLfloat shininess;
    GLfloat ambient[4];
    GLfloat emission[4];
    Model* model = 0;
    Material* mat = 0;
    Light* light = 0;
    string name;
    Scalar radius;
    Vector<Scalar> tempPos, tempRot, tempScale;
    
    long tempCount, tempLCount;
	  		
	vector<Scalar> temp;
    
   	delete physics;
    physics = new PListener(); 
 	physics->setScene(currentScene);
 	
 	PObject* pm;
  			
  	Vector<Scalar> gravity;
  	gravity.x=0.0;
  	gravity.y=-9.80665;
  	gravity.z=0.0;
        
	fstream file;
	file.open(filename, ios::in);
	
	if(!file.is_open())
		return results;
		
		file>>name;
	if(name.compare(LEVEL_FILE_VER)!=0)
		return results;
		
	currentScene->empty();
	
	file>>tempPos.x>>tempPos.y>>tempPos.z;
	file>>tempRot.x>>tempRot.y>>tempRot.z;
	file>>tempCount;
	file>>tempLCount;
	
	currentScene->moveCamera(tempPos);
	currentScene->rotateCamera(tempRot);
	
	//std::clog<<"World Pos: "<<worldPos.x<<worldPos.y<<worldPos.z<<std::endl;
	//std::clog<<"World Rot: "<<worldRot.x<<worldRot.y<<worldRot.z<<std::endl;
	//std::clog<<"count: "<<count<<std::endl;
	//std::clog<<"light count: "<<lcount<<std::endl;
	
	if(tempCount!=0)
	{
		std::clog<<"Loading models..."<<std::endl;
		for(int i = 0; i<tempCount;i++)
		{
			
			name.clear();
			file>>name;
			//std::clog<<" Model("<<i<<"): "<<name<<std::endl;
				  		
	  		model = new Model(name);
	  	
		  	file>>diffuse[0]>>diffuse[1]>>diffuse[2]>>diffuse[3];
		  	file>>spec[0]>>spec[1]>>spec[2]>>spec[3];
		  	file>>shininess;
		  	file>>ambient[0]>>ambient[1]>>ambient[2]>>ambient[3];
		  	file>>emission[0]>>emission[1]>>emission[2]>>emission[3];
		  	file>>tempPos.x>>tempPos.y>>tempPos.z;
		  	file>>tempRot.x>>tempRot.y>>tempRot.z;
		  	file>>tempScale.x>>tempScale.y>>tempScale.z;
	  	
	  		mat = new Material();
	  	
	  		mat->setDiffuse(diffuse[0],diffuse[1],diffuse[2],diffuse[3]);
	  		mat->setSpec(spec[0],spec[1],spec[2],spec[3]);
	  		mat->setShininess(shininess);
	  		mat->setAmbient(ambient[0],ambient[1],ambient[2],ambient[3]);
	  		mat->setEmission(emission[0],emission[1],emission[2],emission[3]);
	  		
	  		currentScene->addModel(model, mat);
	  		
	  		currentScene->rotateModel(i,tempRot);
	  		currentScene->moveModel(i,tempPos);
	  		currentScene->scaleModel(i,tempScale);
	  		
	  		pm = new POSphere();
	  		
	  		file>>radius;
  
  			temp.clear();
  			temp.push_back(0.4);//garbage
  			temp.push_back(radius);//radius of bounding sphere
  			std::clog<<"setting model to "<<tempPos.x<<", "<<tempPos.y<<", "<<tempPos.z<<std::endl;
  			pm->setPoM(tempPos);
  			pm->setStats(temp);
  			pm->addForce(gravity);
			physics->addModel(i,pm);
	  		
	  		//std::clog<<"Model("<<i<<"): "<<std::endl;
	  		//std::clog<<tempPos.x<<tempPos.y<<" "<<tempPos.z<<std::endl;
		  	//std::clog<<tempRot.x<<" "<<tempRot.y<<" "<<tempRot.z<<std::endl;
		  	//std::clog<<tempScale.x<<" "<<tempScale.y<<" "<<tempScale.z<<std::endl;
	  		
	  		model = 0;
		    mat = 0;
		    pm = 0;
		    std::clog<<"Progress: "<<(((float)i/(float)(tempCount-1))*100.0f)<<"%"<<std::endl;
		  }
		  std::clog<<"Models Loaded!"<<std::endl;
	  }
	  
	  if(tempLCount!=0)
	  {
	  	std::clog<<"Loading lights..."<<std::endl;
	  	for(int i=0;i<tempLCount;i++)
	  	{	  			
	  		light = new Light();
	  		
	  		currentScene->addLight(light);
	  		
	  		file>>tempPos.x>>tempPos.y>>tempPos.z;
	  		file>>tempRot.x>>tempRot.y>>tempRot.z;
	  		
	  		currentScene->moveLight(i,tempPos);
	  		currentScene->rotateLight(i,tempRot);
	  		
	  		light = 0;    
		}
		std::clog<<"Lights Loaded!"<<std::endl;
	  }
	  
	  //TEST GROUND TILL I FIGURE OUT HOW TO DENOTE THIS...
 	  PObject* ground = new POPlane();
	  temp.clear();
 	  temp.push_back(0.3);//garbage
	  temp.push_back(0.0);//x of normal
  	  temp.push_back(1.0);//y of normal
      temp.push_back(0.0);//z of normal
      temp.push_back(100.0);//length
      temp.push_back(100.0);//width
      ground->setStats(temp);
      tempPos.x = 0.0;
  	  tempPos.y = -1.0;
      tempPos.z = 0.0;
      ground->setPoM(tempPos);
      physics->addModel(-1, ground);
	  
	  file.close();
	  results = true;
	  std::clog<<"Scene Loaded!"<<std::endl;
	  return results;
}

void Game::saveScene(string filename)
{  
    Model* tempModel;
    Material* tempMat;
    Vector<Scalar> tempPos;
    Vector<Scalar> tempRot;
    long count, lcount, tempCount = 0;
        
    tempPos = currentScene->getCameraPos();
    tempRot = currentScene->getCameraRot(); 
    count = currentScene->getModelCount();
    lcount = currentScene->getLightCount();
        
	fstream file;
	file.open(filename.c_str(), ios::out);
	file<<LEVEL_FILE_VER<<std::endl;
	file<<tempPos.x<<" "<<tempPos.y<<" "<<tempPos.z<<std::endl;
	file<<tempRot.x<<" "<<tempRot.y<<" "<<tempRot.z<<std::endl;
	file<<count<<std::endl;
	file<<lcount<<std::endl;
	//if(root==0)
		//return;
	//current = root;
	//while(current != 0)
	  //{
	  	//file<<current->model->getName()<<"\n";
	  	
	  	//current->mat->getDiffuse(diffuse);
	  	//current->mat->getSpec(spec);
	  	//current->mat->getShininess(shininess);
	  	//current->mat->getAmbient(ambient);
	  	//current->mat->getEmission(emission);
	  	//file<<diffuse[0]<<" "<<diffuse[1]<<" "<<diffuse[2]<<" "<<diffuse[3]<<std::endl;
	  	//file<<spec[0]<<" "<<spec[1]<<" "<<spec[2]<<" "<<spec[3]<<std::endl;
	  	//file<<shininess<<std::endl;
	  	//file<<ambient[0]<<" "<<ambient[1]<<" "<<ambient[2]<<" "<<ambient[3]<<std::endl;
	  	//file<<emission[0]<<" "<<emission[1]<<" "<<emission[2]<<" "<<emission[3]<<std::endl;
	  	//file<<current->pos.x<<" "<<current->pos.y<<" "<<current->pos.z<<std::endl;
	  	//file<<current->rot.x<<" "<<current->rot.y<<" "<<current->rot.z<<std::endl;
	  	//file<<current->scale.x<<" "<<current->scale.y<<" "<<current->scale.z<<std::endl;
	    //file<<"\n";
	    //current = current->next;
	  //}
	  
	  //file<<"\n\n"<<std::endl;
	  
	  //if(lroot==0)
		//return;
	//lcurrent = lroot;
	//while(lcurrent != 0)
	  //{
	  	//file<<lcurrent->pos.x<<" "<<lcurrent->pos.y<<" "<<lcurrent->pos.z<<std::endl;
	  	//file<<lcurrent->rot.x<<" "<<lcurrent->rot.y<<" "<<lcurrent->rot.z<<std::endl;
	    
	    //lcurrent = lcurrent->next;
	  //}
	  file.close();
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
