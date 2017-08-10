#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "TextureSamplerFactory.h"

class ResourcePool;

class TextureSampler : public Resource<TextureSampler, TextureSamplerFactory, ResourcePool>
{
public:
	TextureSampler();
	~TextureSampler();

	struct InitData : public ResourceInitParams {

		InitData() {}

		

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

	virtual void load() = 0;
	virtual void unload() = 0;

protected:
};

