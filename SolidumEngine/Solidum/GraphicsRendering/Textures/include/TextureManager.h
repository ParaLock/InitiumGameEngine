#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"
#include "../../../ResourceFramework/include/IResource.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../Directx11Rendering/dxTextures/include/dxTexture.h"
#include "../../Textures/include/Texture.h"

class TextureManager : public IResourceManager
{
public:
	TextureManager();
	~TextureManager();

	virtual IResource* createResource(IResourceBuilder* builder, std::string name);
};

