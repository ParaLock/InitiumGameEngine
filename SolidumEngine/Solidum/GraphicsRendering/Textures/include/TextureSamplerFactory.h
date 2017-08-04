#pragma once

#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/ResourcePool.h"

class TextureSampler;

class TextureSamplerFactory {
private:
	//This function is kinda a hack. For some reason the compiler did not
	//like a direct use of forward declared derived classes in template function.
	static IResource* createInner(ResourcePool* pool);
public:

	template<typename T, typename T_POOL>
	static IResource* createResource(ResourcePool* pool) {

		if (typeid(T) == typeid(TextureSampler)) {

			return createInner(pool);
		}

		return nullptr;
	}

private:
};