#include "../include/GCLQManager.h"

GCLQManager* GCLQManager::singletonInstance = nullptr;

GCLQManager * GCLQManager::getInstance()
{
	return singletonInstance;
}

GCLQManager::GCLQManager()
{
	if (singletonInstance == nullptr)
		singletonInstance = this;
	else
		return;
}


GCLQManager::~GCLQManager()
{
}

void GCLQManager::createCommandQueue(std::string name)
{
	_commandQueues[name] = new GraphicsCommandListQueue();
}

void GCLQManager::setPrimaryCommandQueue(std::string name)
{
	_primaryQueueName = name;
}

GraphicsCommandListQueue * GCLQManager::getPrimaryCommandQueue()
{
	return _commandQueues.at(_primaryQueueName);
}

GraphicsCommandListQueue * GCLQManager::getCommandQueue(std::string name)
{
	return _commandQueues.at(name);
}
