#pragma once

#include "../../../../SolidumAPI/core_interfaces/IGraphicsCommandBlock.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../../ResourceFramework/include/ResourceCreator.h"

class GraphicsCommandBlock : public IGraphicsCommandBlock
{
private:
	ResourceCreator& _resourceCreator;
	std::list<IGraphicsCommand*> _loadedCommands;

	int _executionPriority;

	void commandLoadedCallback(IResource* loadedCmd);
public:
	GraphicsCommandBlock(int priority, ResourceCreator& creator);
	~GraphicsCommandBlock();

	bool operator<(GraphicsCommandBlock& other) {
		if (_executionPriority < other._executionPriority) { return true; }

		return false;
	}

	template<typename T_CMD>
	void createCommand(typename T_CMD::InitData* params) {

		_resourceCreator.createResourceDeferred<T_CMD>(params, "",
			std::bind(&GraphicsCommandBlock::commandLoadedCallback, this, std::placeholders::_1)
			);
	}

	void execute();
};

