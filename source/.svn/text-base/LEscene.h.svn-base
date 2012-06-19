#ifndef __SCENE_H__
#define __SCENE_H__

#define LEVEL_FILE_VER "version1.0"

#ifndef GLUT_WHEEL_UP
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
#endif

#define MOUSEXSENS (0.05f)
#define MOUSEYSENS (-0.1f)
#define MOUSEZOOM (0.3f)

//modes:
#define MAXNUM_KEYBOARD_MODES 4

#define KEYBOARDINPUT_MODE 950
#define SAVELEVEL_MODE 951
#define LOADLEVEL_MODE 952
#define LOADMODEL_MODE 953
#define LOADSHADER_MODE 954


//mouse flags:
#define MIDDLE_MOUSE 1000
#define LEFT_MOUSE 1001
#define RIGHT_MOUSE 1002
#define WHEEL_UP_MOUSE 1003
#define WHELL_DOWN_MOUSE 1004

//Mod Key flags:
#define SHIFT_KEY 1021
#define ALT_KEY 1022
#define CTRL_KEY 1023

#define KEY_MODEL_MOVE_X 900
#define KEY_MODEL_MOVE_Y 901
#define KEY_MODEL_MOVE_Z 902
#define KEY_MODEL_ROTATE_X 903
#define KEY_MODEL_ROTATE_Y 904
#define KEY_MODEL_ROTATE_Z 905
#define KEY_MODEL_SCALE 906
#define KEY_MODEL_SCALE_X 907
#define KEY_MODEL_SCALE_Y 908
#define KEY_MODEL_SCALE_Z 909

#define KEY_LIGHT_MOVE_X 910
#define KEY_LIGHT_MOVE_Y 911
#define KEY_LIGHT_MOVE_Z 912
#define KEY_LIGHT_ROTATE_X 913
#define KEY_LIGHT_ROTATE_Y 914
#define KEY_LIGHT_ROTATE_Z 915

#include "../ExGine/animatedModel.h"
#include "../ExGine/material.h"
#include "../ExGine/light.h"
#include "../ExGine/gui.h"
#include "../ExGine/FBO.h"
#include "../ExGine/prim.h"
#include "../ExGine/timer.h"

