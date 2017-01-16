#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../Textures/include/TextureSampler.h"

class dxTextureSampleState : public TextureSampler
{
private:
	ID3D11SamplerState* sampleState;
public:
	dxTextureSampleState(IResourceBuilder *builder);
	~dxTextureSampleState();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);
};
