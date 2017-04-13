#pragma once
#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"
#include "RenderTarget.h"

class RenderTargetManager : public IResourceManager
{
public:
	RenderTargetManager();
	~RenderTargetManager();

	virtual IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

