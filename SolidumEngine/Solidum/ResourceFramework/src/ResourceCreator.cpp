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

IResource* ResourceCreator::createResourceImmediate(ResourceInitParams * params, std::string name, std::string typeName, std::function<void(IResource*)> resLoadedCallback)
{
	PrototypeCache& cache = _sysInstance->getResourcePrototypeCache();

	auto& creationFunction = cache.getPrototype(typeName);

	IResource* newResource = creationFunction();

	IResourceContext* context = newResource->getContext();

	newResource->name(name);
	context->setResourceInitParams(params);

	newResource->load();

	resLoadedCallback((IResource*)newResource);

	return newResource;
}

void ResourceCreator::createResourceDeferred(ResourceInitParams * params, std::string name, std::string typeName, std::function<void(IResource*)> resLoadedCallback)
{
	PrototypeCache& cache = _sysInstance->getResourcePrototypeCache();

	auto& creationFunction = cache.getPrototype(typeName);

	IResource* newResource = creationFunction();

	IResourceContext* context = newResource->getContext();

	newResource->name(name);
	context->setResourceInitParams(params);

	_pendingResources.push_back(ResourcePendingCreation(newResource, resLoadedCallback));
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

std::unordered_map<std::type_index, unsigned int>& ResourceCreator::getTypeToTypeIDMap()
{
	return _typeIDByTypeIndex;
}

