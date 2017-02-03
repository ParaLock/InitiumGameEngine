#include "../include/GPUPipelineManager.h"



GPUPipelineManager::GPUPipelineManager()
{
}


GPUPipelineManager::~GPUPipelineManager()
{
}

IResource* GPUPipelineManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		newResource = new dxGPUPipeline();
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
