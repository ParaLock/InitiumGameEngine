#include "../include/RenderNodePool.h"

void RenderNodePool::allocateResources(RENDER_NODE_TYPE type, int numResources) {

	for (int i = 0; i < numResources; i++) {
		if (_freeList.find(type) == _freeList.end()) {
			_freeList.insert({ type, std::list<RenderNode*>() });
		}
		_freeList.at(type).push_back(_factory->createObject(type));
	}
}

RenderNode * RenderNodePool::getResource(RENDER_NODE_TYPE type)
{
	if (_freeList.find(type) == _freeList.end()) {
		_freeList.insert({ type, std::list<RenderNode*>() });
	}

	if (_freeList.at(type).size() == 0) {
		_freeList.at(type).push_back(_factory->createObject(type));
	}

	RenderNode* res = _freeList.at(type).front();

	_freeList.at(type).pop_front();

	return res;
}

void RenderNodePool::releaseResource(RenderNode * res)
{
	if (_freeList.find(res->getType()) == _freeList.end()) {
		_freeList.insert({ res->getType(), std::list<RenderNode*>() });
	}

	_freeList.at(res->getType()).push_back(res);
}
