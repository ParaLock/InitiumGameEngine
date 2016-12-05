#include "../include/TextureSamplerFactory.h"



TextureSamplerFactory::TextureSamplerFactory()
{
}


TextureSamplerFactory::~TextureSamplerFactory()
{
}

ITextureSampler * TextureSamplerFactory::createTextureSampler(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode)
{
	return new dxTextureSampleState(texFilterType, anisotropyFilterLevel, texAddressMode);
}
