#pragma once
#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/ResourcePool.h"

class GPUBuffer;
class ResourcePool;

class GPUBufferFactory
{
private:
	//This function is kinda a hack. For some reason the compiler did not
	//like a direct use of forward declared derived classes in template function.
	static IResource* createInner(ResourcePool* pool, IResourceCreator* creator);
public:
	GPUBufferFactory() {};
	~GPUBufferFactory() {};

	template<typename T, typename T_POOL>
	static IResource* createResource(ResourcePool* pool, IResourceCreator* creator) {

		if (std::is_same<T, GPUBuffer>::value) {

			return createInner(pool, creator);

		}

		return nullptr;
	}
};
