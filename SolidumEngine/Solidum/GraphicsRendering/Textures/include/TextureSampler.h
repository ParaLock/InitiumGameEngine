#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../ResourceFramework/include/IResource.h"

class TextureSamplerBuilder : public IResourceBuilder {
public:
	TEX_FILTERS _texFilterType;
	ANISOTRPHIC_FILTER_LEVELS _anisotropyFilterLevel;
	TEX_ADDR_MODES _texAddressMode;

	TextureSamplerBuilder(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode) {
		_texAddressMode = texAddressMode;
		_texFilterType = texFilterType;
		_anisotropyFilterLevel = anisotropyFilterLevel;
	}
};

class TextureSampler : public IResource
{
public:
	TextureSampler();
	~TextureSampler();

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);
};

