#include "../include/DepthStencilFactory.h"

#include "../../Directx11Rendering/dxDepthStencil/include/dxDepthStencil.h"

IResource * DepthStencilFactory::createInner(ResourcePool * pool, IResourceCreator* creator)
{

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxDepthStencil>(creator, []() {return new dxDepthStencil; });

		break;
	}


	return nullptr;
}


