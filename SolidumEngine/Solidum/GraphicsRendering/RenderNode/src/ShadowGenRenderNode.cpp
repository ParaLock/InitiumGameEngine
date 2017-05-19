#include "../include/ShadowGenRenderNode.h"



ShadowGenRenderNode::ShadowGenRenderNode()
{
	_type = RENDER_NODE_TYPE::SHADOW_GEN_RENDER_NODE;
}


ShadowGenRenderNode::~ShadowGenRenderNode()
{
}

void ShadowGenRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_id = realBuilder->_id;

	isLoaded = true;
}

void ShadowGenRenderNode::unload()
{
	_parent = nullptr;
	_child = nullptr;


	isLoaded = false;
}

bool ShadowGenRenderNode::isRenderViable()
{
	return true;
}

void ShadowGenRenderNode::render()
{
	_renderParams.setPerNodeParam_isVisible(true);
}
