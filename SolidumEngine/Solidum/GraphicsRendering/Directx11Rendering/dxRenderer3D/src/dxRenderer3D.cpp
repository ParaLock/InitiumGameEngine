#include "../include/dxRenderer3D.h"



dxRenderer3D::dxRenderer3D()
{
}


dxRenderer3D::~dxRenderer3D()
{
}

void dxRenderer3D::setFrameBufferAsCurrent()
{
	dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

	dxCore->dxDevContext->OMSetRenderTargets(1, &dxCore->FrameBufferShaderAccess, dxCore->depthStencil);
}

void dxRenderer3D::clearFrameBuffer(float R, float G, float B, float A)
{
	dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

	dxCore->dxDevContext->ClearRenderTargetView(dxCore->FrameBufferShaderAccess, D3DXCOLOR(R, G, B, A));
}

void dxRenderer3D::clearZBuffer()
{
	dxDeviceAccessor::dxEncapsulator->clearDepthStencil();
}

void dxRenderer3D::swapFrame()
{
	dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

	dxCore->dxSwapchain->Present(1, 0);
}
