#include "../include/StringManipulation.h"



StringManipulation::StringManipulation()
{
}


StringManipulation::~StringManipulation()
{
}

std::vector<std::string> StringManipulation::split(std::string * text, char sep)
{
	text->erase(std::remove(text->begin(), text->end(), '\t'), text->end());

	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;

	while ((end = text->find(sep, start)) != std::string::npos) {
		tokens.push_back(text->substr(start, end - start));
		start = end + 1;
	}

	tokens.push_back(text->substr(start));
	return tokens;
}

std::string StringManipulation::ws2s(const std::wstring & wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
	
}
