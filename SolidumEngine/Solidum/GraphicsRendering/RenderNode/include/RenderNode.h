#pragma once
#include "../../../sysInclude.h"

#include "../../RenderParameters/include/RenderParams.h"

#include "../../GraphicsCommandListQueueManager/include/GCLQManager.h"
#include "../../ShaderCommands/include/ShaderCommand.h"

#include "../../../ResourceFramework/include/IResource.h"

class IResource;
class GPUPipeline;
class RenderComposite;

class RenderNode : public IResource
{
protected:
	uint64_t _id;

	RENDER_NODE_TYPE _type;

	RenderParams _renderParams;

	RenderNode* _parent = nullptr;
	RenderNode* _child = nullptr;

public:
	RenderNode();
	~RenderNode();

	virtual void updateGlobalRenderParams(GlobalRenderingParams params);

	virtual void render() = 0;

	void setChild(RenderNode* child) { _child = child; };
	RenderNode* getChild() { return _child; }

	void setParent(RenderNode* parent) { _parent = parent; };
	RenderNode* getParent() { return _parent; };

	RENDER_NODE_TYPE getType() { return _type; }
	RenderParams* getRenderParams() { return &_renderParams; };

	virtual bool isRenderViable() = 0;

	uint64_t getID() { return _id; }
};

