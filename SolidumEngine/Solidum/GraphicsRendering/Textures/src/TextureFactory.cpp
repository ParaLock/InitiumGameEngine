#include "../include/TextureFactory.h"

#include "../../Directx11Rendering/dxTextures/include/dxTexture.h"

IResource * TextureFactory::createInner(ResourcePool * pool, IResourceCreator* creator)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxTexture>(creator);

		break;
	}

	return nullptr;
}
