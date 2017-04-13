#pragma once
#include "../../../ResourceFramework/include/ResourcePool.h"

#include "RenderNodeFactory.h"

#include "RenderNode.h"
class RenderNodeFactory;

class RenderNodePool : public ResourcePool<RenderNode, RENDER_NODE_TYPE>
{
private:
	std::map<RENDER_NODE_TYPE, std::list<RenderNode*>> _freeList;
	RenderNodeFactory* _factory;
public:
	RenderNodePool(RenderNodeFactory* factory) { _factory = factory; }
	~RenderNodePool() {};

	void allocateResources(RENDER_NODE_TYPE type, int numResources);

	RenderNode* getResource(RENDER_NODE_TYPE type);

	void releaseResource(RenderNode* res);
};

