#include "../include/GPUPipelineManager.h"



GPUPipelineManager::GPUPipelineManager()
{
}


GPUPipelineManager::~GPUPipelineManager()
{
}

IResource* GPUPipelineManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	IResource* newResource = new GPUPipeline();

	if (loadAsync) {

	}
	else {
		newResource->load(builder);
	}

	_activeResources->insert({ name, newResource });

	return newResource;
}
