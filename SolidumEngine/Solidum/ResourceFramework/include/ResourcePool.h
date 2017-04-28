#pragma once
#include "../../sysInclude.h"

template < class ResourceType, typename EnumType, class FactoryType >
class ResourcePool
{
protected:
	FactoryType* _factory;
private:

	struct PerTypePool {
		std::list<int> _freeIndices;
		std::vector<ResourceType*> _pool;
	};

	std::vector<PerTypePool*> _commandPools;
public:
	ResourcePool() {};
	~ResourcePool() {};

	void allocateResources(EnumType type, int numResources) {

	}

	ResourceType* getResource(EnumType type) {
		IResource* resource = nullptr;

		PerTypePool* properPool;

		int typeIndex = (int)type;

		//Get the correct pool for given type
		if (_commandPools.size() <= typeIndex) {

			int diff = (typeIndex - _commandPools.size()) + 1;

			for (int i = 0; i <= diff; i++) {

				_commandPools.push_back(new PerTypePool());
			}
		}

		properPool = _commandPools[typeIndex];


		//Get resource from pool
		if (properPool->_freeIndices.empty()) {

			int newIndex = (properPool->_pool.size() + 1) - 1;

			properPool->_pool.push_back(_factory->createObject(type));
			properPool->_freeIndices.push_back(newIndex);
		}

		int newIndex = properPool->_freeIndices.back();

		properPool->_freeIndices.pop_back();

		resource = properPool->_pool[newIndex];
		resource->setPoolIndex(newIndex);


		return (ResourceType*)resource;
	}

	void releaseResource(ResourceType* res) {

		IResource* resource = (IResource*)res;

		resource->unload();

		PerTypePool* properPool;

		int typeIndex = (int)res->getType();

		//Get the correct pool for given type
		if (_commandPools.size() < typeIndex) {

			int diff = (typeIndex - _commandPools.size()) + 1;

			for (int i = 0; i < diff; i++) {
				_commandPools.push_back(new PerTypePool());
			}
			properPool = _commandPools.back();
		}
		else {
			properPool = _commandPools[typeIndex];
		}

		int index = res->getPoolIndex();

		//Add resource to pool
		properPool->_freeIndices.push_back(index);
	}
};

