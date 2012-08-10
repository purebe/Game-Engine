// GE_Draw.h
//
// Author: John Conder
// Date: 05/10/2012
//
// Purpose:
// This header contains functions for drawing in the game engine.

#pragma once

#include <SDL.h>

#include "GE_Core.h"

namespace GE
{
	//
	// Draws an image to the position specified in dstRect (width and
	// height ignored), from the rectangle specified in srcRect 
	// (entire rectangle considered).
	//
	int BlitImage(SDL_Surface* srcSurface, SDL_Rect& srcRect, SDL_Surface* dstSurface, SDL_Rect& dstRect);
}