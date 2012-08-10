// GE_Rect.cpp
//
// Author: John Conder
// Date: 06/21/2012
//
// Purpose:
// The implementation of the functions for GE_Rect.h

#include "GE_Rect.h"

//
// Set the values of rect to the parameters.
//
void GE::MakeRect(GE::Rect* rect, float x, float y, float w, float h)
{
	if ( rect == nullptr )
	{
		rect = new GE::Rect;
	}

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

//
// Return a GERect with the values of the parameters.
//
GE::Rect GE::MakeRect(float x, float y, float w, float h)
{
	GE::Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

//
// Returns a pointer to a GERect with the values of the parameters.
//
GE::Rect* GE::MakePRect(float x, float y, float w, float h)
{
	GE::Rect* rect;
	rect = new GE::Rect;

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	return rect;
}