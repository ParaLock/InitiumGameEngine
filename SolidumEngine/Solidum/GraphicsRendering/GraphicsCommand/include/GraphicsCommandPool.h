#pragma once
#include "../../../ResourceFramework/include/ResourcePool.h"
#include "GraphicsCommandFactory.h"
#include "GraphicsCommand.h"

class GraphicsCommandPool : public ResourcePool<GraphicsCommand, GRAPHICS_COMMAND_TYPE>
{
private:
	struct PerTypePool {
		std::list<int> _freeIndices;
		std::vector<GraphicsCommand*> _pool;
	};

	GraphicsCommandFactory* _factory;

	std::vector<PerTypePool*> _commandPools;
public:
	GraphicsCommandPool(GraphicsCommandFactory* factory) { _factory = factory; };
	~GraphicsCommandPool() {};

	void allocateResources(GRAPHICS_COMMAND_TYPE type, int numResources);

	GraphicsCommand* getResource(GRAPHICS_COMMAND_TYPE type);

	void releaseResource(GraphicsCommand* res);
};

