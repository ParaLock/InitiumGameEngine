#include "../include/GPUBufferFactory.h"

#include "../../Directx11Rendering/dxBuffers/include/dxGPUBuffer.h"

IResource * GPUBufferFactory::createInner(ResourcePool * pool)
{
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		return pool->getResource<dxGPUBuffer>();

		break;
	}

	return nullptr;
}
