#pragma once

#include "../../../../sysInclude.h"

#include "../../../Window/include/window.h"

#ifndef _DXDEVICE_H
#define _DXDEVICE_H

struct dxDevConfig
{
	D3D_DRIVER_TYPE				DriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT						Flags = D3D11_CREATE_DEVICE_DEBUG;
	UINT						SDKVersion = D3D11_SDK_VERSION;
};

struct dxSwapchainConfig
{
	UINT						BufferCount = 1;
	UINT						Width;
	UINT						Height;
	DXGI_FORMAT					Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_USAGE					BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	HWND						OutputWindow;
	UINT						SampleCount = 1;
	UINT						SampleQuality = 0;
	BOOL						Windowed = TRUE;
};

struct dxConfigBlock {

	dxDevConfig dev;
	dxSwapchainConfig swapchain;

};

class dxDevice
{
protected:
private:

	void InitializeDepthBuffer();
	void InitializeFrameBuffer();
	void InitializeRasterStates();
	void InitializeDepthStencilStates();

	void InitializeBlendStates();

	void InitializeViewport();

	ID3D11Texture2D* FrameBufferTexture = nullptr;
	
	ID3D11Texture2D* depthTexture = nullptr;

	ID3D11ShaderResourceView* depthShaderView = nullptr;

	dxConfigBlock devConfig;

public:
	dxDevice();
	~dxDevice();

	ID3D11RenderTargetView* FrameBufferShaderAccess;
	ID3D11Device *dxDev;
	ID3D11DeviceContext *dxDevContext;
	IDXGISwapChain *dxSwapchain;

	D3D11_VIEWPORT meshViewport;
	D3D11_VIEWPORT lightViewport;

	ID3D11DepthStencilView *depthStencil;

	ID3D11DepthStencilState* depthStencilDisable;
	ID3D11DepthStencilState* depthStencilEnable;
	ID3D11DepthStencilState* depthLessEqualState;

	ID3D11RasterizerState* rasterStateNormalRendering;
	ID3D11RasterizerState* rasterStateNoCulling;

	ID3D11BlendState *lightBlendState;
	ID3D11BlendState *passBlendState;
	ID3D11BlendState *blendDisable;


	void clearDepthStencil();
	void clearFrameBuffer(float R, float G, float B, float A);
	
	void setRasterState(RASTER_STATE state);

	void setDepthTestState(DEPTH_TEST_STATE state);

	void setBlendState(BLEND_STATE state);

	void setViewport(std::string viewportSelect);

	void Initialize(dxConfigBlock *config);

	ID3D11RenderTargetView* getFrameBufferRenderTarget() { return FrameBufferShaderAccess; }
	ID3D11Texture2D* getFrameBufferTexture() { return FrameBufferTexture; }

	ID3D11ShaderResourceView* getDepthBufferShaderView() { return depthShaderView; }
	ID3D11Texture2D* getDepthBufferTexture() { return depthTexture; }

};

#endif