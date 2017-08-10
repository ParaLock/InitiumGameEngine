#include "../include/ShaderFactory.h"

#include "../../Directx11Rendering/dxShaders/include/dxShader.h"

IResource * ShaderFactory::createInner(ResourcePool * pool, IResourceCreator* creator)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxShader>(creator);

		break;
	}

	return nullptr;
}
