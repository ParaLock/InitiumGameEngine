#pragma once
#include "../../sysInclude.h"

#include "../../MemoryManagement/include/SlabCache.h"

#include "../../ResourceFramework/include/ResourcePool.h"

#include "../../TaskFramework/include/Task.h"

#include "../../EngineCore/include/IEngineInstance.h"

#include "IResource.h"

struct ResourcePendingCreation {

	ResourcePendingCreation() {}

	ResourcePendingCreation(
		IResource* resource,
		std::function<void(IResource*)> resLoadedCallback
		)
	{
		_resource = resource;
		_resLoadedCallback = resLoadedCallback;
	}

	IResource* _resource;
	std::function<void(IResource*)> _resLoadedCallback;
};

class ResourceCreator
{
private:

	IEngineInstance* _sysInstance;

	std::mutex _pendingResourceQueueLock;

	std::shared_ptr<TaskHandle> _taskHandle;

	std::list<ResourcePendingCreation> _pendingResources;

public:
	ResourceCreator(IEngineInstance* sysInstance);
	~ResourceCreator();

	void waitForCompletionOfCreationTask();

	template<typename T_RESOURCE>
	void createResourceDeferred(typename T_RESOURCE::InitData* initParams, std::string name,
		std::function<void(IResource*)> resLoadedCallback) 
	{
		IResource* newResource = T_RESOURCE::Factory::createResource<T_RESOURCE, typename T_RESOURCE::POOL>(&T_RESOURCE::_pool);

		IResourceContext* context = newResource->getContext();

		newResource->name(name);
		context->setResourceInitParams(initParams);

		_pendingResources.push_back(ResourcePendingCreation(newResource, resLoadedCallback));
	}

	template<typename T_RESOURCE>
	T_RESOURCE* createResourceImmediate(typename T_RESOURCE::InitData* initParams, std::string name,
		std::function<void(IResource*)> resLoadedCallback)
	{
		IResource* newResource = T_RESOURCE::Factory::createResource<T_RESOURCE, typename T_RESOURCE::POOL>(&T_RESOURCE::_pool);

		IResourceContext* context = newResource->getContext();

		newResource->name(name);
		context->setResourceInitParams(initParams);

		newResource->load();

		resLoadedCallback((IResource*)newResource);

		return (T_RESOURCE*)newResource;

	}

	IEngineInstance* getParentEngine() { return _sysInstance; };

	void loadPendingResources();

	void setTaskHandle(std::shared_ptr<TaskHandle> handle) { _taskHandle = handle; };
};


