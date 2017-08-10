#include "../include/TextureSamplerFactory.h"

#include "../../Directx11Rendering/dxTextures/include/dxTextureSampleState.h"

IResource * TextureSamplerFactory::createInner(ResourcePool * pool, IResourceCreator* creator)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxTextureSampleState>(creator);

		break;
	}

	return nullptr;
}
