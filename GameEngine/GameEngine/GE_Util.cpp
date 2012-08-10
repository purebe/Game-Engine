// GE_Util.cpp
//
// Author: John Conder
// Date: 06/21/2012
//
// Purpose:
// The implementation of the functions for GE_Util.h

#include "GE_Util.h"

//
// Converts a GERect to a SDL_Rect.
//
SDL_Rect GEToSDLRect(GE::Rect const& geRect)
{
	SDL_Rect tmp;

	tmp.x = (Sint16)geRect.x;
	tmp.y = (Sint16)geRect.y;
	tmp.w = (Sint16)geRect.w;
	tmp.h = (Sint16)geRect.h;

	return tmp;
}

//
// Converst a SDL_Rect to a GERect.
//
GE::Rect SDLToGERect(SDL_Rect const& sdlRect)
{
	GE::Rect tmp;

	tmp.x = sdlRect.x;
	tmp.y = sdlRect.y;
	tmp.w = sdlRect.w;
	tmp.h = sdlRect.h;

	return tmp;
}