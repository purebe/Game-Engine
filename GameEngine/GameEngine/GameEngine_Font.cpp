// GameEngine_Font.cpp
//
// Author: John Conder
// Date: 07/01/2012
//
// Purpose:
// The implementation of the functions for GameEngine_Font.h

#include "GameEngine_Font.h"

//
// Initialize the required variables with the class.
//
GameEngine_Font::GameEngine_Font(TTF_Font* font, SDL_Color const& const color) : currentFont(font), currentColor(color)
{
}

GameEngine_Font::GameEngine_Font(TTF_Font* font) : currentFont(font)
{
	SDL_Color color = {255, 255, 255};
	currentColor = color;
}

GameEngine_Font::GameEngine_Font() : currentFont(nullptr)
{
	SDL_Color color = {255, 255, 255};
	currentColor = color;
}

//
// Print the text to the screen.
//
void GameEngine_Font::Print(std::string const& text, float const& time)
{
	GE::FontLine tmp;

	tmp.text = text;
	tmp.liveTime = time;
	tmp.startTime = -1.0f;
	tmp.deleteFlag = false;

	printStrings.push_back(tmp);
}

//
// Draw the strings ready to be printed.
//
void GameEngine_Font::DrawStrings(SDL_Surface* screen)
{
	if ( currentFont == nullptr )
	{
		std::cerr << "Attempting to call GameEngine_Font::DrawStrings() without registering a font.\n";
	}
	else
	{
		for ( auto itr = printStrings.begin(); itr != printStrings.end(); ++itr )
		{
			// Check if the timer is running
			if ( !timer.GetState() )
			{
				timer.Start();
			}

			// Check if this is the first time displaying a line
			if ( itr->startTime < 0.0f )
			{
				itr->startTime = timer.GetTimeElapsed();
			}

			// Check if the line has expired
			double delta = timer.GetTimeElapsed() - itr->startTime;
			if ( delta >= itr->liveTime )
			{
				// Flag it for deletion
				itr->deleteFlag = true;
			}

			SDL_Surface* printSurface = TTF_RenderText_Solid(currentFont, itr->text.c_str(), currentColor);
			SDL_Rect rect = {0,0,0,0};

			SDL_BlitSurface(printSurface, nullptr, screen, &rect);
			SDL_FreeSurface(printSurface);
		}
	}
}

//
// Handles deletion.
//
void GameEngine_Font::Update()
{
	// Remove any elements flagged for deletion
	for ( auto itr = printStrings.begin(); itr != printStrings.end(); ++itr )
	{
		if ( itr->deleteFlag )
		{
			itr = printStrings.erase(itr);
			if ( itr == printStrings.end() )
			{
				break;
			}
		}
	}
}

//
// Sets the current font.
// REMARKS: Unloads the currently loaded font, if it exists.
//
void GameEngine_Font::SetFont(TTF_Font* font)
{
	if ( currentFont != nullptr )
	{
		TTF_CloseFont(currentFont);
	}

	currentFont = font;
}

//
// Sets the current color.
//
void GameEngine_Font::SetColor(SDL_Color const& color)
{
	currentColor = color;
}