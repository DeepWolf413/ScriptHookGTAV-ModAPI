#pragma once
#include <string>
#include <vector>

namespace ModAPI::Utils::StdUtils
{
	template <class elementType>
	bool VectorContainsElement(std::vector<elementType> vector, elementType element)
	{
		return std::find(vector.begin(), vector.end(), element) != vector.end();
	}

	// Sets all characters in the string to lower.
	extern std::string ToLower(const std::string& string);;
}