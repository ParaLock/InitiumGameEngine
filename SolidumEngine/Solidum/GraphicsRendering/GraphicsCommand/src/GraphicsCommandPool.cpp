#include "../include/GraphicsCommandPool.h"

void GraphicsCommandPool::allocateResources(GRAPHICS_COMMAND_TYPE type, int numResources) 
{

}

GraphicsCommand* GraphicsCommandPool::getResource(GRAPHICS_COMMAND_TYPE type) 
{
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
	

	return (GraphicsCommand*)resource;
}

void GraphicsCommandPool::releaseResource(GraphicsCommand* res) 
{

	IResource* resource = (IResource*)res;

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
