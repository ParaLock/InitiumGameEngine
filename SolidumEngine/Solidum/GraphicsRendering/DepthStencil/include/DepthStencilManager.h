#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/ActiveGraphicsAPI.h"
#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../Directx11Rendering/dxDepthStencil/include/dxDepthStencil.h"

class DepthStencilManager : public IResourceManager
{
public:
	DepthStencilManager();
	~DepthStencilManager();

	IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

