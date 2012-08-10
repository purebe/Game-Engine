// GE_Conversion.h
//
// Author: John Conder
// Date: 07/03/2012
//
// Purpose:
// Provides some utility conversion function wrappers.

#pragma once

#include <string>
#include <sstream>

namespace GE
{
	template <class T>
	std::string to_string(T const& t)
	{
		std::stringstream strm;
		strm << t;
		return strm.str();
	}
}