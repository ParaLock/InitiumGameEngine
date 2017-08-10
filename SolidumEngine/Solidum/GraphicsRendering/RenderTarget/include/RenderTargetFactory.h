#pragma once
#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/ResourcePool.h"

class RenderTarget;

class RenderTargetFactory
{
private:
	//This function is kinda a hack. For some reason the compiler did not
	//like a direct use of forward declared derived classes in template function.
	static IResource* createInner(ResourcePool* pool, IResourceCreator* creator);
public:
	RenderTargetFactory() {};
	~RenderTargetFactory() {};

	template<typename T, typename T_POOL>
	static IResource* createResource(ResourcePool* pool, IResourceCreator* creator) {

		if (typeid(T) == typeid(RenderTarget)) {

			return createInner(pool, creator);

		}

		return nullptr;
	}
};
