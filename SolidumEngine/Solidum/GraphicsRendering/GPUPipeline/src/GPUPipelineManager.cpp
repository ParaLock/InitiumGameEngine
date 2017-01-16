#include "../include/GPUPipelineManager.h"



GPUPipelineManager::GPUPipelineManager()
{
}


GPUPipelineManager::~GPUPipelineManager()
{
}

IResource* GPUPipelineManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newResource = nullptr;

	newResource = GPUPipelineFactory::createPipeline(builder);

	if (newResource != nullptr) {
		_activeResources->insert({ name, newResource });

		return newResource;
	}

	return nullptr;
}
