#ifndef _TIMER_H
#define _TIMER_H

#include <string>
#include <windows.h>

class Timer
{
private:
	LARGE_INTEGER startTime;
	double timeTaken;

public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	double GetTime();
};

#endif