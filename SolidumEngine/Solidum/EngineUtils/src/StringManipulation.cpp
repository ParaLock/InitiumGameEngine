#include "../include/StringManipulation.h"



StringManipulation::StringManipulation()
{
}


StringManipulation::~StringManipulation()
{
}

std::vector<std::string> StringManipulation::split(std::string * s, const char* delim)
{
	s->erase(std::remove(s->begin(), s->end(), '\t'), s->end());

	std::vector<std::string> tokens;

	char * dup = strdup(s->c_str());
	char * token = strtok(dup, delim);
	while (token != NULL) {
		tokens.push_back(std::string(token));
		token = strtok(NULL, delim);
	}

	free(dup);

	return tokens;
}

std::string StringManipulation::ws2s(const std::wstring & wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
	
}
