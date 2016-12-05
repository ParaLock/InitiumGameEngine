#include "../include/RenderTargetFactory.h"



RenderTargetFactory::RenderTargetFactory()
{
}


RenderTargetFactory::~RenderTargetFactory()
{
}

std::shared_ptr<std::vector<IRenderTarget*>> RenderTargetFactory::createRenderTargets(int numRenderTargets)
{
	std::shared_ptr<std::vector<IRenderTarget*>> newRenderTargets(new std::vector<IRenderTarget*>);

	for (int i = 0; i < numRenderTargets; i++) {
		newRenderTargets->push_back(new dxRenderTarget());
	}

	return newRenderTargets;
}
