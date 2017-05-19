#pragma once
#include "../../RenderNode/include/RenderNode.h"

#include "../../Shaders/include/IShader.h"

#include "IRenderNodeTree.h"

class RenderNodeTree : public IRenderNodeTree
{
private:
	std::map<uint64_t, RenderNode*>* _nodeQueryMap;
	std::map<RENDER_NODE_TYPE, RenderNode*>* _rootNodes;
public:
	RenderNodeTree();
	~RenderNodeTree();

	uint64_t getUniqueNodeID();

	void addNode(RenderNode* node, uint64_t id);

	void updateGlobalRenderParams(GlobalRenderingParams params);

	void updateNodeVisibility(bool isVisible, uint64_t nodeid);

	RenderParams* getRenderNodeParams(uint64_t nodeid);

	std::list<RenderNode*> queryNodesByType(RENDER_NODE_TYPE type);

	void removeNode(uint64_t id);

	void frustrumCull();

	void optimize();

	void walkTree();
};

