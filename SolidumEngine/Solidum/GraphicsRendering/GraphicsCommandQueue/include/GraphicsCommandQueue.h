#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

class GraphicsCommandQueue
{
private:
	std::list<GraphicsCommand*>* _queue;
public:
	GraphicsCommandQueue();
	~GraphicsCommandQueue();

	void queueCommand(GraphicsCommand* command);

	void processCommands();
};

