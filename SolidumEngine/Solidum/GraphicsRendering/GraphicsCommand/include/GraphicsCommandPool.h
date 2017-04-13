#pragma once
#include "../../../ResourceFramework/include/ResourcePool.h"
#include "GraphicsCommandFactory.h"
#include "GraphicsCommand.h"

class GraphicsCommandPool : public ResourcePool<GraphicsCommand, GRAPHICS_COMMAND_TYPE>
{
private:
	std::map<GRAPHICS_COMMAND_TYPE, std::list<GraphicsCommand*>*> _freeList;
	GraphicsCommandFactory* _factory;
public:
	GraphicsCommandPool(GraphicsCommandFactory* factory) { _factory = factory; };
	~GraphicsCommandPool() {};

	void allocateResources(GRAPHICS_COMMAND_TYPE type, int numResources);

	GraphicsCommand* getResource(GRAPHICS_COMMAND_TYPE type);

	void releaseResource(GraphicsCommand* res);
};

