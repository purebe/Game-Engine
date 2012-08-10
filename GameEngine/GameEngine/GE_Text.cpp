// GE_Text.cpp
//
// Author: John Conder
// Date: 07/01/2012
//
// Purpose:
// The implementation of the functions for GE_Text.h

#include "GE_Text.h"

//
// Parse through formatted strings and update any values.
//
void GE_Text::ParseStrings()
{
	int argCount = 0;
	for ( auto itr = printStrings.begin(); itr != printStrings.end(); ++itr )
	{
		if ( itr->textStream )
		{
			// Create a copy of the string to chop up for rfind() operations
			std::string chopStr = itr->textStream->GetText();

			// Create a copy of the template string in order to replace the values
			std::string tmpStr = itr->textStream->GetText();

			// Parse the string and update it's values
			int pos;
			while ( (pos = chopStr.rfind("|f")) != chopStr.npos )
			{
				// Replace the string in tmpStr
				switch (chopStr.at(pos+2))
				{
				case 'i':
				{
					std::string replaceStr = GE::to_string(*((int*)itr->textStream->GetPtr(argCount++)));
					tmpStr.replace(pos, 3, replaceStr);
					break;
				}
				case 'f':
				{
					std::string replaceStr = GE::to_string(*((float*)itr->textStream->GetPtr(argCount++)));
					tmpStr.replace(pos, 3, replaceStr);
					break;
				}
				case 'd':
				{
					std::string replaceStr = GE::to_string(*((double*)itr->textStream->GetPtr(argCount++)));
					tmpStr.replace(pos, 3, replaceStr);
					break;
				}
				default:
					break;
				}

				// Chop the occurance out of the chopStr
				chopStr.erase(pos, chopStr.npos);
			}

			// Replace the string that will be drawn with the tmp string
			itr->text = tmpStr;
		}
	}
}

//
// Initialize the required variables with the class.
//
GE_Text::GE_Text(TTF_Font* font, SDL_Color const& color) : currentFont(font), currentColor(color)
{
}

GE_Text::GE_Text(TTF_Font* font) : currentFont(font)
{
	SDL_Color color = {255, 255, 255};
	currentColor = color;
}

GE_Text::GE_Text() : currentFont(nullptr)
{
	SDL_Color color = {255, 255, 255};
	currentColor = color;
}

//
// Print the text to the screen.
//
void GE_Text::Print(std::string const& text, float time)
{
	GE::TextPacket tmp;

	tmp.text = text;
	tmp.liveTime = time;
	tmp.startTime = -1.0f;
	tmp.textStreamFlag = false;
	tmp.deleteFlag = false;
	tmp.textStream = nullptr;

	printStrings.push_back(tmp);
}

//
// Print the fontStream to the screen.
//
void GE_Text::Print(GE_TextStream& textStream, float time)
{
	GE::TextPacket tmp;

	tmp.text = textStream.GetText();
	tmp.liveTime = time;
	tmp.startTime = -1.0f;
	tmp.textStreamFlag = true;
	tmp.deleteFlag = false;
	tmp.textStream = new GE_TextStream(textStream);

	printStrings.push_back(tmp);
}

//
// Draw the strings ready to be printed.
//
void GE_Text::DrawStrings(SDL_Surface* screen)
{
	if ( currentFont == nullptr )
	{
		std::cerr << "Attempting to call GE_Font::DrawStrings() without registering a font.\n";
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
void GE_Text::Update()
{
	// Determine if we have no strings to work with
	if ( printStrings.empty() )
	{
		if ( timer.GetState() )
		{
			timer.Stop();
		}
		return;
	}

	// Remove any elements flagged for deletion
	for ( auto itr = printStrings.begin(); itr != printStrings.end(); ++itr )
	{
		if ( itr->deleteFlag )
		{
			if ( itr->textStreamFlag )
			{
				if ( itr->textStream != nullptr )
				{
					delete itr->textStream;
					itr->textStream = nullptr;
				}
			}

			itr = printStrings.erase(itr);
			if ( itr == printStrings.end() )
			{
				break;
			}
		}
	}

	// Update values in formatted strings
	ParseStrings();
}

//
// Sets the current font.
// REMARKS: Unloads the currently loaded font, if it exists.
//
void GE_Text::SetFont(TTF_Font* font)
{
	if ( currentFont != nullptr )
	{
		TTF_CloseFont(currentFont);
		currentFont = nullptr;
	}

	currentFont = font;
}

//
// Sets the current color.
//
void GE_Text::SetColor(SDL_Color const& color)
{
	currentColor = color;
}