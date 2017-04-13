#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommandListQueue/include/GraphicsCommandListQueue.h"

class GCLQManager
{
private:
	std::string _primaryQueueName = "null";
	std::map<std::string, GraphicsCommandListQueue*> _commandQueues;
public:
	GCLQManager();
	~GCLQManager();

	void createCommandQueue(std::string name);
	void setPrimaryCommandQueue(std::string name);

	GraphicsCommandListQueue* getPrimaryCommandQueue();
	GraphicsCommandListQueue* getCommandQueue(std::string name);

	static GCLQManager* singletonInstance;
	static GCLQManager* getInstance();
};

