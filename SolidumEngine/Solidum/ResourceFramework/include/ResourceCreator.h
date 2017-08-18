#pragma once

#include "PrototypeCache.h"

#include "../../sysInclude.h"

#include "../../../SolidumAPI/core_objects/include/SlabCache.h"

#include "../../ResourceFramework/include/ResourcePool.h"

#include "../../TaskFramework/include/Task.h"

#include "../../../SolidumAPI/core_interfaces/IEngineInstance.h"

#include "../../../SolidumAPI/core_interfaces/IResource.h"
#include "../../../SolidumAPI/core_interfaces/IResourceCreator.h"

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

class ResourceCreator : public IResourceCreator
{
private:

	std::unordered_map<std::type_index, unsigned int> _typeIDByTypeIndex;

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
		IResource* newResource = T_RESOURCE::Factory::createResource<T_RESOURCE, typename T_RESOURCE::POOL>(&T_RESOURCE::_pool, this);

		IResourceContext* context = newResource->getContext();

		newResource->name(name);
		context->setResourceInitParams(initParams);

		_pendingResources.push_back(ResourcePendingCreation(newResource, resLoadedCallback));
	}

	template<typename T_RESOURCE>
	T_RESOURCE* createResourceImmediate(typename T_RESOURCE::InitData* initParams, std::string name,
		std::function<void(IResource*)> resLoadedCallback)
	{
		IResource* newResource = T_RESOURCE::Factory::createResource<T_RESOURCE, typename T_RESOURCE::POOL>(&T_RESOURCE::_pool, this);

		IResourceContext* context = newResource->getContext();

		newResource->name(name);
		context->setResourceInitParams(initParams);

		newResource->load();

		resLoadedCallback((IResource*)newResource);

		return (T_RESOURCE*)newResource;

	}

	IResource* createResourceByPrototypeImmediate(ResourceInitParams* params, std::string name, std::string typeName,
		std::function<void(IResource*)> resLoadedCallback);

	void createResourceByPrototypeDeferred(ResourceInitParams* params, std::string name, std::string typeName,
		std::function<void(IResource*)> resLoadedCallback);

	template<typename T_PROTO>
	void addPrototype(std::string typeName) {

		PrototypeCache& cache = _sysInstance->getResourcePrototypeCache();

		cache.addPrototype(typeName,

			[=]() {

			IResource* newResource = T_PROTO::Factory::createResource
				<T_PROTO, typename T_PROTO::POOL>(&T_PROTO::_pool, this);

			return newResource;
		});
	}



	IEngineInstance* getParentEngine() { return _sysInstance; };

	void loadPendingResources();

	void setTaskHandle(std::shared_ptr<TaskHandle> handle) { _taskHandle = handle; };

	std::unordered_map<std::type_index, unsigned int>& getTypeToTypeIDMap();
};


