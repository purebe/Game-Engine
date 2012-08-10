// GameEngine_Font.h
//
// Author: John Conder
// Date: 06/22/2012
//
// Purpose:
// Provides a basic font engine for displaying textual data.

#pragma once

#include "GameEngine_Rect.h"
#include "GameEngine_Draw.h"
#include "GameEngine_Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>

namespace GE
{
	struct FontLine
	{
		std::string text;
		float liveTime;
		double startTime;

		bool deleteFlag;
	};
}

class GameEngine_Font
{
private:
	TTF_Font* currentFont;
	SDL_Color currentColor;

	GameEngine_Timer timer;

	GE::Rect printRegion;
	std::vector<GE::FontLine> printStrings;

public:
	GameEngine_Font(TTF_Font* font, SDL_Color const& color);
	GameEngine_Font(TTF_Font* font);
	GameEngine_Font();

	void Print(std::string const& text, float const& time=5000.0f);
	void DrawStrings(SDL_Surface* screen);
	void Update();

	void SetFont(TTF_Font* font);
	void SetColor(SDL_Color const& color);
};