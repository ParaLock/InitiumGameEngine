#pragma once
#include "../../../ResourceFramework/include/ResourcePool.h"
#include "GraphicsCommandFactory.h"
#include "GraphicsCommand.h"

class GraphicsCommandPool : public ResourcePool<GraphicsCommand, GRAPHICS_COMMAND_TYPE, GraphicsCommandFactory>
{
private:

public:
	GraphicsCommandPool(GraphicsCommandFactory* factory) { _factory = factory; };
	~GraphicsCommandPool() {};
};

