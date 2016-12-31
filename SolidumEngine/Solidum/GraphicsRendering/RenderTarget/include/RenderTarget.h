#pragma once
#include "../../../sysInclude.h"

class RenderTarget
{
protected:

	int _mipLevel;
	int _aaSamples;
	int _texFormat;

public:
	RenderTarget();
	~RenderTarget();

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);

	virtual void Clear(float R, float G, float B, float A);
};

