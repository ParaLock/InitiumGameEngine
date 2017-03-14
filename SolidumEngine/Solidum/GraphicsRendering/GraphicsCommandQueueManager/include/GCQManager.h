#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommandQueue/include/GraphicsCommandQueue.h"

class GCQManager
{
private:
	std::string _primaryQueueName = "null";
	std::map<std::string, GraphicsCommandQueue*> _commandQueues;
public:
	GCQManager();
	~GCQManager();

	void createCommandQueue(std::string name);
	void setPrimaryCommandQueue(std::string name);

	GraphicsCommandQueue* getPrimaryCommandQueue();
	GraphicsCommandQueue* getCommandQueue(std::string name);

	static GCQManager* singletonInstance;
	static GCQManager* getInstance();
};

