#pragma once
#include "../../../sysInclude.h"

class Shader;
class RenderNode;

struct GlobalRenderingParams;
struct LocalRenderingParams;

class IRenderNodeTree
{
public:
	IRenderNodeTree();
	~IRenderNodeTree();

	virtual uint64_t getUniqueNodeID() = 0;

	virtual void setExecutionOrder(std::vector<SHADER_RENDER_TYPE> order) = 0;

	virtual void addNode(RenderNode* node, uint64_t id) = 0;

	virtual void updateGlobalRenderParams(GlobalRenderingParams params) = 0;

	virtual void updateNodeVisibility(bool isVisible, uint64_t nodeid) = 0;

	virtual std::vector<RenderNode*> queryAllShadowCastingLights() = 0;
	virtual std::vector<RenderNode*> queryAllMeshes() = 0;

	virtual void removeNode(uint64_t id) = 0;

	virtual void frustrumCull() = 0;

	virtual void optimize() = 0;

	virtual void walkTree() = 0;
};

