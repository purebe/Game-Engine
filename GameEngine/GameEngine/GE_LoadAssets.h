// GE_LoadAssets.h
//
// Author: John Conder
// Date: 05/11/2012
//
// Purpose:
// This header contains functions for loading assets into the game
// engine.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace GE
{
	//
	// Loads, optimizes, and color keys an image from given path.
	// Special thanks to: Lazy Foo (code and comment almost
	// copy/pasted) Any image loaded with LoadImage() must be freed
	// with SDL_FreeSurface() when done.
	//
	SDL_Surface* LoadAssetImg(std::string const& filename);
}