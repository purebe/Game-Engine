// GE_Draw.cpp
//
// Author: John Conder
// Date: 05/10/2012
//
// Purpose:
// The implementation of the functions for GE_Draw.h

#include "GE_Draw.h"

//
// Draws an image to the position specified in dstRect (width and
// height ignored), from the rectangle specified in srcRect (entire
// rectangle considered).
//
int GE::BlitImage(SDL_Surface* srcSurface, SDL_Rect& srcRect, SDL_Surface* dstSurface, SDL_Rect& dstRect)
{
	return SDL_BlitSurface(srcSurface, &srcRect, dstSurface, &dstRect);
}