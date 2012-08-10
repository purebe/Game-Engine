// GE_FPS.cpp
//
// Author: John Conder
// Date: 07/04/2012
//
// Purpose:
// The implementation of GE_FPS in GE_Metrics.h

#include "GE_Metrics.h"

GE_FPS::GE_FPS() : frameCount(0), fps(0), ready(false)
{
}

void GE_FPS::Start()
{
	fpsTimer.Start();
	ready = true;
}

void GE_FPS::Stop()
{
	// We don't need to call fpsTimer.Stop() because ready can only be true
	// after a call to Start() again
	ready = false;
}

void GE_FPS::Update()
{
	if ( !ready )
	{
		return;
	}

	++frameCount;
	if ( frameCount == 100 )
	{
		double timePerFrame = fpsTimer.GetTimeElapsed() / 100;
		fps = (1 / timePerFrame) * 1000;

		fpsTimer.Start();
		frameCount = 0;
	}
}

double GE_FPS::GetFPS()
{
	return fps;
}