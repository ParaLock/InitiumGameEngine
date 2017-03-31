#pragma once
#include "../../../sysInclude.h"

#include "../../RenderParameters/include/RenderParams.h"

#include "../../GraphicsCommandQueueManager/include/GCQManager.h"
#include "../../ShaderCommands/include/ShaderCommand.h"

class IResource;
class GPUPipeline;
class RenderComposite;
class IShader;

class RenderNode
{
protected:
	IShader* _shader = nullptr;

	uint64_t _id;

	RENDER_NODE_TYPE _type;

	RenderParams _renderParams;

	RenderNode* _parent = nullptr;
	RenderNode* _child = nullptr;

	bool _isVisible = false;
public:
	RenderNode();
	~RenderNode();

	virtual void* getVar(std::string varname) { return nullptr; };

	virtual void updateGlobalRenderParams(GlobalRenderingParams params);

	virtual void render() = 0;

	void setChild(RenderNode* child) { _child = child; };
	RenderNode* getChild() { return _child; }

	void setParent(RenderNode* parent) { _parent = parent; };
	RenderNode* getParent() { return _parent; };

	void setVisibility(bool isVisible) { _isVisible = isVisible; };

	RENDER_NODE_TYPE getType() { return _type; }
	RenderParams* getRenderParams() { return &_renderParams; };

	bool getVisibility() { return _isVisible; };

	virtual bool isRenderViable() = 0;

	uint64_t getID() { return _id; }

	IShader* getShader() { return _shader; }
};

