#pragma once
#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/ResourcePool.h"

class dxDepthStencil;
class ResourcePool;
class DepthStencil;

class DepthStencilFactory
{
private:
	//This function is kinda a hack. For some reason the compiler did not
	//like a direct use of forward declared derived classes in template function.
	static IResource* createInner(ResourcePool* pool);
public:
	DepthStencilFactory() {};
	~DepthStencilFactory() {};

	template<typename T, typename T_POOL>
	static IResource* createResource(ResourcePool* pool) {

		if (std::is_same<T, DepthStencil>::value) {

			return createInner(pool);

		}

		return nullptr;
	}
};
