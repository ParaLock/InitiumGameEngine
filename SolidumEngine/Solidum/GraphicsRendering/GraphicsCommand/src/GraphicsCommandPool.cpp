#include "../include/GraphicsCommandPool.h"

void GraphicsCommandPool::allocateResources(GRAPHICS_COMMAND_TYPE type, int numResources)
{
	for (int i = 0; i < numResources; i++) {
		if (_freeList.find(type) == _freeList.end()) {
			_freeList.insert({ type, new std::list<GraphicsCommand*>() });
		}
		_freeList.at(type)->push_back(_factory->createObject(type));
	}
}

GraphicsCommand* GraphicsCommandPool::getResource(GRAPHICS_COMMAND_TYPE type) {

	if (_freeList.find(type) == _freeList.end()) {

		_freeList.insert({ type, new std::list<GraphicsCommand*>() });
	}

	if (_freeList.at(type)->size() == 0) {
		_freeList.at(type)->push_back(_factory->createObject(type));
	}

	GraphicsCommand* res = _freeList.at(type)->front();

	_freeList.at(type)->pop_front();

	return res;
}

void GraphicsCommandPool::releaseResource(GraphicsCommand* res) {
	res->unload();

	if (_freeList.find(res->getType()) == _freeList.end()) {
		_freeList.insert({ res->getType(), new std::list<GraphicsCommand*>() });
	}

	_freeList.at(res->getType())->push_back(res);
}
