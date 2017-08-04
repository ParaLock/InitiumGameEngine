#include "../include/TextureFactory.h"

#include "../../Directx11Rendering/dxTextures/include/dxTexture.h"

IResource * TextureFactory::createInner(ResourcePool * pool)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxTexture>();

		break;
	}

	return nullptr;
}
