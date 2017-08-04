#include "../include/ResourceCreator.h"


ResourceCreator::ResourceCreator(IEngineInstance * sysInstance)
{
	_sysInstance = sysInstance;
}

ResourceCreator::~ResourceCreator()
{
}

void ResourceCreator::waitForCompletionOfCreationTask()
{
	if(_taskHandle)
		while (!_taskHandle->_taskComplete) {}
}

void ResourceCreator::loadPendingResources()
{
	for (auto itr = _pendingResources.begin(); itr != _pendingResources.end(); itr++) {

		ResourcePendingCreation resourceDesc = *itr;

		resourceDesc._resource->load();

		resourceDesc._resLoadedCallback(resourceDesc._resource);
	}

	_pendingResources.clear();

}
