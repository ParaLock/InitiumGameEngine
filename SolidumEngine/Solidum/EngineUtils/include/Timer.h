#ifndef HRTIMER
#define HRTIMER

#include <windows.h>
#include <vector>

class HRTimer
{
private:	
	
	LARGE_INTEGER start;
    LARGE_INTEGER stop;
	LARGE_INTEGER frequency;
	LARGE_INTEGER timeElapsed;

public:

	HRTimer() { QueryPerformanceFrequency(&frequency); };
	
	void reset() { QueryPerformanceCounter(&start); }
	void startTimer() { reset(); }

    double getElapsedTimeSeconds()
	{	
		QueryPerformanceCounter( &stop );			
		timeElapsed.QuadPart = stop.QuadPart - start.QuadPart;			
		return (double) timeElapsed.QuadPart / frequency.QuadPart ;		
	}
};

#endif
