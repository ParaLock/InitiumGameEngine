#pragma once
#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"
#include "../../RenderingCore/include/ActiveAPITypeAccessor.h"

class RenderTargetFactory
{
private:
public:
	RenderTargetFactory();
	~RenderTargetFactory();

	static RenderTarget* createRenderTarget(int mipLevel, int aaSamples, TEX_FORMAT texFormat);
};

