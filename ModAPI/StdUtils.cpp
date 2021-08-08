#include <algorithm>

#include "StdUtils.h"

std::string Utils::StdUtils::ToLower(std::string string)
{
	auto lowercasedString = string;
	std::transform(lowercasedString.begin(), lowercasedString.end(), lowercasedString.begin(), tolower);

	return lowercasedString;
}
