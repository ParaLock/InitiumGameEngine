#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../../ResourceFramework/include/ResourceCreator.h"

#include "GraphicsCommandBlock.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

class GraphicsCommandList
{
private:

	std::list<GraphicsCommandBlock> _activeCmdBlockListStore;

	std::list<GraphicsCommandBlock*> _activeCmdBlockListSorted;

	ResourceCreator* _resourceCreator;

	void sortBlocks(std::list<GraphicsCommandBlock*>& list_in);

public:
	GraphicsCommandList(ResourceCreator* resourceCreator)
		: _resourceCreator(resourceCreator) 
	{
	};

	~GraphicsCommandList();

	IGraphicsCommandBlock* getNextCmdBlock(int priority);

	void executeCommands();
};

