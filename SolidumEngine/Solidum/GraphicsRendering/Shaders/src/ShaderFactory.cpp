#include "../include/ShaderFactory.h"

#include "../../Directx11Rendering/dxShaders/include/dxShader.h"

IResource * ShaderFactory::createInner(ResourcePool * pool)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxShader>();

		break;
	}

	return nullptr;
}
