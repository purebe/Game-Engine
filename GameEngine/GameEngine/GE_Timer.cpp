// GE_Timer.cpp
//
// Author: John Conder
// Date: 07/03/2012
//
// Purpose:
// The implementation of the functions for GE_Timer.h

#include "GE_Timer.h"

//
// Constructor to initialize the boolean ready to false.
//
GE_Timer::GE_Timer() : ready(false)
{
}

//
// Selects a starting point for the timer.
// Subsequent calls to Start() simply "Restart" the timer.
// NOTE: You _must_ call Start() at least once before you call
// GetTimeElapsed(), otherwise, you will always get the value '-1.0'
// as you cannot have elapsed time if the timer has never been started.
//
void GE_Timer::Start()
{
	LARGE_INTEGER procFreq;
	DWORD_PTR originalMask;

	if ( !QueryPerformanceFrequency(&procFreq) )
	{
		std::cerr << "Call to QueryPerformanceFrequency failed!\n";
		return ;
	}

	frequency = (double)procFreq.QuadPart;

	originalMask = SetThreadAffinityMask(GetCurrentThread(), 0);
	if ( !QueryPerformanceCounter(&start) )
	{
		std::cerr << "Call to QueryPerformanceCounter failed!\n";
	}

	// Always set the thread affinity back to the original when done.
	SetThreadAffinityMask(GetCurrentThread(), originalMask);

	ready = true;
}

//
// Returns the timer to the initial state.
//
void GE_Timer::Stop()
{
	ready = false;
}

//
// Returns the time, in milliseconds, since the last call to Start().
//
double GE_Timer::GetTimeElapsed()
{
	if ( !ready )
	{
		std::cerr << "Call to GetTimeElapsed() without a call to GE_Timer.Start()!\n";
		return -1.0;
	}

	DWORD_PTR originalMask;
	originalMask = SetThreadAffinityMask(GetCurrentThread(), 0);

	// No matter whether the call works or not, we must set the
	// thread affinity mask back to the original when done.
	if ( !QueryPerformanceCounter(&stop) )
	{
		std::cerr << "Call to QueryPerformanceCounter failed!\n";
		SetThreadAffinityMask(GetCurrentThread(), originalMask);
		return -1.0;
	}

	SetThreadAffinityMask(GetCurrentThread(), originalMask);

	return ((stop.QuadPart - start.QuadPart) / frequency) * 1000;
}

//
// Returns the state of the timer.
//
bool GE_Timer::GetState()
{
	return ready;
}