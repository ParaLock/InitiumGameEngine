#pragma once

class IRenderTarget 
{
public:
	IRenderTarget();
	virtual ~IRenderTarget();

	int resSlot;
	int parentShaderType;

	virtual void BindAsShaderResource() = 0;

	virtual void Clear(float R, float G, float B, float A) = 0;
};

