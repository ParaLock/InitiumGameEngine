#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../GraphicsCommand/include/GraphicsCommandFactory.h"
#include "../../GraphicsCommand/include/GraphicsCommandPool.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

class GraphicsCommandList
{
private:
	std::list<GraphicsCommand*> _commandList;
public:
	GraphicsCommandList();
	~GraphicsCommandList();

	void setRenderStateFlags() {};

	void queueCommand(GraphicsCommand* command);

	void executeCommands();
};