class Scene
{
public:
	Scene(){testGUI = new Gui();currentShaderID = 0;fbo = NULL;offset = blink= doFPS = pickMode=toFbo=false;root=current=0;full=0;lightToggle=toggle=count=0;worldRot.x = 0;worldRot.y = 0;worldRot.z = 0;worldPos.x = 0;worldPos.y = 0;worldPos.z = 0;};
	~Scene(){delete [] root; delete [] current;};
	void saveScene(string filename);
	bool loadScene(const char* filename);
	void draw(void);
	long addModel(Model* _model, Material* _mat);
	bool addLight(Light* _light);
	void KB(unsigned char key, int x, int y);
	void SKB(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void PassMouseMotion(int x, int y);
	void Reshape(int x, int y){windowX = x; windowY = y; if(fbo != NULL)fbo->setRes(x,y);testGUI->reshape(x,y);};
	
	void addShader(glslProgram* shader);
	void deleteShader();
	
	void moveCamera(Vector<float> pos);
	void moveCamera(float x, float y, float z);
	void moveCamera(char axis, float amount);
	void moveCameraInc(float xIncriment, float yIncriment, float zIncriment);
	void moveCameraInc(char axis, float incriment);
	void rotateCamera(Vector<float> rot);
	void rotateCamera(float aboutX, float aboutY, float aboutZ);
	void rotateCamera(char axis, float theta);
	void rotateCameraInc(float xIncriment, float yIncriment, float zIncriment);
	void rotateCameraInc(char axis, float incrimentTheta);
	Vector<float> getCameraPos();
	Vector<float> getCameraRot();
	
	void moveModel(long modelID, Vector<float> pos);
	void moveModel(long modelID, float x, float y, float z);
	void moveModel(long modelID, char axis, float amount);
	void moveModelInc(long modelID, float xIncriment, float yIncriment, float zIncriment);
	void moveModelInc(long modelID, char axis, float incriment);
	void rotateModel(long modelID, Vector<float> rot);
	void rotateModel(long modelID, float aboutX, float aboutY, float aboutZ);
	void rotateModel(long modelID, char axis, float theta);
	void rotateModelInc(long modelID, float xIncriment, float yIncriment, float zIncriment);
	void rotateModelInc(long modelID, char axis, float incrimentTheta);
	void scaleModel(long modelID, Vector<float> scale);
	void scaleModel(long modelID, float x, float y, float z);
	void scaleModel(long modelID, char axis, float amount);
	void scaleModelInc(long modelID, float xIncriment, float yIncriment, float zIncriment);
	void scaleModelInc(long modelID, char axis, float incriment);
	void toggleMipmaps(long modelID);
	//becareful with the return value from these, if the ID doesn't exsist there could be problems, I'll work it out later -Matt
	Vector<float> getModelPos(long modelID);
	Vector<float> getModelRot(long modelID);
	long* findModelID(char* name);
	const char* findName(long modelID);
	void instanceModel(long modelID);
	void duplicateModel(long modelID);
	long getCurrentSelection(){return toggle;};
	
	void moveLight(long lightID, Vector<float> pos);
	void moveLight(long lightID, float x, float y, float z);
	void moveLight(long lightID, char axis, float amount);
	void moveLightInc(long lightID, float xIncriment, float yIncriment, float zIncriment);
	void moveLightInc(long lightID, char axis, float incriment);
	void rotateLight(long lightID, Vector<float> rot);
	void rotateLight(long lightID, float aboutX, float aboutY, float aboutZ);
	void rotateLight(long lightID, char axis, float theta);
	void rotateLightInc(long lightID, float xIncriment, float yIncriment, float zIncriment);
	void rotateLightInc(long lightID, char axis, float incrimentTheta);
	//becareful with the return value from these, if the ID doesn't exsist there could be problems, I'll work it out later -Matt
	Vector<float> getLightPos(long lightID);
	Vector<float> getLightRot(long lightID);
protected:
	void empty();
	bool exists(long modelID);
	void soundOff();

	struct MNode
	{
		long ID;
		MNode* next;
		Model* model;
	    Material* mat;
		
		Vector<float> rot;
		Vector<float> pos;
		Vector<float> scale;
	};

	MNode* root;
	MNode* current;
	
	struct LNode
	{
		long ID;
		LNode* next;
		Light* light;
		
		Vector<float> rot;
		Vector<float> pos;
	};

	LNode* lroot;
	LNode* lcurrent;

	bool full;

	long count;
	long lcount;
	
	Vector<float> worldRot;
	Vector<float> worldPos;
private:
	bool map[1024];
	FBO* fbo;
	int mouseX, mouseY;
	int windowX, windowY;

	//for testing
	Timer fpsTimer;
	bool doFPS;
	bool toFbo;
	bool pickMode;
	bool offset;
	bool blink;
	long toggle;
	long lightToggle;
	Gui* testGUI;
	vector<glslProgram*> shaders;
	unsigned int currentShaderID;
};

void Scene::draw(void)
{  
	static bool first = true;
	//static glslProgram* genericShader = new glslProgram("data/shaders/fragLight.vs","data/shaders/fragLight.fs");
	//static glslProgram* nmbShader = new glslProgram("data/shaders/nmb.vs","data/shaders/nmb.fs");
	//static glslProgram* csmShader = new glslProgram("data/shaders/csm.vs","data/shaders/csm.fs");
	//static glslProgram* nmbShader = new glslProgram("data/shaders/SteepParallax.vs","data/shaders/SteepParallax.vrt");
	if(first)
	{
		shaders.push_back(new glslProgram("data/shaders/fragLight.vs","data/shaders/fragLight.fs"));
		shaders.push_back(new glslProgram("data/shaders/nmb.vs","data/shaders/nmb.fs"));
		shaders.push_back(new glslProgram("data/shaders/csm.vs","data/shaders/csm.fs"));
		shaders.push_back(new glslProgram("data/shaders/test.vs","data/shaders/test.fs"));
		//string log;
		//genericShader->GetProgramLog(log);
		//std::clog<<"Generic Shader Log:\n"<<log<<std::endl;
		//nmbShader->GetProgramLog(log);
		//std::clog<<"NMB Shader Log:\n"<<log<<std::endl;
		first = false;
	}
	//testing GUI
	//testGUI->draw();
	
	//for model blink
	static bool draw = true;
	static Timer blinkFrame;
	
	Plane* panel;
	if(toFbo)
	{
		if(fbo == NULL)
			fbo = new FBO();
		fbo->attach();
		panel = new Plane();
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();	
	glPushMatrix();
  	glTranslatef(0.0, 0.0, -5.0);
  
	glPushMatrix();
	glTranslatef(worldPos.x, worldPos.y, worldPos.z);
	glRotatef(worldRot.x, 1.0, 0.0, 0.0);
	glRotatef(worldRot.y, 0.0, 1.0, 0.0);
	glRotatef(worldRot.z, 0.0, 0.0, 1.0);
	
	if(root!=0)
	{
		current = root;
		while(current != 0)
		  {
		  	glPushMatrix();
		  	glTranslatef(current->pos.x, current->pos.y, current->pos.z);
			glRotatef(current->rot.x, 1.0, 0.0, 0.0);
			glRotatef(current->rot.y, 0.0, 1.0, 0.0);
			glRotatef(current->rot.z, 0.0, 0.0, 1.0);
			glScalef(current->scale.x,current->scale.y,current->scale.z);
			
//			current->mat->addToModel();
			if(pickMode)
			{
				current->model->draw(0,false);
			}
			else
			{
				if(offset&&current->ID==toggle)
				{
					//for offset line... 
					glEnable(GL_POLYGON_OFFSET_FILL);
					
					glPolygonOffset(2.0f, 2.0f);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					
					glDisable(GL_LIGHTING);
					current->model->draw(0,false);
					glEnable(GL_LIGHTING);
					
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					if(currentShaderID == 0)
						current->model->draw();
					else
						current->model->draw(shaders[currentShaderID-1]);
					
					glDisable(GL_POLYGON_OFFSET_FILL);
				}
				else if(blink&&current->ID==toggle)
				{
					if (!blinkFrame.isRunning())
						blinkFrame.start();
					if(blinkFrame.delta()>500)
					{
						draw = draw?false:true;
						blinkFrame.reset();
					}
					if(draw)
					{
						if(currentShaderID == 0)
							current->model->draw();
						else
							current->model->draw(shaders[currentShaderID-1]);
					}
				}
				else
					if(currentShaderID == 0)
						current->model->draw();
					else
	        			current->model->draw(shaders[currentShaderID-1]);
	        }
		    glPopMatrix();
	    
		    current = current->next;
		  }
	}  
	  if(lroot!=0)
	{
		lcurrent = lroot;
		while(lcurrent != 0)
		  {
		  	glPushMatrix();
			glRotatef(lcurrent->rot.x, 1.0, 0.0, 0.0);
			glRotatef(lcurrent->rot.y, 0.0, 1.0, 0.0);	
			glRotatef(lcurrent->rot.z, 0.0, 0.0, 1.0);
			
		    lcurrent->light->draw();
		    glPopMatrix();
		    
		    lcurrent = lcurrent->next;
		  }
	  }
	  
	  glPopMatrix();	  	  
	  glPopMatrix();
	  if(toFbo)
	  {
	  	fbo->detach();	
	  	
	  	if(fbo->bindTextures())
	  	{
	  		
	  		panel->draw();
	  		//std::clog<<"Drawing to FBO\n";
	  	}
	  }
	
		 if(doFPS)
	{  
		//glMatrixMode(GL_PROJECTION);
		//glPushMatrix();
		//glLoadIdentity();
		//gluOrtho2D(0,640, 0, 480);
		//glScalef(1,-1,1);
		//glMatrixMode(GL_MODELVIEW);
		//glTranslatef(0.0f,0.0f, -5.0f);
		static int frame = 0;
		//static char fps[20];
		//char* temp;
		
		frame++;
	
		if (!fpsTimer.isRunning())
			fpsTimer.start();
		if(fpsTimer.delta()>1000)
		{	
			std::clog<<"FPS: "<<(frame*1000.0f/(fpsTimer.delta()))<<std::endl;	
			//sprintf(fps,"FPS:%4.2f",frame*5000.0f/(fpsTimer.delta()));
			fpsTimer.reset();
			frame = 0;
		}
		
		//glColor3f(1.0f,1.0f,1.0f);
		//for(temp=fps;*temp != '\0';temp++)
		//{
			//glutStrokeCharacter(GLUT_STROKE_ROMAN,*temp);
		//}
		//glMatrixMode(GL_PROJECTION);
		//glPopMatrix();
		//glMatrixMode(GL_MODELVIEW);
	}
	
	  glutSwapBuffers();
}

long Scene::addModel(Model* _model,Material* _mat)
{
	long tempID=-1;
	bool done=false;
  if(count == 0||root==0)
    {
    	std::clog<<"making root"<<std::endl;
    	root = new MNode;
    	current = root;
    	//root->model = new Model;
    	root->mat = _mat;
    	root->model = _model;
    	root->next = 0;
    	root->ID = 0;
    	count = 1;
    	current =root;
    }
  else
  {
  		std::clog<<"making leaf"<<std::endl;
    	current =root;
		while(current->next != 0)
	 		current = current->next;

	  	for(long i=0;i<=count&&!done;i++)
	  	{
	  		std::clog<<"testing "<<i<<std::endl;
	  		if (!exists(i))
 	 		{
 	 			std::clog<<"found free at "<<i<<std::endl;
	  			tempID = i;
	  			done = true;
	  		}
		}//*/

	  current->next = new MNode;
	  current->next->model = _model;
	  current->next->mat = _mat;
	  current->next->next = 0;	  
	  //std::clog<<"Next assigned: "<<tempID<<std::endl;
	  current->next->ID = tempID;
 	  count++;
 	  current = current->next;
  }
  current->rot.x = 0;
  current->rot.y = 0;
  current->rot.z = 0;
  
  current->pos.x = 0;
  current->pos.y = 0;
  current->pos.z = 0;

  current->scale.x = 1.0;
  current->scale.y = 1.0;
  current->scale.z = 1.0;
  
  return current->ID;
}

bool Scene::addLight(Light* _light)
{
	if(lcount == 8)
		return false;
  if(lroot == 0)
    {
      lroot = new LNode;
      lcurrent = lroot;
      //lroot->light = new Light;
      lroot->light = _light;
      lroot->next = 0;
      lroot->ID = 0;
      lcount = 1;
      return true;
    }

      lcurrent = lroot;
  while(lcurrent->next != 0)
    lcurrent = lcurrent->next;

  lcurrent->next = new LNode;
  //lcurrent->light = new Light;
  lcurrent->next->light = _light;
  lcurrent->next->next = 0;
  lcurrent->next->ID = count;
  lcount++;
  lcurrent = lcurrent->next;
  
  lcurrent->rot.x = 0;
  lcurrent->rot.y = 0;
  lcurrent->rot.z = 0;
  
  lcurrent->pos.x = 0;
  lcurrent->pos.y = 0;
  lcurrent->pos.z = 0;
  
  return true;
}

void Scene::KB(unsigned char key, int x, int y)
{
	Model* tempm = 0;
	Material* tmat = 0;
	Light* templ = 0;
	static string temp, temp2;
	static bool firstName = true;
	int mod = glutGetModifiers();
	
	if(!map[KEYBOARDINPUT_MODE])
	{
		if(mod == GLUT_ACTIVE_SHIFT)
			map[SHIFT_KEY] = true;
		else
			map[SHIFT_KEY] = false;
			
		if(mod == GLUT_ACTIVE_ALT)
			map[ALT_KEY] = true;
		else
			map[ALT_KEY] = false;
		
		if(mod == GLUT_ACTIVE_CTRL)
			map[CTRL_KEY] = true;
		else
			map[CTRL_KEY] = false;
	
		switch(key)
		{
			//esc key
			case 27:
			//case 'q':
			//case 'Q':
					//glutLeaveGameMode();
					exit(0);
					break;
					
			case 'z':
			case 'Z':
				moveModelInc(toggle,'y',-0.1);
				if(map[SHIFT_KEY])
					moveModelInc(toggle,'y',-0.1);
				break;
				
			case 'x':
			case 'X':
				moveModelInc(toggle,'y',0.1);
				if(map[SHIFT_KEY])
					moveModelInc(toggle,'y',0.1);
				break;
				
			case 'a':
			case 'A':
				rotateModelInc(toggle,'y',-1);
				if(map[SHIFT_KEY])
					rotateModelInc(toggle,'y',-1);
				break;	
				
			case 'd':
			case 'D':
				rotateModelInc(toggle,'y',1);
				if(map[SHIFT_KEY])
					rotateModelInc(toggle,'y',1);
				break;	
				
			case 'w':
			case 'W':
				rotateModelInc(toggle,'x',-1);
				if(map[SHIFT_KEY])
					rotateModelInc(toggle,'x',-1);
				break;
				
			case 's':
			case 'S':
				rotateModelInc(toggle,'x',1);
				if(map[SHIFT_KEY])
					rotateModelInc(toggle,'x',1);
				break;
				
			case 'e':
			case 'E':
				rotateModelInc(toggle,'z',1);
				if(map[SHIFT_KEY])
					rotateModelInc(toggle,'z',1);
				break;
				
			case 'c':
			case 'C':
				rotateModelInc(toggle,'z',-1);
				if(map[SHIFT_KEY])
					rotateModelInc(toggle,'z',-1);
				break;
				
			case 'j':
			case 'J':
				moveLightInc(lightToggle,'y',-0.1);
				if(map[SHIFT_KEY])
					moveLightInc(lightToggle,'y',-0.1);
				break;
				
			case 'u':
			case 'U':
				moveLightInc(lightToggle,'y',0.1);
				if(map[SHIFT_KEY])
					moveLightInc(lightToggle,'y',0.1);
				break;
				
			case 'h':
			case 'H':
				moveLightInc(lightToggle,'x',-0.1);
				if(map[SHIFT_KEY])
					moveLightInc(lightToggle,'x',-0.1);
				break;	
				
			case 'k':
			case 'K':
				moveLightInc(lightToggle,'x',0.1);
				if(map[SHIFT_KEY])
				moveLightInc(lightToggle,'x',0.1);
				break;	
				
			case 't':
				//do
				//{
				toggle++;
				if(toggle == count)
					toggle = 0;
				//}while(!exists(toggle));
				std::clog<<"Switching to model\""<<findName(toggle)<<"\"."<<std::endl;
				break;
			case 'T':
				lightToggle++;
				if(lightToggle == lcount)
					lightToggle = 0;
				std::clog<<"Switching to Light["<<lightToggle<<"]."<<std::endl;
				break;
			case 'i':
			case 'I':
				map[KEYBOARDINPUT_MODE] = true;
				map[LOADMODEL_MODE] = true;
				break;
			case 'o':
			case 'O':
				map[KEYBOARDINPUT_MODE] = true;
				map[SAVELEVEL_MODE] = true;
				break;
			case 'p':
			case 'P':
				map[KEYBOARDINPUT_MODE] = true;
				map[LOADLEVEL_MODE] = true;
				break;
			case '-':
				break;
			case '_':
				empty();
				break;
			case ']':
				soundOff();
				break;
			case 'f':
				instanceModel(toggle);
				break;
			case 'F':
				duplicateModel(toggle);
				break;
			case 0:
				if(y == 0)//double check
				{
					map[x] = true;
					if(x == SAVELEVEL_MODE || x == LOADLEVEL_MODE || x == LOADMODEL_MODE || x == LOADSHADER_MODE)
						map[KEYBOARDINPUT_MODE] = true;
				}
				break;
			case 'l':
			case 'L':
				templ = new Light();
				addLight(templ);
				default:
				break;	
			case 'g':
			case 'G':
				currentShaderID++;
				//std::clog<<"# of shaders loaded: "<<shaders.size()<<"\n";
				if(shaders.size()+1<=currentShaderID)
					currentShaderID=0;
				std::clog<<"Changed to shader:"<<currentShaderID<<" named: "<<((currentShaderID!=0)?shaders[currentShaderID-1]->getName():"fixed-pipeline")<<"\n";
				break;
			case 'v':
				deleteShader();
				break;
			case 'V':
				map[KEYBOARDINPUT_MODE] = true;
				map[LOADSHADER_MODE] = true;
				firstName =true;
				break;
		}
	}
	else
	{
		switch(key)
		{
			case 13: //ENTER
				if(map[SAVELEVEL_MODE])
				{
					saveScene(temp);
					for(int i = KEYBOARDINPUT_MODE; i<=KEYBOARDINPUT_MODE+MAXNUM_KEYBOARD_MODES;i++)
						map[i] = false;
					clog<<"Final:"<<temp<<"\n";
					temp.clear();
					break;
				}	
				if(map[LOADMODEL_MODE])
				{
					tmat = new Material();
					tempm = new Model(temp);
					addModel(tempm,tmat);	
					for(int i = KEYBOARDINPUT_MODE; i<=KEYBOARDINPUT_MODE+MAXNUM_KEYBOARD_MODES;i++)
						map[i] = false;
					clog<<"Final:"<<temp<<"\n";
					temp.clear();
					break;
				}		
				if(map[LOADLEVEL_MODE])
				{
					loadScene(temp.c_str());
					for(int i = KEYBOARDINPUT_MODE; i<=KEYBOARDINPUT_MODE+MAXNUM_KEYBOARD_MODES;i++)
						map[i] = false;
					clog<<"Final:"<<temp<<"\n";
					temp.clear();
					break;
				}
				if(map[LOADSHADER_MODE])
				{
					if (firstName)
					{
						temp2 = temp;
						temp.clear();
						firstName = false;
					}
					else
					{
						addShader(new glslProgram(temp2, temp));	
						for(int i = KEYBOARDINPUT_MODE; i<=KEYBOARDINPUT_MODE+MAXNUM_KEYBOARD_MODES;i++)
							map[i] = false;
						clog<<"Final:"<<temp<<" and "<<temp2<<"\n";
						temp.clear();temp2.clear();
					}
					break;
				}	
			case 27: //ESC				
				for(int i = KEYBOARDINPUT_MODE; i<=KEYBOARDINPUT_MODE+MAXNUM_KEYBOARD_MODES;i++)
					map[i] = false;
				clog<<"Final:"<<temp<<"\n";
				temp.clear();
				break;
			case 8: //BACKSPACE
			     if(temp.length()>0)
			     	temp.erase(temp.length()-1);
				clog<<temp<<"\n";
				break;
			case 127: //DELETE
				break;
			default:
				if(key != 0)
					temp.push_back((char)key);
				clog<<temp<<"\n";
		}
	}
}

void Scene::SKB(int key, int x, int y)
{
	int mod = glutGetModifiers();
	
	if(mod == GLUT_ACTIVE_SHIFT)
		map[SHIFT_KEY] = true;
	else
		map[SHIFT_KEY] = false;
		
	if(mod == GLUT_ACTIVE_ALT)
		map[ALT_KEY] = true;
	else
		map[ALT_KEY] = false;
		
	if(mod == GLUT_ACTIVE_CTRL)
		map[CTRL_KEY] = true;
	else
		map[CTRL_KEY] = false;
	
	switch(key)
	{
		case GLUT_KEY_F1:
			std::clog<<"TOGGLE FULLSCREEN"<<std::endl;
			if (full)
			{
				full=false;
				glutFullScreen();
			}
			else
			{
				full=true;
				glutReshapeWindow(600, 600);
				glutPositionWindow(50, 50);
			}
			break;
		case GLUT_KEY_F2:
			std::clog<<"TOGGLE LIGHTING"<<std::endl;
			if (glIsEnabled(GL_LIGHTING))
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			break;
		case GLUT_KEY_F3:
			std::clog<<"TOGGLE TEXTURE"<<std::endl;
			glActiveTexture(GL_TEXTURE0);
			if (glIsEnabled(GL_TEXTURE_2D))
				glDisable(GL_TEXTURE_2D);
			else
				glEnable(GL_TEXTURE_2D);
			break;
		case GLUT_KEY_F4:
			std::clog<<"TOGGLE MIPMAPS"<<std::endl;
			toggleMipmaps(toggle);
			break;
		case GLUT_KEY_F5:
			std::clog<<"TOGGLE RENDER TO FBO"<<std::endl;
			if(toFbo)
				toFbo = false;
			else 
				toFbo = true;
			break;
		case GLUT_KEY_F6:
			if(pickMode)
			{
				pickMode = false;
				std::clog<<"PICK MODE OFF"<<std::endl;
				glEnable(GL_LIGHTING);
				glEnable(GL_BLEND);
				//glEnable(GL_FOG);	
			}
			else
			{	
				pickMode = true;
				std::clog<<"PICK MODE ON"<<std::endl;
				glDisable(GL_LIGHTING);
				glDisable(GL_BLEND);
				//glDisable(GL_FOG);		
			}
			break;
		case GLUT_KEY_F7:
			doFPS = doFPS?false:true;
			if(doFPS)
				std::clog<<"FPS ON"<<std::endl;
			else
				std::clog<<"FPS OFF"<<std::endl;
			break;
		case GLUT_KEY_F8:
			offset = offset?false:true;
			blink = blink?false:true;
			if(offset)
				std::clog<<"SELECTION OFFSET ON"<<std::endl;
			else
				std::clog<<"SELECTION BLINK ON"<<std::endl;
			break;
		case GLUT_KEY_UP:
			moveModelInc(toggle,'z',-0.1);
			if(map[SHIFT_KEY])
				moveModelInc(toggle,'z',-0.1);
			break;
			
		case GLUT_KEY_DOWN:
			moveModelInc(toggle,'z',0.1);
			if(map[SHIFT_KEY])
				moveModelInc(toggle,'z',0.1);
			break;
		
		case GLUT_KEY_LEFT:
			moveModelInc(toggle,'x',-0.1);
			if(map[SHIFT_KEY])
				moveModelInc(toggle,'x',-0.1);
			break;
			
		case GLUT_KEY_RIGHT:
			moveModelInc(toggle,'x',0.1);
			if(map[SHIFT_KEY])
				moveModelInc(toggle,'x',0.1);
			break;
	}
}

void Scene::Mouse(int button, int state, int x, int y)
{
	int mod = glutGetModifiers();
	
	switch(button)
	{
		case GLUT_MIDDLE_BUTTON:
			if (state == GLUT_DOWN)
			{
				//std::clog<<"state: down ("<<x<<","<<y<<") "<<std::endl;
				mouseX = x;
				mouseY = y;
				map[MIDDLE_MOUSE] = true;
				
				if(mod == GLUT_ACTIVE_SHIFT)
					map[SHIFT_KEY] = true;
				if(mod == GLUT_ACTIVE_ALT)
					map[ALT_KEY] = true;
				if(mod == GLUT_ACTIVE_CTRL)
					map[ALT_KEY] = true;
			}
			if (state == GLUT_UP)
			{
				//std::clog<<"state: up ("<<x<<","<<y<<") "<<std::endl;
				if(mod != GLUT_ACTIVE_SHIFT)
					map[SHIFT_KEY] = false;
				if(mod != GLUT_ACTIVE_ALT)
					map[ALT_KEY] = false;
				if(mod != GLUT_ACTIVE_CTRL)
					map[ALT_KEY] = false;
				map[MIDDLE_MOUSE] = false;
			}
			break;
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)
			{
				//clear menu flags
				for(int i = KEY_MODEL_MOVE_X;i<=KEY_LIGHT_ROTATE_Z;i++)
					map[i] = false;
				
				//mouse select code
				
				//std::clog<<"MOUSE SELECT"<<std::endl;
				
				if(fbo == NULL)
					fbo = new FBO();
				
				fbo->attach();
				
				glDisable(GL_LIGHTING);
				glActiveTexture(GL_TEXTURE0);
				glDisable(GL_TEXTURE_2D);
				glActiveTexture(GL_TEXTURE1);
				glDisable(GL_TEXTURE_2D);
				//glDisable(GL_FOG);
				
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
				glLoadIdentity();	
				glPushMatrix();
 			 	glTranslatef(0.0, 0.0, -5.0);
  
				glPushMatrix();
				glTranslatef(worldPos.x, worldPos.y, worldPos.z);
				glRotatef(worldRot.x, 1.0, 0.0, 0.0);
				glRotatef(worldRot.y, 0.0, 1.0, 0.0);
				glRotatef(worldRot.z, 0.0, 0.0, 1.0);
	
				if(root!=0)
				{
					current = root;
					while(current != 0)
					  {
						glPushMatrix();
					  	glTranslatef(current->pos.x, current->pos.y, current->pos.z);
						glRotatef(current->rot.x, 1.0, 0.0, 0.0);
						glRotatef(current->rot.y, 0.0, 1.0, 0.0);
						glRotatef(current->rot.z, 0.0, 0.0, 1.0);
						glScalef(current->scale.x,current->scale.y,current->scale.z);
			
				        current->model->draw(0,false);
					    glPopMatrix();
	    
					    current = current->next;
					  }
				  glPopMatrix();
				}  

	 			 glPopMatrix();
	 			 
	 			 GLubyte pix[3];
	 			 
	 			 GLint VP[4];
	 			 glGetIntegerv(GL_VIEWPORT, VP);
	 			 
	 			 glReadPixels(x, VP[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pix);
	 			 
			  	fbo->detach();		
			  	
			  	if(root!=0)
				{
					current = root;
					while(current != 0)
					  {
					  	if(current->model->checkColor(pix))
					  	{
					  		toggle = current->ID;
					  		std::clog<<"MOUSE SELECT FOUND!! @:"<<toggle<<std::endl;
							glActiveTexture(GL_TEXTURE0);
							glEnable(GL_TEXTURE_2D);
							glActiveTexture(GL_TEXTURE1);
							glEnable(GL_TEXTURE_2D);
					  		glEnable(GL_LIGHTING);
							//glEnable(GL_FOG);
					  		break;
					  	}
					  	//std::clog<<"MOUSE SELECT !found yet"<<std::endl;
					  	
					    current = current->next;
					  }
					  	glEnable(GL_LIGHTING);
						glActiveTexture(GL_TEXTURE0);
						glEnable(GL_TEXTURE_2D);
						glActiveTexture(GL_TEXTURE1);
						glEnable(GL_TEXTURE_2D);
						//glEnable(GL_FOG);
				}  
			}
			break;
		case GLUT_WHEEL_UP:
			if(state == GLUT_UP)
			{
				moveCameraInc(0,0,MOUSEZOOM);
				if(mod == GLUT_ACTIVE_SHIFT)
					moveCameraInc(0,0,MOUSEZOOM);
			}
			break;
		case GLUT_WHEEL_DOWN:
			if(state == GLUT_UP)
			{
				moveCameraInc(0,0,-MOUSEZOOM);
				if(mod == GLUT_ACTIVE_SHIFT)
					moveCameraInc(0,0,-MOUSEZOOM);
			}
			break;
	}
	glutPostRedisplay();
	return;
}

void Scene::moveModel(long modelID, Vector<float> pos)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->pos.x=pos.x;
			current->pos.y=pos.y;
			current->pos.z=pos.z;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::moveModel(long modelID, float x, float y, float z)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->pos.x=x;
			current->pos.y=y;
			current->pos.z=z;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
} 
  
void Scene::moveModel(long modelID, char axis, float amount)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			switch(axis){
				case 'x':
				case 'X':
					current->pos.x = amount;
					break;
				case 'y':
				case 'Y':
					current->pos.y = amount;
					break;
				case 'z':
				case 'Z':
					current->pos.z = amount;
					break;
				default:
					break;
				}
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}    

