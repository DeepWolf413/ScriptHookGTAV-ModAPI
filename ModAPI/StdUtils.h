#pragma once
#ifndef INCLUDE_UTILS_STDUTILS_H_
#define INCLUDE_UTILS_STDUTILS_H_
#include <string>
#include <vector>

namespace Utils
{
	namespace StdUtils
	{
		template <class elementType>
		bool VectorContainsElement(std::vector<elementType> vector, elementType element)
		{ return std::find(vector.begin(), vector.end(), element) != vector.end(); }

		// Sets all characters in the string to lower.
		extern std::string ToLower(std::string string);
	};
}

#endif