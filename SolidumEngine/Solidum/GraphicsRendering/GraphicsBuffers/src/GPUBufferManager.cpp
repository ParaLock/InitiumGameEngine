#include "../include/GPUBufferManager.h"



GPUBufferManager::GPUBufferManager()
{
}


GPUBufferManager::~GPUBufferManager()
{
}

IResource* GPUBufferManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{

	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		newResource = new dxGPUBuffer();
		break;
	}

	if (loadAsync) {

	}
	else {
		newResource->load(builder);
	}

	_activeResources->insert({ name, newResource });

	return newResource;
}
