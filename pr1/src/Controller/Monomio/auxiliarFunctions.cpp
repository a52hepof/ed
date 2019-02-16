#include "auxiliarFunctions.hpp"


bool ed::near(const float &n1, const float &n2)
{
	return FLOAT_NEAR_PRESICION > abs(n1 - n2);
}

bool ed::isInt(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		if ( !isdigit(s[i]) )
		return false;

	return true;
}

bool ed::isFloat(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		if (! ( isdigit(s[i]) || s[i] == '.' ) )
		return false;

	return true;
}
