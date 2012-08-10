// GE_Rect.h
//
// Author: John Conder
// Date: 05/11/2012
//
// Purpose:
// This header contains the GERect struct.

#pragma once

namespace GE
{
	//
	// The common rect struct used in the GE.
	//
	struct Rect
	{
		float x, y;
		float w, h;
	};

	void MakeRect(Rect* rect, float x, float y, float w, float h);
	Rect MakeRect(float x, float y, float w, float h);
	Rect* MakePRect(float x, float y, float w, float h);
}