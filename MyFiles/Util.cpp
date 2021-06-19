#include "Util.h"

std::string Util::ToLower(std::string input)
{
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	return input;
}
