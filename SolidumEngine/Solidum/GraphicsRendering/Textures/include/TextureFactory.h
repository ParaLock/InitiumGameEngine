#pragma once

#include "../../ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/ResourcePool.h"

class Texture;
class ResourcePool;

class TextureFactory
{
private:
	//This function is kinda a hack. For some reason the compiler did not
	//like a direct use of forward declared derived classes in template function.
	static IResource* createInner(ResourcePool* pool);
public:
	TextureFactory();
	~TextureFactory();

	template<typename T, typename T_POOL>
	static IResource* createResource(T_POOL* pool) {

		if (typeid(T) == typeid(Texture)) {

			return createInner(pool);

		}

		return nullptr;
	}
};

