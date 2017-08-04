#include "../include/GraphicsCommandList.h"


GraphicsCommandList::~GraphicsCommandList()
{
	for each(IGraphicsCommand* command in _loadedCommands) {

		IResource* resCast = dynamic_cast<IResource*>(command);

		resCast->release();
	}

	reset();
}

void GraphicsCommandList::commandLoadedCallback(IResource * loadedCmd)
{
	IGraphicsCommand* cmd = dynamic_cast<IGraphicsCommand*>(loadedCmd);

	_loadedCommands.push_back(cmd);
}

void GraphicsCommandList::executeCommands()
{
	for each(IGraphicsCommand* command in _loadedCommands) {

		command->execute();
	}
}

void GraphicsCommandList::reset()
{
	_loadedCommands.clear();
}
