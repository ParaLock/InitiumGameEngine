#pragma once
#include "../../../ResourceManagement/include/IResourceManager.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxTextures/include/dxTextureSampleState.h"

#include "TextureSampler.h"

class TextureSamplerManager : public IResourceManager
{
public:
	TextureSamplerManager();
	~TextureSamplerManager();

	virtual IResource* createResource(IResourceBuilder* builder, std::string name);
};

