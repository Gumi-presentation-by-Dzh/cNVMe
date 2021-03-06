/*
This file is part of cNVMe and is released under the MIT License
(C) - Charles Machalow - 2017
Strings.h - A header file for the Strings (helper) functions
*/

#pragma once

#include "Types.h"

/// <summary>
/// Used to get the params for strings::toString
/// </summary>
#define ToStringParams(abbreviation, description) \
	abbreviation, #abbreviation, description

namespace cnvme
{
	namespace strings
	{
		/// <summary>
		/// Fills a string with a given width
		/// </summary>
		/// <param name="str">given string to fill</param>
		/// <param name="width">width</param>
		/// <returns>Filled string</returns>
		std::string rfill(std::string str, unsigned int width);

		/// <summary>
		/// Converts the given value to a hex string (without to leading 0x)
		/// </summary>
		std::string toHexString(UINT_64 value);

		/// <summary>
		/// Takes a value, abbreviation, description and returns a nice looking string representation
		/// </summary> 
		std::string toString(UINT_64 value, std::string abbreviation, std::string description);
	
		/// <summary>
		/// Converts bool to string
		/// </summary>
		std::string toString(bool value);

		/// <summary>
		/// indents a given string by 2 spaces
		/// </summary>
		std::string indentLines(std::string str);
	}
}