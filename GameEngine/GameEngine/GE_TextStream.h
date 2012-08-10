// GE_TextStream.h
//
// Author: John Conder
// Date: 07/09/2012
//
// Purpose:
// Provides a TextStream object that can be used to pass variable data to the
// GE_Font engine instead of textual strings.  The reasoning behind
// this is in order to provide a way to display things such as Frames Per 
// Second (FPS) which change constantly, and should be updated every frame,
// without having to resort to manually calling a Print() for each update.
// Instead, you pass the string "FPS: " and a pointer to the FPS value
// to a FontStream, and then Print the fontstream on a FontEngine.

#pragma once

#include "GE_Conversion.h"

#include <string>
#include <vector>

class GE_TextStream
{
protected:
	std::vector<void* const> ptrList;
	std::string textStream;

public:
	GE_TextStream();

	std::string GetText();
	void* const GetPtr(int i);

	friend GE_TextStream& operator<<(GE_TextStream& ts, std::string const& text);
	friend GE_TextStream& operator<<(GE_TextStream& ts, int* ptr);
	friend GE_TextStream& operator<<(GE_TextStream& ts, float* ptr);
	friend GE_TextStream& operator<<(GE_TextStream& ts, double* ptr);

	template <class T> friend GE_TextStream& operator<<(GE_TextStream& ts, T const& value);
};

template <typename T>
GE_TextStream& operator<<(GE_TextStream& ts, T const& value)
{
	ts.textStream.append(GE::to_string(value));

	return ts;
}