void Scene::moveModelInc(long modelID, float xIncriment, float yIncriment, float zIncriment)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->pos.x+=xIncriment;
			current->pos.y+=yIncriment;
			current->pos.z+=zIncriment;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::moveModelInc(long modelID, char axis, float incriment)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			switch(axis){
				case 'x':
				case 'X':
					current->pos.x += incriment;
					break;
				case 'y':
				case 'Y':
					current->pos.y += incriment;
					break;
				case 'z':
				case 'Z':
					current->pos.z += incriment;
					break;
				default:
					break;
				}
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::rotateModel(long modelID, Vector<float> rot)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->rot.x=rot.x;
			current->rot.y=rot.y;
			current->rot.z=rot.z;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::rotateModel(long modelID, float aboutX, float aboutY, float aboutZ)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->rot.x=aboutX;
			current->rot.y=aboutY;
			current->rot.z=aboutZ;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
} 
  
void Scene::rotateModel(long modelID, char axis, float theta)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			switch(axis){
				case 'x':
				case 'X':
					current->rot.x = theta;
					break;
				case 'y':
				case 'Y':
					current->rot.y = theta;
					break;
				case 'z':
				case 'Z':
					current->rot.z = theta;
					break;
				default:
					break;
				}
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}    

void Scene::rotateModelInc(long modelID, float xIncriment, float yIncriment, float zIncriment)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->rot.x+=xIncriment;
			current->rot.y+=yIncriment;
			current->rot.z+=zIncriment;
			
			if(current->rot.x < 0)
				current->rot.x+=360;
			if(current->rot.x > 360)
				current->rot.x-=360;
				
			if(current->rot.y < 0)
				current->rot.y+=360;
			if(current->rot.y > 360)
				current->rot.y-=360;
				
			if(current->rot.z < 0)
				current->rot.z+=360;
			if(current->rot.z > 360)
				current->rot.z-=360;
			
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::rotateModelInc(long modelID, char axis, float incrimentTheta)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
	{
		return;
	}
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			switch(axis){
				case 'x':
				case 'X':
					current->rot.x += incrimentTheta;
					if(current->rot.x < 0)
						current->rot.x+=360;
					if(current->rot.x > 360)
						current->rot.x-=360;
					break;
				case 'y':
				case 'Y':
					current->rot.y += incrimentTheta;
					if(current->rot.y < 0)
						current->rot.y+=360;
					if(current->rot.y > 360)
						current->rot.y-=360;
					break;
				case 'z':
				case 'Z':
					current->rot.z += incrimentTheta;
					if(current->rot.z < 0)
						current->rot.z+=360;
					if(current->rot.z > 360)
						current->rot.z-=360;
					break;
				default:
					break;
				}
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::scaleModel(long modelID, Vector<float> scale)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->scale.x=scale.x;
			current->scale.y=scale.y;
			current->scale.z=scale.z;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::scaleModel(long modelID, float x, float y, float z)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->scale.x=x;
			current->scale.y=y;
			current->scale.z=z;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
} 
  
