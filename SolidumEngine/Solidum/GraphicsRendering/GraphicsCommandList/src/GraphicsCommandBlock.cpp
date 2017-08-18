#include "..\include\GraphicsCommandBlock.h"



void GraphicsCommandBlock::commandLoadedCallback(IResource * loadedCmd)
{
	IGraphicsCommand* cmd = dynamic_cast<IGraphicsCommand*>(loadedCmd);

	_loadedCommands.push_back(cmd);
}

GraphicsCommandBlock::GraphicsCommandBlock(int priority, ResourceCreator& creator) :
	_resourceCreator(creator)
{
	_executionPriority = priority;
}


GraphicsCommandBlock::~GraphicsCommandBlock()
{
	for each(IGraphicsCommand* command in _loadedCommands) {

		IResource* resCast = dynamic_cast<IResource*>(command);

		resCast->release();
	}
}

void GraphicsCommandBlock::execute()
{
	for each(IGraphicsCommand* command in _loadedCommands) {
	
		command->execute();

	}
}
