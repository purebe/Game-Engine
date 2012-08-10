// GE_Text.h
//
// Author: John Conder
// Date: 06/22/2012
//
// Purpose:
// Provides a basic font engine for displaying textual data.

#pragma once

#include "GE_TextStream.h"

#include "GE_Rect.h"
#include "GE_Draw.h"
#include "GE_Timer.h"
#include "GE_Conversion.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>

namespace GE
{
	struct TextPacket
	{
		// REFACTOR Remove std::string text -- regular streams should work using TextStream's, rather than std::string.
		std::string text;
		float liveTime;
		double startTime;

		bool textStreamFlag;
		bool deleteFlag;

		GE_TextStream* textStream;
	};
}

// TODO TextStreams need to have an output rectangle specified
// TODO Keep track of current line when printing multiple lines
// 
class GE_Text
{
private:
	TTF_Font* currentFont;
	SDL_Color currentColor;

	GE_Timer timer;

	GE::Rect printRegion;
	std::vector<GE::TextPacket> printStrings;

	void ParseStrings();

public:
	GE_Text(TTF_Font* font, SDL_Color const& color);
	GE_Text(TTF_Font* font);
	GE_Text();

	void Print(std::string const& text, float time=5000.0f);
	void Print(GE_TextStream& textStream, float time=5000.0f);
	void DrawStrings(SDL_Surface* screen);
	void Update();

	void SetFont(TTF_Font* font);
	void SetColor(SDL_Color const& color);
};