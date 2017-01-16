#include "../include/GPUBufferManager.h"



GPUBufferManager::GPUBufferManager()
{
}


GPUBufferManager::~GPUBufferManager()
{
}

IResource* GPUBufferManager::createResource(IResourceBuilder * builder, std::string name)
{

	IResource* newResource = nullptr;
	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		newResource = new dxGPUBuffer(builder);

		int ref12 = -1;
		break;
	}

	if (newResource != nullptr) {

		_activeResources->insert({ name, newResource });

		return newResource;
	}

	return nullptr;
}
