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
	static IResource* createInner(ResourcePool* pool, IResourceCreator* creator);
public:
	TextureFactory();
	~TextureFactory();

	template<typename T, typename T_POOL>
	static IResource* createResource(T_POOL* pool, IResourceCreator* creator) {

		if (typeid(T) == typeid(Texture)) {

			return createInner(pool, creator);

		}

		return nullptr;
	}
};

