#pragma once

#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/ResourcePool.h"

class Shader;
class ResourcePool;

class ShaderFactory
{
private:
	//This function is kinda a hack. For some reason the compiler did not
	//like a direct use of forward declared derived classes in template function.
	static IResource* createInner(ResourcePool* pool);
public:
	ShaderFactory();
	~ShaderFactory();

	template<typename T, typename T_POOL>
	static IResource* createResource(T_POOL* pool) {

		if (typeid(T) == typeid(Shader)) {

			return createInner(pool);

		}

		return nullptr;

	}
};

