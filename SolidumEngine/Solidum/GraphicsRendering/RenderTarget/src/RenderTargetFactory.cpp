#include "../include/RenderTargetFactory.h"



RenderTargetFactory::RenderTargetFactory()
{
}


RenderTargetFactory::~RenderTargetFactory()
{
}

RenderTarget * RenderTargetFactory::createRenderTarget(int mipLevel, int aaSamples, TEX_FORMAT texFormat)
{
	RenderTarget *renderTarget = nullptr;

	switch (ActiveAPITypeAccessor::_apiInUse) {
	case DIRECTX11:

		renderTarget = new dxRenderTarget(mipLevel, aaSamples, texFormat);
		break;
	}

	return renderTarget;
}
