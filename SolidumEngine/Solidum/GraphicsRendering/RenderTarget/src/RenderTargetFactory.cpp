#include "../include/RenderTargetFactory.h"

#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

IResource * RenderTargetFactory::createInner(ResourcePool * pool, IResourceCreator* creator)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxRenderTarget>(creator);

		break;
	}

	return nullptr;
}