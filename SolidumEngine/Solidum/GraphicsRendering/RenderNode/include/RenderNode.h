#pragma once
#include "../../../sysInclude.h"

#include "../../RenderParameters/include/RenderParams.h"

class IResource;
class GPUPipeline;
class RenderComposite;
class IShader;

class RenderNode
{
protected:
	uint64_t id;
	IShader* _shader;

	RenderParams _renderParams;

	RenderNode* _parent = nullptr;
	RenderNode* _child = nullptr;

	bool _isVisible = false;
public:
	RenderNode();
	~RenderNode();

	virtual void updateGlobalRenderParams(GlobalRenderingParams params);
	virtual void updateLocalRenderParams(LocalRenderingParams params);

	virtual void render() = 0;

	void setChild(RenderNode* child) { _child = child; };
	RenderNode* getChild() { return _child; }

	void setParent(RenderNode* parent) { _parent = parent; };
	RenderNode* getParent() { return _parent; };

	void setVisibility(bool isVisible) { _isVisible = isVisible; };

	IShader* getShader() { return _shader; }
};

