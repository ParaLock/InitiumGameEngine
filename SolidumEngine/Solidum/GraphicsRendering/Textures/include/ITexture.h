#pragma once

class ITexture 
{
private:
public:
	ITexture();
	virtual ~ITexture();

	int resSlot = 0;
	int parentShaderType = 0;

	virtual void Bind() = 0;
};

