// GE_Metrics.h
//
// Author: John Conder
// Date: 07/04/2012
//
// Purpose:
// Provides implementations of various metrics for use within the GE.

#pragma once

#include "GE_Timer.h"

class GE_FPS
{
private:
	GE_Timer fpsTimer;
	int frameCount;

	double fps;
	bool ready;

public:
	GE_FPS();

	void Start();
	void Stop();
	void Update();

	double GetFPS();
};