void Scene::scaleModel(long modelID, char axis, float amount)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			switch(axis){
				case 'x':
				case 'X':
					current->scale.x = amount;
					break;
				case 'y':
				case 'Y':
					current->scale.y = amount;
					break;
				case 'z':
				case 'Z':
					current->scale.z = amount;
					break;
				default:
					break;
				}
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}    

void Scene::scaleModelInc(long modelID, float xIncriment, float yIncriment, float zIncriment)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->scale.x+=xIncriment;
			current->scale.y+=yIncriment;
			current->scale.z+=zIncriment;
			
			if(current->scale.x<0)
				current->scale.x = 0.0f;
			if(current->scale.y<0)
				current->scale.y = 0.0f;
			if(current->scale.z<0)
				current->scale.z = 0.0f;
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::scaleModelInc(long modelID, char axis, float incriment)
{
	//check for valid modelID
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			switch(axis){
				case 'x':
				case 'X':
					current->scale.x += incriment;
					break;
				case 'y':
				case 'Y':
					current->scale.y += incriment;
					break;
				case 'z':
				case 'Z':
					current->scale.z += incriment;
					break;
				default:
					break;
				}
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

Vector<float> Scene::getModelPos(long modelID)
{
		//check for valid modelID
	if(modelID<0||modelID>=count)
	{
		Vector<float> temp;
		return temp;
	}
	if(root == NULL)
	{
		Vector<float> temp;
		return temp;
	}
	current=root;	

	do{
		if(current->ID == modelID)
		{
			return current->pos;
		}
		current=current->next;
	}
	while(current != NULL);
	Vector<float> temp;
	return temp;
}

Vector<float> Scene::getModelRot(long modelID)
{
		//check for valid modelID
	if(modelID<0||modelID>=count)
	{
		Vector<float> temp;
		return temp;
	}
	if(root == NULL)
	{
		Vector<float> temp;
		return temp;
	}
	current=root;	

	do{
		if(current->ID == modelID)
		{
			return current->rot;
		}
		current=current->next;
	}
	while(current != NULL);
	Vector<float> temp;
	return temp;
}

const char* Scene::findName(long modelID)
{
if(modelID<0||modelID>=count)
		return 0;
	if(root == NULL)
		return 0;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			return current->model->getName();
		}
		current=current->next;
	}
	while(current != NULL);
	return 0;
}

