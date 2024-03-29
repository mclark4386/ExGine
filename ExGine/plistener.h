#ifndef __PLISTENER_H__
#define __PLISTENER_H__

#include "scene.h"
#include "pobject.h"
#include <list>
#include <iostream>
#include <algorithm>

/*
 * This will be where the octree will be and this is where the moves will be as well
 */

struct modInfo
      {
           long modID;         ///<model ID
           PObject* pObj;      ///<pobject pointer
      };

typedef std::list<modInfo>::iterator modInt;///< model information list interator

class PListener
{
public:
       PListener(){errorFlag = false;};
       ~PListener(){};
       void init();
       void update();
       void addModel(long ID, PObject* bounds){modInfo temp; temp.modID=ID; temp.pObj=bounds;li.push_back(temp);};
       void setScene(Scene* scene){actscene=scene;};
       void moveModel(long modelID, Vector<Scalar> vel){modInt temp = getModel(modelID); if(temp!=modInt(NULL))temp->pObj->setVelocity(vel);};
       void moveModelInc(long modelID, char axis, Scalar force);
       void moveModel(long modelID, char axis, Scalar force);
       void handleKeys(unsigned char key, int x, int y);
       void handleSKeys(int key, int x, int y);
       bool isError(){bool temp = errorFlag; errorFlag = false; return temp;};
       bool compareID(long i, modInfo j){ return (i == j.modID);};
       
protected:          
		modInt getModel(long _modID);
          
          std::list<modInfo> li;		///<list of all our models
          Scene* actscene;           ///<active scene pointer
          bool errorFlag;
};

void PListener::init()
{
	
}

void PListener::update()
{
	modInt i = li.begin();
	modInt j;
	Vector<Scalar> reversal(0,1,0);
	Vector<Scalar> tempPoM;
	Scalar dist;
	bool hit = true;
	
	for(i = li.begin();i != li.end();i++)
	{
		for(j=i;j!=li.end();j++)
		{
			if(j==i)continue;
			dist = i->pObj->detectCollision(j->pObj);
			if (dist>0.0001)
			{
				j->pObj->update();
				actscene->moveModel(j->modID,j->pObj->getPoM());
				hit = false;
			}
			if (dist<=0.0001&&dist>=-0.0001)
			{
				//std::clog<<"dead even"<<std::endl;
				j->pObj->runVelocity();
				actscene->moveModel(j->modID,j->pObj->getPoM());
				hit = true;
			}
			if (dist<-0.0001)
			{
				hit = true;
				tempPoM = j->pObj->getPoM() - (reversal * dist);
				//std::clog<<"neg hit"<<tempPoM.x<<", "<<tempPoM.y<<", "<<tempPoM.z<<std::endl;
				j->pObj->setPoM(tempPoM);
				j->pObj->runVelocity();
				actscene->moveModel(j->modID,j->pObj->getPoM());
			}
			//std::clog<<"Checking collision between "<<i->modID<<" and "<<j->modID<<" dist:"<<dist<<" hit:"<<hit<<
			//	"\n\t"<<i->pObj->getPoM().x<<", "<<i->pObj->getPoM().y<<", "<<i->pObj->getPoM().z<<"    "<<j->pObj->getPoM().x<<", "<<j->pObj->getPoM().y<<", "<<j->pObj->getPoM().z<<std::endl;
		}
		if (!hit)
		{
			//std::clog<<"updating: "<<i->modID<<" at: "<<i->pObj->getPoM().x<<", "<<i->pObj->getPoM().y<<", "<<i->pObj->getPoM().z<<std::endl;
			i->pObj->update();
			//std::clog<<"updating: "<<j->modID<<" at: "<<j->pObj->getPoM().x<<", "<<j->pObj->getPoM().y<<", "<<j->pObj->getPoM().z<<std::endl;
			//j->pObj->update();
		}
		else
		{
			i->pObj->runVelocity();
			//j->pObj->runVelocity();
		}
			
		actscene->moveModel(i->modID,i->pObj->getPoM());
			
		//if(++i == li.end())
		//{
			//std::clog<<"last updating: "<<i->modID<<" at: "<<i->pObj->getPoM().x<<", "<<i->pObj->getPoM().y<<", "<<i->pObj->getPoM().z<<std::endl;
			//if(!hit)
				//i->pObj->update();
			//else
				//i->pObj->runVelocity();
			//actscene->moveModel(i->modID,i->pObj->getPoM());
		//}
			
		hit = true;
	}
	
	
}

void PListener::moveModel(long modelID, char axis, Scalar force)
{
	modInt model = li.end();//search(li.begin(),li.end(),modelID,compareID);
	Vector<Scalar> temp;
	//if(model == li.end()&&isError())
	//	return;
	
	if(model == li.end())
	{
		//for testing: NEED TO FIX!
		model = li.begin();
		model++;
	}
	switch(axis){
				case 'x':
				case 'X':
					temp.x = force;
					temp.y = 0.0;
					temp.z = 0.0;
					model->pObj->setVelocity(temp);
					break;
				case 'y':
				case 'Y':
					temp.x = 0.0;
					temp.y = force;
					temp.z = 0.0;
					model->pObj->setVelocity(temp);
					break;
				case 'z':
				case 'Z':
					temp.x = 0.0;
					temp.y = 0.0;
					temp.z = force;
					model->pObj->setVelocity(temp);
					break;
				default:
					break;
				}
	//std::clog<<"mod: "<<modelID<<" axis "<<axis<<" force "<<force<<": "<<temp.x<<", "<<temp.y<<", "<<temp.z<<std::endl;
}

void PListener::handleKeys(unsigned char key, int x, int y)
{
	long toggle = actscene->getCurrentModel();
	//std::clog<<"key: "<<key<<" ID: "<<toggle<<" x "<<x<<" y "<<y<<std::endl;
	switch(key)
	{
		case 'z':
		case 'Z':
			moveModel(toggle,'y',-10.0);
			break;
				
		case 'x':
		case 'X':
			moveModel(toggle,'y',10.0);
			break;		
	}
}

void PListener::handleSKeys(int key, int x, int y)
{
	long toggle = actscene->getCurrentModel();
	//std::clog<<"skey: "<<key<<" ID: "<<toggle<<" x "<<x<<" y "<<y<<std::endl;
	switch(key)
	{	
		case GLUT_KEY_UP:
			moveModel(toggle,'z',-10.0);
			break;
			
		case GLUT_KEY_DOWN:
			moveModel(toggle,'z',10.0);
			break;
		
		case GLUT_KEY_LEFT:
			moveModel(toggle,'x',-10.0);
			break;
			
		case GLUT_KEY_RIGHT:
			moveModel(toggle,'x',10.0);
			break;	
	}
}

modInt PListener::getModel(long _modID)
{
	modInt i;
	for(i = li.begin();i != li.end();i++);
		if(i->modID == _modID)
			return i;
	errorFlag = true;
	return li.end();
}

#endif
