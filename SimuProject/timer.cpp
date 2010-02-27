#include "timer.h"

#include <sstream>

Timer::Timer() : 
	timeTaken( 0.0 )
{

}

Timer::~Timer()
{
}

void Timer::Start()
{
	DWORD oldAff = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&startTime);
	SetThreadAffinityMask(GetCurrentThread(), oldAff);
}

void Timer::Stop()
{
	LARGE_INTEGER endTime;
	LARGE_INTEGER freq;

	DWORD oldAff = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&endTime);
	QueryPerformanceFrequency(&freq);
	SetThreadAffinityMask(GetCurrentThread(), oldAff);
	timeTaken = (double)(endTime.QuadPart-startTime.QuadPart)/freq.QuadPart;
}

double Timer::GetTime()
{
	return timeTaken;
}