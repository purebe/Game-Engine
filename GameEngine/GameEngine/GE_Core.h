// GE_Core.h
//
// Author: John Conder
// Date: 05/09/2012
//
// Purpose:
// This class maintains the game loop and basic core game variable
// information.

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class GE_Core
{
private:
	const int TICKS_PER_SECOND;
	const int SKIP_TICKS;
	const int MAX_FRAMESKIP;

protected:
	bool gameRunning;

	SDL_Event curEvent;
	
	Uint32 screenWidth;
	Uint32 screenHeight;

	std::string windowTitle;

	SDL_Surface* screen;

public:
	GE_Core();
	~GE_Core();

	void Run();
	void Initialize();

	virtual void BaseUpdate();
	virtual void MetricUpdate();

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Draw(float interpolation) = 0;
	virtual void Update() = 0;
};