#include "../include/TextureSamplerFactory.h"



TextureSamplerFactory::TextureSamplerFactory()
{
}


TextureSamplerFactory::~TextureSamplerFactory()
{
}

TextureSampler * TextureSamplerFactory::createTextureSampler(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode)
{
	TextureSampler* sampleState = nullptr;

	switch (ActiveAPITypeAccessor::_apiInUse) {
	case DIRECTX11:
		sampleState = new dxTextureSampleState(texFilterType, anisotropyFilterLevel, texAddressMode);
		break;
	}

	return sampleState;
}
