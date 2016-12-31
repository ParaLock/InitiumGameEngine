#pragma once
#include "../../../sysInclude.h"

class Texture
{
public:
	Texture();
	~Texture();

	virtual void loadImage(LPCWSTR filename);

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);
};

