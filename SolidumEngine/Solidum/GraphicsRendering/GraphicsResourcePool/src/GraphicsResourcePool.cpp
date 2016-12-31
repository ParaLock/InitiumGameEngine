#include "../include/GraphicsResourcePool.h"

GraphicsResourcePool::GraphicsResourcePool(std::string poolID)
{
	_poolID = poolID;
	_resourceList = new std::map<std::string, std::pair<bool, void*>>;
}

GraphicsResourcePool::~GraphicsResourcePool()
{
	delete _resourceList;
}

void GraphicsResourcePool::addResource(void * res, std::string resName, bool shared)
{
	if (_resourceList->count(resName) == 0) {
		_resourceList->insert({ resName, std::make_pair(shared, res) });
	}
}

void * GraphicsResourcePool::getResource(std::string resName)
{
	void* res;

	if (_resourceList->count(resName) > 0) {
		std::pair<bool, void*> resCore = _resourceList->at(resName);

		res = resCore.second;

		if (!resCore.first) {
			_itr = _resourceList->find(resName);
			_resourceList->erase(_itr);
		}
	}
	else {
		res = nullptr;
	}

	return res;
}
