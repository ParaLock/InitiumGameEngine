#pragma once

#include "../../Textures/include/ITexture.h"
#include "../../../sysInclude.h"

class IShader
{
public:
	IShader();
	virtual ~IShader();

	virtual void updateVar(std::string varName, void *data) = 0;

	virtual void Bind() = 0;

	virtual void updateGPU() = 0;

	virtual void attachTex(ITexture *tex);
};

