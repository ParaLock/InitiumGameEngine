#include "../include/TextureSamplerFactory.h"

#include "../../Directx11Rendering/dxTextures/include/dxTextureSampleState.h"

IResource * TextureSamplerFactory::createInner(ResourcePool * pool)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxTextureSampleState>();

		break;
	}

	return nullptr;
}