//This function does duplicate , but you will not be able to mouse select the duplicate... you can't "t" select it though
void Scene::instanceModel(long modelID)
{	
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			addModel(current->model, current->mat);
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;

}

//This function does duplicate , but you will not be able to mouse select the duplicate... you can't "t" select it though
void Scene::duplicateModel(long modelID)
{
	string tempnam;
	Model* mtemp;
	
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			tempnam = findName(modelID);
			mtemp = new Model(tempnam);
			addModel(mtemp, current->mat);
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;

}

void Scene::saveScene(string filename)
{  
	GLfloat diffuse[4];
    GLfloat spec[4];
    GLfloat shininess;
    GLfloat ambient[4];
    GLfloat emission[4];
        
	fstream file;
	file.open(filename.c_str(), ios::out);
	file<<LEVEL_FILE_VER<<std::endl;
	file<<worldPos.x<<" "<<worldPos.y<<" "<<worldPos.z<<std::endl;
	file<<worldRot.x<<" "<<worldRot.y<<" "<<worldRot.z<<std::endl;
	file<<count<<std::endl;
	file<<lcount<<std::endl;
	if(root==0)
		return;
	current = root;
	while(current != 0)
	  {
	  	file<<current->model->getName()<<"\n";
	  	
	  	current->mat->getDiffuse(diffuse);
	  	current->mat->getSpec(spec);
	  	current->mat->getShininess(shininess);
	  	current->mat->getAmbient(ambient);
	  	current->mat->getEmission(emission);
	  	file<<diffuse[0]<<" "<<diffuse[1]<<" "<<diffuse[2]<<" "<<diffuse[3]<<std::endl;
	  	file<<spec[0]<<" "<<spec[1]<<" "<<spec[2]<<" "<<spec[3]<<std::endl;
	  	file<<shininess<<std::endl;
	  	file<<ambient[0]<<" "<<ambient[1]<<" "<<ambient[2]<<" "<<ambient[3]<<std::endl;
	  	file<<emission[0]<<" "<<emission[1]<<" "<<emission[2]<<" "<<emission[3]<<std::endl;
	  	file<<current->pos.x<<" "<<current->pos.y<<" "<<current->pos.z<<std::endl;
	  	file<<current->rot.x<<" "<<current->rot.y<<" "<<current->rot.z<<std::endl;
	  	file<<current->scale.x<<" "<<current->scale.y<<" "<<current->scale.z<<std::endl;
	    file<<"\n";
	    current = current->next;
	  }
	  
	  file<<"\n\n"<<std::endl;
	  
	  if(lroot==0)
		return;
	lcurrent = lroot;
	while(lcurrent != 0)
	  {
	  	file<<lcurrent->pos.x<<" "<<lcurrent->pos.y<<" "<<lcurrent->pos.z<<std::endl;
	  	file<<lcurrent->rot.x<<" "<<lcurrent->rot.y<<" "<<lcurrent->rot.z<<std::endl;
	    
	    lcurrent = lcurrent->next;
	  }
	  file.close();
}

