#pragma once
#include "../../../sysInclude.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Directx11Rendering/dxTextures/include/dxTextureSampleState.h"
#include "../../RenderingCore/include/ActiveAPITypeAccessor.h"

class TextureSamplerFactory
{
public:
	TextureSamplerFactory();
	~TextureSamplerFactory();

	static TextureSampler* createTextureSampler(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode);
};

