#pragma once
#include "../../sysInclude.h"

class StringManipulation
{
public:
	StringManipulation();
	~StringManipulation();

	static std::vector<std::string> split(std::string * text, char sep);

	static std::string ws2s(const std::wstring& wstr);

};

