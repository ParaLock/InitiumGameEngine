#pragma once
#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxTextures/include/dxTextureSampleState.h"

#include "TextureSampler.h"

class TextureSamplerManager : public IResourceManager
{
public:
	TextureSamplerManager();
	~TextureSamplerManager();

	virtual IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

