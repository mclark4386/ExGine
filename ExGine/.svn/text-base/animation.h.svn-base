#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "timer.h"
#include "afile.h"

class Animation
{
public:
	Animation(){fps=0.0f;frameCount=0;boneCount=0;running=false;looping=false;frames=0;mark=0;};
	Animation(const char* filename);
	Animation(aFile* myA);
	~Animation();
	GLfloat* getCurrentFrames();
	float getCurrentDelta();
	int getBoneCount(){return boneCount;};
	void start();
	void reset();
	void stop();
	bool isRunning(){return running;};
protected:
	string filename;
	bool looping;
	bool running;
	float fps;
	int frameCount;
	int boneCount;
	GLfloat* frames;
	float mark;//will store the time delta at the time of getting the current frames
	Timer timer;
};

Animation::Animation(const char* _filename)
{
	aFile* myA = new aFile(_filename);
	
	if(myA->isError())
	{
		std::clog<<"Too Many Bones in file"<<std::endl;
		running = false;
		mark = 0;
		frames =0;
		frameCount = 0;
		boneCount = 0;
		fps = 0.0;
		looping = false;
		return;
	}
	
	filename = _filename;
	
	looping = myA->isLooping();
	frameCount = myA->getFrameCount();
	boneCount = myA->getBoneCount();
	fps = myA->getFramesPerSecond();
	
	frames = myA->getFrames();
	
	running = false;
	mark = 0;
}

Animation::Animation(aFile* myA)
{	
	filename = myA->getFilename();
	
	looping = myA->isLooping();
	frameCount = myA->getFrameCount();
	boneCount = myA->getBoneCount();
	fps = myA->getFramesPerSecond();
	
	frames = myA->getFrames();
	
	running = false;
	mark = 0;
}

Animation::~Animation()
{
	delete [] frames;
}

void Animation::start()
{
	std::clog<<"Starting "<<filename.c_str()<<" animation."<<std::endl;
	timer.start();
	running = true;
}

void Animation::reset()
{
	timer.reset();
	mark = 0;
}

void Animation::stop()
{
	timer.stop();
	mark = 0;
	running = false;
}

GLfloat* Animation::getCurrentFrames()
{
	if(!running)
	{
		//std::clog<<"Not running"<<std::endl;
		return frames;//initial pose
	}
		
	float time = timer.delta() * 1000;//time in seconds
	
	mark = time * fps;//number of frames that have passed sine the beginning of animation
	
	if(!looping&&mark>frameCount)
	{
		stop();
		return frames;//initial pose
	}
	
	while(mark > frameCount)
		mark -= frameCount;
		
	//mark is now at the init frame + delta to final frame... 
	int currentFrame = (int)mark;
	mark -= currentFrame;
	
	//std::clog<<"Getting frame:"<<currentFrame<<" mark:"<<mark<<std::endl;
	
	return frames+(currentFrame*boneCount*8);
}

float Animation::getCurrentDelta()
{
	if(!running)
		return 0;
		
	return mark;
}

#endif
