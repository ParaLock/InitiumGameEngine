#include "../include/GraphicsCommandList.h"



GraphicsCommandList::GraphicsCommandList()
{
}


GraphicsCommandList::~GraphicsCommandList()
{
	for each(GraphicsCommand* command in _commandList) {
		IGraphicsCore::getInstance()->
			getGraphicsCommandPool()->releaseResource(command);
	}
}

void GraphicsCommandList::queueCommand(GraphicsCommand * command)
{
	_commandList.push_back(command);
}

void GraphicsCommandList::executeCommands()
{
	for each(GraphicsCommand* command in _commandList) {

		command->execute();
	}
}
