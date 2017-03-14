#include "../include/GCQManager.h"

GCQManager* GCQManager::singletonInstance = nullptr;

GCQManager * GCQManager::getInstance()
{
	return singletonInstance;
}

GCQManager::GCQManager()
{
	if (singletonInstance == nullptr)
		singletonInstance = this;
	else
		return;
}


GCQManager::~GCQManager()
{
}

void GCQManager::createCommandQueue(std::string name)
{
	_commandQueues[name] = new GraphicsCommandQueue();
}

void GCQManager::setPrimaryCommandQueue(std::string name)
{
	_primaryQueueName = name;
}

GraphicsCommandQueue * GCQManager::getPrimaryCommandQueue()
{
	return _commandQueues.at(_primaryQueueName);
}

GraphicsCommandQueue * GCQManager::getCommandQueue(std::string name)
{
	return _commandQueues.at(name);
}
