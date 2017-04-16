#pragma once
#include "../../../ResourceFramework/include/ResourcePool.h"

#include "RenderNodeFactory.h"

#include "RenderNode.h"
class RenderNodeFactory;

class RenderNodePool : public ResourcePool<RenderNode, RENDER_NODE_TYPE, RenderNodeFactory>
{
private:
public:
	RenderNodePool(RenderNodeFactory* factory) { _factory = factory; }
	~RenderNodePool() {};
};

