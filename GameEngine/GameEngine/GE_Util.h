// GE_Util.h
//
// Author: John Conder
// Date: 06/22/2012
//
// Purpose:
// Utility functions.

#pragma once

#include "GE_Rect.h"

#include <SDL.h>

SDL_Rect GEToSDLRect(GE::Rect const& geRect);
GE::Rect SDLToGERect(SDL_Rect const& sdlRect);