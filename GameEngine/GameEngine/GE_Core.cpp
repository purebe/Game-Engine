// GE_Core.cpp
//
// Author: John Conder
// Date: 05/09/2012
//
// Purpose:
// The implementation of the functions for GE_Core.h

#include "GE_Core.h"

//
// Initialize our constant variables
//
GE_Core::GE_Core() : TICKS_PER_SECOND(60), SKIP_TICKS(1000/TICKS_PER_SECOND), MAX_FRAMESKIP(15)
{
}

//
// Should free up any allocated resources here
//
GE_Core::~GE_Core()
{
	TTF_Quit();
	SDL_Quit();
}

//
// Handles the main game loop
//
void GE_Core::Run()
{
	// Dewitter's game loop
	Uint32 nextGameTick = SDL_GetTicks();
	int loops;
	float interpolation;

	Initialize();
	Load();

	while( gameRunning )
	{
		loops = 0;
		while( SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			BaseUpdate();
			Update();

			nextGameTick += SKIP_TICKS;

			loops++;
		}

		MetricUpdate();

		interpolation = float( SDL_GetTicks() + SKIP_TICKS - nextGameTick )
						/ float( SKIP_TICKS );

		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

		Draw(interpolation);

		SDL_Flip(screen);
	}

	Unload();
}

//
// Handles basic initialization before the game loop begins
//
void GE_Core::Initialize()
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		std::cerr << "Error calling SDL_Init().\n";
	}
	
	if ( TTF_Init() == -1 )
	{
		std::cerr << "Error calling TTF_Init().\n";
	}

	screen = 0;
	screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if ( screen == nullptr )
	{
		std::cerr << "Error calling SDL_SetVideoMode()...return value of nullptr.\n";
	}

	SDL_WM_SetCaption(windowTitle.c_str(), 0);

	gameRunning = true;
}

//
// Handles mundane update information such as handling basic window related events
// It's expected this will be overriden by the child class
//
void GE_Core::BaseUpdate()
{
	while( SDL_PollEvent( &curEvent ) )
	{
		if( curEvent.type == SDL_QUIT )
		{
			gameRunning = false;
		}
	}
}

//
// MetricUpdate() is basically a non-locked logic update function.  You can
// use it to calculate the display FPS for example, but DO NOT use it for
// in-game logic stuff, as, that is rate-locked for a reason.
//
void GE_Core::MetricUpdate()
{
}