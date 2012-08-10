// GE_LoadAssets.cpp
//
// Author: John Conder
// Date: 05/11/2012
//
// Purpose:
// The implementation of the functions for GE_LoadAssets.h

#include "GE_LoadAssets.h"

//
// Loads, optimizes, and color keys an image from given path.
// Special thanks to: Lazy Foo (code and comment almost copy/pasted)
// Any image loaded with LoadImage() must be free'd with
// SDL_FreeSurface() when done.
//
SDL_Surface* GE::LoadAssetImg(std::string const& filename)
{
	SDL_Surface* loadedImage = 0;
	SDL_Surface* optimizedImage = 0;
		
	loadedImage = IMG_Load(filename.c_str());

	if ( loadedImage != 0 )
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if ( optimizedImage != 0 )
		{
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF));
		}
	}

	return optimizedImage;
}