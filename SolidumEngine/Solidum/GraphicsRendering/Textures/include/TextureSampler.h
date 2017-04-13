#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../ResourceFramework/include/IResource.h"

class TextureSampler : public IResource
{
public:
	TextureSampler();
	~TextureSampler();

	struct InitData : public IResourceBuilder {

		TEX_FILTERS _texFilterType;
		ANISOTRPHIC_FILTER_LEVELS _anisotropyFilterLevel;
		TEX_ADDR_MODES _texAddressMode;

		InitData(TEX_FILTERS texFilterType, 
					ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, 
						TEX_ADDR_MODES texAddressMode) 
		{
			_texAddressMode = texAddressMode;
			_texFilterType = texFilterType;
			_anisotropyFilterLevel = anisotropyFilterLevel;
		}
	};

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;
};

