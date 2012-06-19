#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	long get();
	void mark();
	long delta();//in milliseconds
	long deltaMark();//in milliseconds
	void reset();
	void stop();
	bool isRunning(){return running;};
protected:
	bool running;
        std::chrono::time_point<std::chrono::system_clock> startMark;
        std::chrono::time_point<std::chrono::system_clock> tempMark;
};

Timer::Timer()
{
  //startMark = tempMark = 0;//doesn't work this way with chrono
	running = false;
}

Timer::~Timer()
{
}

void Timer::start()
{
  startMark = std::chrono::system_clock::now();
  tempMark = std::chrono::system_clock::now();
	running = true;
}

long Timer::get()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Timer::mark()
{
	tempMark = std::chrono::system_clock::now();
}

long Timer::delta()
{
  auto duration =  std::chrono::system_clock::now() - startMark;
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

long Timer::deltaMark()
{
  auto duration =  std::chrono::system_clock::now() - tempMark;
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}	

void Timer::reset()
{
	startMark = tempMark = std::chrono::system_clock::now();
}

void Timer::stop()
{
  //startMark = tempMark = 0;//see above
	running = false;
}

#endif
