#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../Textures/include/ITextureSampler.h"

class dxTextureSampleState : public ITextureSampler
{
private:
	ID3D11SamplerState* sampleState;
public:
	dxTextureSampleState(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode);
	~dxTextureSampleState();

	ID3D11SamplerState *GetSampler() { return sampleState; };

	void Bind();
};
