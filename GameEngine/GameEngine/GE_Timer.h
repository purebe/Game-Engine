// GE_Timer.h
//
// Author: John Conder
// Date: 07/03/2012
//
// Purpose:
// Provides a high resolution timer class.

#pragma once

#include <Windows.h>

#include <iostream>

// CROSS_PLATFORM: Provide other OS implementations
class GE_Timer
{
private:
	LARGE_INTEGER start;
	LARGE_INTEGER stop;

	double frequency;
	bool ready;

public:
	GE_Timer();

	void Start();
	void Stop();
	double GetTimeElapsed();

	bool GetState();
};