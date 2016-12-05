#pragma once

class ITextureSampler 
{
public:
	ITextureSampler();
	virtual ~ITextureSampler();

	int resSlot = 0;
	int parentShaderType = 0;

	virtual void Bind() = 0;
};

