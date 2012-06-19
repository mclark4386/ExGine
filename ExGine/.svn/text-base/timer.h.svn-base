#ifndef __TIMER_H__
#define __TIMER_H__

#include "exogl.h"

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	int get();
	void mark();
	int delta();
	int deltaMark();
	void reset();
	void stop();
	bool isRunning(){return running;};
protected:
	bool running;
	int startMark;
	int tempMark;
};

Timer::Timer()
{
	startMark = tempMark = 0;
	running = false;
}

Timer::~Timer()
{
}

void Timer::start()
{
	startMark = tempMark = glutGet(GLUT_ELAPSED_TIME);
	running = true;
}

int Timer::get()
{
	return glutGet(GLUT_ELAPSED_TIME);
}

void Timer::mark()
{
	tempMark = glutGet(GLUT_ELAPSED_TIME);
}

int Timer::delta()
{
	return glutGet(GLUT_ELAPSED_TIME) - startMark;
}

int Timer::deltaMark()
{
	return glutGet(GLUT_ELAPSED_TIME) - tempMark;
}	

void Timer::reset()
{
	startMark = tempMark = glutGet(GLUT_ELAPSED_TIME);
}

void Timer::stop()
{
	startMark = tempMark = 0;
	running = false;
}

#endif
