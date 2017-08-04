#pragma once
#include "../../sysInclude.h"

#include "../include/IResource.h"

class ResourcePool {
private:

	struct PerTypePool {
		std::list<unsigned int> _freeIndices;
		std::vector<IResource*> _resourcePool;
	};

	std::unordered_map<unsigned int, PerTypePool*> _resourcePools;
public:

	template<typename T>
	IResource* getResource() {

		unsigned int type = IResource::getTypeID(std::type_index(typeid(T)));

		if (type == 0) { IResource::addType(std::type_index(typeid(T))); type = IResource::getTypeID(std::type_index(typeid(T))); }

		IResource* resource = nullptr;

		PerTypePool* pool = nullptr;

		auto& itr = _resourcePools.find(type);

		if (itr != _resourcePools.end()) {
			pool = _resourcePools.at(type);
		}
		else {

			pool = new PerTypePool;

			_resourcePools.insert({ type, pool});
		}

		if (pool->_freeIndices.empty()) {

			int newIndex = (pool->_resourcePool.size() + 1) - 1;

			pool->_resourcePool.push_back(new T());
			pool->_freeIndices.push_back(newIndex);
		}

		int newIndex = pool->_freeIndices.back();

		pool->_freeIndices.pop_back();

		resource = pool->_resourcePool[newIndex];
		resource->poolIndex(newIndex);

		resource->type(type);

		return resource;
	}
	
	void releaseResource(IResource* res) {

		unsigned int type = res->type();

		PerTypePool* pool = nullptr;

		auto& itr = _resourcePools.find(type);

		if (itr != _resourcePools.end()) {
			pool = _resourcePools.at(type);
		}
		else {
			pool = new PerTypePool;
			_resourcePools.insert({ type, pool });
		}

		res->type(type);
		
		int index = res->poolIndex();

		pool->_freeIndices.push_back(index);
	}
};
