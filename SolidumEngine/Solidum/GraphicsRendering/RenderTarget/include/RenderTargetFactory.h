#pragma once

#include "../include/IRenderTarget.h"
#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

class RenderTargetFactory
{
public:
	RenderTargetFactory();
	~RenderTargetFactory();

	static std::shared_ptr<std::vector<IRenderTarget*>> createRenderTargets(int numRenderTargets);
};
