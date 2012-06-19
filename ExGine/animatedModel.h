#ifndef __ANIMATEDMODEL_H__
#define __ANIMATEDMODEL_H__

#include "model.h"
#include "timer.h"

/*************************************
 * 
 * transforms....
 * 
 * ***********************************/

class AModel:public Model
{
public:
	AModel(){};
	AModel(mFile* myM):Model(myM){};
	~AModel(){};
	void draw();
protected:
	bool update();
	
	Timer animationTimer;
};

void AModel::draw()
{
	if(!update())
		return;
	Model::draw();
}

bool AModel::update()
{
	return true;
}

#endif
