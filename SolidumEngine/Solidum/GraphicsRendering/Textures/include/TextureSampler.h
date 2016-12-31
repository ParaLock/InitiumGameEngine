#pragma once
#include "../../../sysInclude.h"

class TextureSampler
{
public:
	TextureSampler();
	~TextureSampler();

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);
};

