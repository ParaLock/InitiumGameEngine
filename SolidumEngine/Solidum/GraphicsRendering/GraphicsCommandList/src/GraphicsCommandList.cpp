#include "../include/GraphicsCommandList.h"



GraphicsCommandList::GraphicsCommandList()
{
}


GraphicsCommandList::~GraphicsCommandList()
{
	for each(GraphicsCommand* command in _loadedCommands) {
		IGraphicsCore::getInstance()->
			getGraphicsCommandPool()->releaseResource(command);
	}
}

void GraphicsCommandList::loadCommands()
{
	int start_s = clock();

	IGraphicsCore* gCore = IGraphicsCore::getInstance();
	GraphicsCommandPool* commandPool = gCore->getGraphicsCommandPool();

	for each(auto unloadedCommand in _unloadedCommands) {
		GraphicsCommand* command = commandPool->getResource(unloadedCommand._type);
		command->load(unloadedCommand._initData);
		_loadedCommands.push_back(command);
	}

	int stop_s = clock();
	std::cout << "GRAPHICS COMMAND LOAD TIME: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << std::endl;
}

void GraphicsCommandList::createCommand(std::shared_ptr<IResourceBuilder> builder, GRAPHICS_COMMAND_TYPE type)
{
	_unloadedCommands.push_back(unloadedCommandData(builder, type));
}

void GraphicsCommandList::executeCommands()
{
	for each(GraphicsCommand* command in _loadedCommands) {

		command->execute();
	}
}
