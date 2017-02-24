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


	int debugRef = -1;
}

void RenderNode::updateLocalRenderParams(LocalRenderingParams params)
{
	_renderParams.setAllLocalParams(params);
}
