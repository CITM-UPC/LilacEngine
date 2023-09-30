#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "vcpkg/packages/sdl2_x64-windows/include/SDL2/SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();

	Uint32 Read();

private:

	bool	running;
	Uint32	started_at;
	Uint32	stopped_at;
};

#endif //__TIMER_H__