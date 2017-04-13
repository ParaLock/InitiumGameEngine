#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommandList/include/GraphicsCommandList.h"

class GraphicsCommandListQueue
{
private:
	std::list<GraphicsCommandList*>* _queue;
public:
	GraphicsCommandListQueue();
	~GraphicsCommandListQueue();

	void queueCommandList(GraphicsCommandList* command);

	void processAllCommands();
};

