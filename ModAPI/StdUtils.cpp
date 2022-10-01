#include <algorithm>

#include "StdUtils.h"

namespace ModAPI::Utils
{
	std::string StdUtils::ToLower(const std::string& string)
	{
		auto lowercasedString = string;
		std::transform(lowercasedString.begin(), lowercasedString.end(), lowercasedString.begin(), tolower);

		return lowercasedString;
	}
	
}
