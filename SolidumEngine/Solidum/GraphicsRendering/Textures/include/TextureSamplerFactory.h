#pragma once

#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxTextures/include/dxTextureSampleState.h"

class TextureSamplerFactory
{
public:
	TextureSamplerFactory();
	~TextureSamplerFactory();

	static ITextureSampler* createTextureSampler(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode);
};

