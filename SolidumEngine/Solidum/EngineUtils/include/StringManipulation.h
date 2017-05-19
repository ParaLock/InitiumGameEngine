#pragma once
#include "../../sysInclude.h"

class StringManipulation
{
public:
	StringManipulation();
	~StringManipulation();

	static std::vector<std::string> split(std::string * text, const char* delim);

	static std::string ws2s(const std::wstring& wstr);

	static bool is_number(const std::string& s)
	{
		return !s.empty() && std::find_if(s.begin(),
			s.end(), [](char c) { return !isdigit(c); }) == s.end();
	}

};