bool Scene::loadScene(const char* filename)
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
    Vector<float> tempPos, tempRot, tempScale;
    
    long tempCount, tempLCount;
    
        
	fstream file;
	file.open(filename, ios::in);
	
	if(!file.is_open())
		return results;
		
		file>>name;
	if(name.compare(LEVEL_FILE_VER)!=0)
		return results;
		
	empty();
	
	file>>worldPos.x>>worldPos.y>>worldPos.z;
	file>>worldRot.x>>worldRot.y>>worldRot.z;
	file>>tempCount;
	file>>tempLCount;
	
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
	  		
	  		addModel(model, mat);
	  		
	  		rotateModel(i,tempRot);
	  		moveModel(i,tempPos);
	  		scaleModel(i,tempScale);
	  		
	  		//std::clog<<"Model("<<i<<"): "<<std::endl;
	  		//std::clog<<tempPos.x<<tempPos.y<<" "<<tempPos.z<<std::endl;
		  	//std::clog<<tempRot.x<<" "<<tempRot.y<<" "<<tempRot.z<<std::endl;
		  	//std::clog<<tempScale.x<<" "<<tempScale.y<<" "<<tempScale.z<<std::endl;
	  		
	  		model = 0;
		    mat = 0;
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
	  		
	  		addLight(light);
	  		
	  		file>>tempPos.x>>tempPos.y>>tempPos.z;
	  		file>>tempRot.x>>tempRot.y>>tempRot.z;
	  		
	  		moveLight(i,tempPos);
	  		rotateLight(i,tempRot);
	  		
	  		light = 0;    
		}
		std::clog<<"Lights Loaded!"<<std::endl;
	  }
	  
	  file.close();
	  results = true;
	  std::clog<<"Scene Loaded!"<<std::endl;
	  return results;
}

void Scene::toggleMipmaps(long modelID)
{
	if(modelID<0||modelID>=count)
		return;
	if(root == NULL)
		return;
	current=root;	

	do{
		if(current->ID == modelID)
		{
			current->model->toggleMipmaps();
			return;
		}
		current=current->next;
	}
	while(current != NULL);
	return;
}

