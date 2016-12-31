#include "../include/GraphicsResourcePoolManager.h"



GraphicsResourcePoolManager::GraphicsResourcePoolManager()
{
	_activePoolList = new std::map<std::string, GraphicsResourcePool*>;
}


GraphicsResourcePoolManager::~GraphicsResourcePoolManager()
{
	delete _activePoolList;
}

void GraphicsResourcePoolManager::createNewResourcePool(std::string poolID)
{
	GraphicsResourcePool *newPool = new GraphicsResourcePool(poolID);

	_activePoolList->insert({poolID, newPool});
}

GraphicsResourcePool * GraphicsResourcePoolManager::getPool(std::string poolID)
{
	std::map<std::string, GraphicsResourcePool*>::iterator itr = _activePoolList->find(poolID);

	GraphicsResourcePool *pool = nullptr;

	if (itr != _activePoolList->end()) {
		pool = _activePoolList->at(poolID);
	}

	return pool;
}

