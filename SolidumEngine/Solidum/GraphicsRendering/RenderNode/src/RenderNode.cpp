#include "../include/RenderNode.h"



RenderNode::RenderNode()
{
}


RenderNode::~RenderNode()
{
}

void RenderNode::updateGlobalRenderParams(GlobalRenderingParams params)
{
	_renderParams.setAllGlobalParams(params);
}