void Scene::moveLight(long lightID, Vector<float> pos)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			lcurrent->pos.x=pos.x;
			lcurrent->pos.y=pos.y;
			lcurrent->pos.z=pos.z;
			lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}

void Scene::moveLight(long lightID, float x, float y, float z)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			lcurrent->pos.x=x;
			lcurrent->pos.y=y;
			lcurrent->pos.z=z;
			lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
} 
  
void Scene::moveLight(long lightID, char axis, float amount)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			switch(axis){
				case 'x':
				case 'X':
					lcurrent->pos.x = amount;
					lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
					break;
				case 'y':
				case 'Y':
					lcurrent->pos.y = amount;
					lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
					break;
				case 'z':
				case 'Z':
					lcurrent->pos.z = amount;
					lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
					break;
				default:
					break;
				}
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}    

void Scene::moveLightInc(long lightID, float xIncriment, float yIncriment, float zIncriment)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			lcurrent->pos.x+=xIncriment;
			lcurrent->pos.y+=yIncriment;
			lcurrent->pos.z+=zIncriment;
			lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}

void Scene::moveLightInc(long lightID, char axis, float incriment)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			switch(axis){
				case 'x':
				case 'X':
					lcurrent->pos.x += incriment;
					lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
					break;
				case 'y':
				case 'Y':
					lcurrent->pos.y += incriment;
					lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
					break;
				case 'z':
				case 'Z':
					lcurrent->pos.z += incriment;
					lcurrent->light->move(lcurrent->pos.x,lcurrent->pos.y,lcurrent->pos.z,1.0f);
					break;
				default:
					break;
				}
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}

void Scene::rotateLight(long lightID, Vector<float> rot)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			lcurrent->rot.x=rot.x;
			lcurrent->rot.y=rot.y;
			lcurrent->rot.z=rot.z;
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}

void Scene::rotateLight(long lightID, float aboutX, float aboutY, float aboutZ)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			lcurrent->rot.x=aboutX;
			lcurrent->rot.y=aboutY;
			lcurrent->rot.z=aboutZ;
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
} 
  
void Scene::rotateLight(long lightID, char axis, float theta)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			switch(axis){
				case 'x':
				case 'X':
					lcurrent->rot.x = theta;
					break;
				case 'y':
				case 'Y':
					lcurrent->rot.y = theta;
					break;
				case 'z':
				case 'Z':
					lcurrent->rot.z = theta;
					break;
				default:
					break;
				}
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}    

void Scene::rotateLightInc(long lightID, float xIncriment, float yIncriment, float zIncriment)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
		return;
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			lcurrent->rot.x+=xIncriment;
			lcurrent->rot.y+=yIncriment;
			lcurrent->rot.z+=zIncriment;
			
			if(lcurrent->rot.x < 0)
				lcurrent->rot.x+=360;
			if(lcurrent->rot.x > 360)
				lcurrent->rot.x-=360;
				
			
			if(lcurrent->rot.y < 0)
				lcurrent->rot.y+=360;
			if(lcurrent->rot.y > 360)
				lcurrent->rot.y-=360;
				
			
			if(lcurrent->rot.z < 0)
				lcurrent->rot.z+=360;
			if(lcurrent->rot.z > 360)
				lcurrent->rot.z-=360;
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}

void Scene::rotateLightInc(long lightID, char axis, float incrimentTheta)
{
	//check for valid lightID
	if(lightID<0||lightID>=lcount)
	{
		return;
	}
	if(lroot == NULL)
		return;
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			switch(axis){
				case 'x':
				case 'X':
					lcurrent->rot.x += incrimentTheta;
					if(lcurrent->rot.x < 0)
						lcurrent->rot.x+=360;
					if(lcurrent->rot.x > 360)
						lcurrent->rot.x-=360;
					break;
				case 'y':
				case 'Y':
					lcurrent->rot.y += incrimentTheta;
					if(lcurrent->rot.y < 0)
						lcurrent->rot.y+=360;
					if(lcurrent->rot.y > 360)
						lcurrent->rot.y-=360;
					break;
				case 'z':
				case 'Z':
					lcurrent->rot.z += incrimentTheta;
					if(lcurrent->rot.z < 0)
						lcurrent->rot.z+=360;
					if(lcurrent->rot.z > 360)
						lcurrent->rot.z-=360;
					break;
				default:
					break;
				}
			return;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	return;
}

Vector<float> Scene::getLightPos(long lightID)
{
		//check for valid lightID
	if(lightID<0||lightID>=lcount)
	{
		Vector<float> temp;
		return temp;
	}
	if(lroot == NULL)
	{
		Vector<float> temp;
		return temp;
	}
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			return lcurrent->pos;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	Vector<float> temp;
	return temp;
}

Vector<float> Scene::getLightRot(long lightID)
{
		//check for valid lightID
	if(lightID<0||lightID>=lcount)
	{
		Vector<float> temp;
		return temp;
	}
	if(lroot == NULL)
	{
		Vector<float> temp;
		return temp;
	}
	lcurrent=lroot;	

	do{
		if(lcurrent->ID == lightID)
		{
			return lcurrent->rot;
		}
		lcurrent=lcurrent->next;
	}
	while(lcurrent != NULL);
	Vector<float> temp;
	return temp;
}

void Scene::empty()
{
	MNode* mtemp;
	LNode* ltemp;
	
	worldPos.x=worldPos.y=worldPos.z=0;
	worldRot.x=worldRot.y=worldRot.z=0;
	if(root==0)
	{	
		count=0;
		return;
	}
	
	current = root;
	while(current != 0)
	  {
	  	if(current->model)
		  	delete current->model;
		if(current->mat)
		  	delete current->mat;
	    mtemp = current;
	    root = current = current->next;
	    delete mtemp;
	  }
	  count=0;
	  root=current=0;
	  
	  if(lroot==0)
	  {
	  	lcount=0;
		return;
	}
	
	lcurrent = lroot;
	while(lcurrent != 0)
	  {
	  	lcurrent->pos.x=lcurrent->pos.y=lcurrent->pos.z=0;
	  	lcurrent->rot.x=lcurrent->rot.y=lcurrent->rot.z=0;
	    
	    delete lcurrent->light;
	    ltemp = lcurrent;
	    lroot = lcurrent = lcurrent->next;
	    delete ltemp;
	  }
	  lcount=0;
	 lroot=lcurrent=0;
}

bool Scene::exists(long modelID)
{
	MNode* temp;
	if(modelID<0)
	{
		std::clog<<"ID less then 0"<<std::endl;
		return false;
	}
	if(root == 0)
	{
		std::clog<<"No models loaded"<<std::endl;
		return false;
	}
	
	temp = root;	

	do{
		if(temp->ID == modelID)
		{
			//std::clog<<modelID<<" ID exists"<<std::endl;
			return true;
		}
		temp=temp->next;
	}
	while(temp != 0);
	
	//std::clog<<"ID doesn't exist"<<std::endl;
	return false;
}

