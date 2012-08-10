// GE_TextStream.cpp
//
// Author: John Conder
// Date: 07/11/2012
//
// Purpose:
// The implementation of the functions for GE_TextStream.h

#include "GE_TextStream.h"

//
// Default constructor.
//
GE_TextStream::GE_TextStream()
{
}

//
// Basic accessor for member textStream.
//
std::string GE_TextStream::GetText()
{
	return textStream;
}

//
// Basic operation to return the (last - i) pointer in the ptrList in the
// TextStream object.
//
void* const GE_TextStream::GetPtr(int i)
{
	return ptrList.at(ptrList.size() - ++i);	// if size() == 1 then .at() should be 0.  Thus, we increment i before we subtract it.
}

//
// Basic operation to add text to the TextStream object.
//
GE_TextStream& operator<<(GE_TextStream& ts, std::string const& text)
{
	ts.textStream.append(text);

	return ts;
}

//
// Basic operations to add a ptr placeholder and address to the TextStream object.
//
GE_TextStream& operator<<(GE_TextStream& ts, int* ptr)
{
	ts.textStream.append("|fi");
	ts.ptrList.push_back((void*)ptr);

	return ts;
}

GE_TextStream& operator<<(GE_TextStream& ts, float* ptr)
{
	ts.textStream.append("|ff");
	ts.ptrList.push_back((void*)ptr);

	return ts;
}

GE_TextStream& operator<<(GE_TextStream& ts, double* ptr)
{
	ts.textStream.append("|fd");
	ts.ptrList.push_back((void*)ptr);

	return ts;
}