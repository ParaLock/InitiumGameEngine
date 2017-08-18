#pragma once

#include "../../sysInclude.h"

#include "../../ResourceFramework/include/ResourcePool.h"

class IResource;

class GenericFactory {
public:

	template<typename T, typename T_POOL>
	static IResource* createResource(T_POOL* pool, IResourceCreator* creator) { return (IResource*)pool->getResource<T>(creator, 
		[]() {return new T; }); }

private:
};