void Scene::soundOff()
{
	if(root==0)
	{
		std::clog<<"EMPTY"<<std::endl;
		return;
	}
	current = root;
	while(current != 0)
	  {
	  	std::clog<<"Model ID: "<<current->ID<<"  Name: "<<current->model->getName()<<std::endl;
	  	current = current->next;
	  }
	  lcurrent = lroot;
	while(lcurrent != 0)
	  {
	  	std::clog<<"Light ID: "<<lcurrent->ID<<" Pos:("<<lcurrent->pos.x<<" , "<<lcurrent->pos.y<<" , "<<lcurrent->pos.z<<")"<<std::endl;
	  	lcurrent = lcurrent->next;
	  }
}


void Scene::moveCamera(Vector<float> pos)
{
	worldPos.x = pos.x;
	worldPos.y = pos.y;
	worldPos.z = pos.z;
	
	return;
}

void Scene::moveCamera(float x, float y, float z)
{
	worldPos.x = x;
	worldPos.y = y;
	worldPos.z = z;	
	return;
} 
  
void Scene::moveCamera(char axis, float amount)
{
	switch(axis)
	{
		case 'x':
		case 'X':
			worldPos.x = amount;
			break;
		case 'y':
		case 'Y':
			worldPos.y = amount;
			break;
		case 'z':
		case 'Z':
			worldPos.z = amount;
			break;
		default:
			break;
	}
	return;
}    

void Scene::moveCameraInc(float xIncriment, float yIncriment, float zIncriment)
{
	worldPos.x+=xIncriment;
	worldPos.y+=yIncriment;
	worldPos.z+=zIncriment;
	return;
}

void Scene::moveCameraInc(char axis, float incriment)
{
	switch(axis){
		case 'x':
		case 'X':
			worldPos.x += incriment;
			break;
		case 'y':
		case 'Y':
			worldPos.y += incriment;
			break;
		case 'z':
		case 'Z':
			worldPos.z += incriment;
			break;
		default:
			break;
		}
	return;
}

void Scene::rotateCamera(Vector<float> rot)
{
	worldRot.x=rot.x;
	worldRot.y=rot.y;
	worldRot.z=rot.z;
	return;
}

void Scene::rotateCamera(float aboutX, float aboutY, float aboutZ)
{
	worldRot.x=aboutX;
	worldRot.y=aboutY;
	worldRot.z=aboutZ;
	return;
} 
  
void Scene::rotateCamera(char axis, float theta)
{
	switch(axis){
		case 'x':
		case 'X':
			worldRot.x = theta;
			break;
		case 'y':
		case 'Y':
			worldRot.y = theta;
			break;
		case 'z':
		case 'Z':
			worldRot.z = theta;
			break;
		default:
			break;
		}
	return;
}    

void Scene::rotateCameraInc(float xIncriment, float yIncriment, float zIncriment)
{
	worldRot.x+=xIncriment;
	worldRot.y+=yIncriment;
	worldRot.z+=zIncriment;
	
	if(worldRot.x < 0)
		worldRot.x+=360;
	if(worldRot.y < 0)
		worldRot.y+=360;
	if(worldRot.z < 0)
		worldRot.z+=360;
	if(worldRot.x > 360)
		worldRot.x-=360;
	if(worldRot.y > 360)
		worldRot.y-=360;
	if(worldRot.z > 360)
		worldRot.z-=360;
	
	return;
}

void Scene::rotateCameraInc(char axis, float incrimentTheta)
{
	switch(axis){
		case 'x':
		case 'X':
			worldRot.x += incrimentTheta;
			if(worldRot.x < 0)
				worldRot.x+=360;
			if(worldRot.x > 360)
				worldRot.x-=360;
			break;
		case 'y':
		case 'Y':
			worldRot.y += incrimentTheta;
			if(worldRot.y < 0)
				worldRot.y+=360;
			if(worldRot.y > 360)
				worldRot.y-=360;
			break;
		case 'z':
		case 'Z':
			worldRot.z += incrimentTheta;
			if(worldRot.z < 0)
				worldRot.z+=360;
			if(worldRot.z > 360)
				worldRot.z-=360;
			break;
		default:
			break;
		}
	return;
}

Vector<float> Scene::getCameraPos()
{
	return worldPos;
}

Vector<float> Scene::getCameraRot()
{
	return worldRot;
}

void Scene::MouseMotion(int x, int y)
{	
	//std::clog<<"IN MOUSE MOTION"<<std::endl;	
	float tempX = (((float)x-(float)mouseX)*MOUSEXSENS);
	float tempY = (((float)y-(float)mouseY)*MOUSEYSENS);
	
	if(map[MIDDLE_MOUSE])
	{
		if(!map[ALT_KEY]&&!map[CTRL_KEY])
		{
			if(map[SHIFT_KEY])
				rotateCameraInc(tempY,-tempX, 0.0f);
			else
				moveCameraInc(tempX,tempY, 0.0f);
		}
		
		glutPostRedisplay();
	}
	
	mouseX = x;
	mouseY = y;
}

void Scene::PassMouseMotion(int x, int y)
{
	static bool trip = false;
	float tempY = (((float)y-(float)mouseY)*MOUSEYSENS);
	
	if(map[KEY_MODEL_MOVE_X])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		moveModelInc(toggle, 'x', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_MOVE_Y])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		moveModelInc(toggle, 'y', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_MOVE_Z])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		moveModelInc(toggle, 'z', -tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_ROTATE_X])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		rotateModelInc(toggle, 'x', -tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_ROTATE_Y])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		rotateModelInc(toggle, 'y', tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_ROTATE_Z])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		rotateModelInc(toggle, 'z', tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_SCALE])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		scaleModelInc(toggle, tempY, tempY, tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_SCALE_X])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		scaleModelInc(toggle, 'x', tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_SCALE_Y])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		scaleModelInc(toggle, 'y', tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_MODEL_SCALE_Z])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		scaleModelInc(toggle, 'z', tempY);
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_LIGHT_MOVE_X])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		moveLightInc(lightToggle, 'x', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_LIGHT_MOVE_Y])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		moveLightInc(lightToggle, 'y', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_LIGHT_MOVE_Z])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		moveLightInc(lightToggle, 'z', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_LIGHT_ROTATE_X])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		rotateLightInc(lightToggle, 'x', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_LIGHT_ROTATE_Y])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		rotateLightInc(lightToggle, 'y', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else if(map[KEY_LIGHT_ROTATE_Z])
	{
		if(!trip)
		{
			mouseX = x;
			mouseY = y;
			trip = true;
		}
		rotateLightInc(lightToggle, 'z', tempY);	
		glutWarpPointer(mouseX,mouseY);
	}
	else
	{
		mouseX = x;
		mouseY = y;
		trip = false;
	}
}

void Scene::addShader(glslProgram* shader)
{
	std::clog<<"Adding shader: "<<shader->getName()<<"\n";
	shaders.push_back(shader);
}

void Scene::deleteShader()
{
	if(currentShaderID != 0)
	{
		std::clog<<"Deleting Shader #"<<currentShaderID<<": "<<shaders[currentShaderID-1]->getName()<<"\n";
		shaders.erase(shaders.begin()+currentShaderID-1);
		if(shaders.size()+1<=currentShaderID)
			currentShaderID=0;
	}
}

#endif
