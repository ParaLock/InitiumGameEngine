#include "../include/RenderTargetFactory.h"

#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

IResource * RenderTargetFactory::createInner(ResourcePool * pool)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxRenderTarget>();

		break;
	}

	return nullptr;
}