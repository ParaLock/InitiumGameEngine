#include "..\include\dxDevice.h"

dxDevice::dxDevice()
{
}

dxDevice::~dxDevice()
{
	dxDev->Release();
	dxDevContext->Release();
	dxSwapchain->Release();
}

void dxDevice::Initialize(dxConfigBlock *config)
{
	dxConfigBlock *devConfig = config;

	HRESULT result;

	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = devConfig->swapchain.BufferCount;
	scd.BufferDesc.Format = devConfig->swapchain.Format;
	scd.BufferUsage = devConfig->swapchain.BufferUsage;

	scd.SampleDesc.Count = config->swapchain.SampleCount;
	scd.OutputWindow = devConfig->swapchain.OutputWindow;
	scd.Windowed = devConfig->swapchain.Windowed;


	UINT creationFlags = 0;
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;

	result = D3D11CreateDeviceAndSwapChain(
		NULL,
		devConfig->dev.DriverType,
		NULL,
		NULL,
		NULL,
		NULL,
		devConfig->dev.SDKVersion,
		&scd,
		&dxSwapchain,
		&dxDev,
		NULL,
		&dxDevContext
		);

		//assert(result == S_OK && "dx device creation failed");

		InitializeFrameBuffer();
		InitializeDepthBuffer();
		InitializeDepthStencilStates();
		InitializeViewport();
		InitializeBlendStates();
		InitializeRasterStates();

		setViewport("light");
}

void dxDevice::InitializeDepthBuffer()
{
	HRESULT result;
	D3D11_TEXTURE2D_DESC descDepth;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;

	ZeroMemory(&descDepth, sizeof(descDepth));
	ZeroMemory(&descDSV, sizeof(descDSV));
	ZeroMemory(&sr_desc, sizeof(sr_desc));

	descDepth.Width = window::getInstance()->screen_width;
	descDepth.Height = window::getInstance()->screen_height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	sr_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	sr_desc.Texture2D.MostDetailedMip = 0;
	sr_desc.Texture2D.MipLevels = -1;

	result = dxDev->CreateTexture2D(&descDepth, NULL, &depthTexture);
	result = dxDev->CreateDepthStencilView(depthTexture, &descDSV, &depthStencil);
	result = dxDev->CreateShaderResourceView(depthTexture, &sr_desc, &depthShaderView);
}

void dxDevice::InitializeFrameBuffer()
{
	HRESULT result;

	result = dxSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&FrameBufferTexture);
	result = dxDev->CreateRenderTargetView(FrameBufferTexture, NULL, &FrameBufferShaderAccess);
}

void dxDevice::InitializeRasterStates()
{
	D3D11_RASTERIZER_DESC rasterizerStateNormalDesc;
	ZeroMemory(&rasterizerStateNormalDesc, sizeof(rasterizerStateNormalDesc));
	
	rasterizerStateNormalDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerStateNormalDesc.CullMode = D3D11_CULL_BACK;
	rasterizerStateNormalDesc.FrontCounterClockwise = FALSE;
	rasterizerStateNormalDesc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
	rasterizerStateNormalDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	rasterizerStateNormalDesc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	rasterizerStateNormalDesc.DepthClipEnable = TRUE;
	rasterizerStateNormalDesc.ScissorEnable = FALSE;
	rasterizerStateNormalDesc.MultisampleEnable = FALSE;
	rasterizerStateNormalDesc.AntialiasedLineEnable = FALSE;

	dxDev->CreateRasterizerState(&rasterizerStateNormalDesc, &rasterStateNormalRendering);

	D3D11_RASTERIZER_DESC rasterizerStateNoCullingDesc;
	ZeroMemory(&rasterizerStateNoCullingDesc, sizeof(rasterizerStateNoCullingDesc));

	rasterizerStateNoCullingDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerStateNoCullingDesc.CullMode = D3D11_CULL_BACK;
	rasterizerStateNoCullingDesc.FrontCounterClockwise = FALSE;
	rasterizerStateNoCullingDesc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
	rasterizerStateNoCullingDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	rasterizerStateNoCullingDesc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	rasterizerStateNoCullingDesc.DepthClipEnable = FALSE;
	rasterizerStateNoCullingDesc.ScissorEnable = FALSE;
	rasterizerStateNoCullingDesc.MultisampleEnable = FALSE;
	rasterizerStateNoCullingDesc.AntialiasedLineEnable = FALSE;

	dxDev->CreateRasterizerState(&rasterizerStateNoCullingDesc, &rasterStateNoCulling);
}

void dxDevice::InitializeDepthStencilStates()
{
	HRESULT result;

	D3D11_DEPTH_STENCIL_DESC depthStencilDisabledDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilEnableDesc;

	ZeroMemory(&depthStencilEnableDesc, sizeof(depthStencilEnableDesc));

	depthStencilEnableDesc.DepthEnable = true;
	depthStencilEnableDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilEnableDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilEnableDesc.StencilEnable = true;
	depthStencilEnableDesc.StencilReadMask = 0xFF;
	depthStencilEnableDesc.StencilWriteMask = 0xFF;

	depthStencilEnableDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilEnableDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilEnableDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilEnableDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilEnableDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilEnableDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilEnableDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilEnableDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = dxDev->CreateDepthStencilState(&depthStencilEnableDesc, &depthStencilEnable);

	ZeroMemory(&depthStencilDisabledDesc, sizeof(depthStencilDisabledDesc));

	depthStencilDisabledDesc.DepthEnable = false;
	depthStencilDisabledDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDisabledDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDisabledDesc.StencilEnable = true;
	depthStencilDisabledDesc.StencilReadMask = 0xFF;
	depthStencilDisabledDesc.StencilWriteMask = 0xFF;

	depthStencilDisabledDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDisabledDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDisabledDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDisabledDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDisabledDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDisabledDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDisabledDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDisabledDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = dxDev->CreateDepthStencilState(&depthStencilDisabledDesc, &depthStencilDisable);
}

void dxDevice::InitializeBlendStates()
{
	HRESULT result;

	D3D11_BLEND_DESC lightBlendStateDesc;
	ZeroMemory(&lightBlendStateDesc, sizeof(D3D11_BLEND_DESC));
	
	lightBlendStateDesc.RenderTarget[0].BlendEnable = TRUE;
	lightBlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	lightBlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	lightBlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	lightBlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	lightBlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	lightBlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	lightBlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	result = dxDev->CreateBlendState(&lightBlendStateDesc, &lightBlendState);

	D3D11_BLEND_DESC passBlendStateDesc;
	ZeroMemory(&passBlendStateDesc, sizeof(D3D11_BLEND_DESC));

	passBlendStateDesc.RenderTarget[0].BlendEnable = TRUE;
	passBlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	passBlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	passBlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	passBlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	passBlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	passBlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	passBlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	passBlendStateDesc.RenderTarget[3].BlendEnable = TRUE;
	passBlendStateDesc.RenderTarget[3].BlendOp = D3D11_BLEND_OP_ADD;
	passBlendStateDesc.RenderTarget[3].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	passBlendStateDesc.RenderTarget[3].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	passBlendStateDesc.RenderTarget[3].SrcBlend = D3D11_BLEND_ONE;
	passBlendStateDesc.RenderTarget[3].DestBlend = D3D11_BLEND_ONE;
	passBlendStateDesc.RenderTarget[3].SrcBlendAlpha = D3D11_BLEND_ONE;
	passBlendStateDesc.RenderTarget[3].DestBlendAlpha = D3D11_BLEND_ONE;

	result = dxDev->CreateBlendState(&passBlendStateDesc, &passBlendState);

	D3D11_BLEND_DESC BlendDisableDesc;
	ZeroMemory(&BlendDisableDesc, sizeof(D3D11_BLEND_DESC));

	BlendDisableDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDisableDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDisableDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDisableDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	BlendDisableDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	BlendDisableDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	BlendDisableDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDisableDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	result = dxDev->CreateBlendState(&BlendDisableDesc, &blendDisable);
}


void dxDevice::InitializeViewport()
{
	ZeroMemory(&meshViewport, sizeof(D3D11_VIEWPORT));

	meshViewport.Width = (FLOAT)window::getInstance()->screen_width;
	meshViewport.Height = (FLOAT)window::getInstance()->screen_height;
	meshViewport.TopLeftX = 0;
	meshViewport.TopLeftY = 0;
	meshViewport.MaxDepth = 1;
	meshViewport.MinDepth = 0;

	ZeroMemory(&lightViewport, sizeof(D3D11_VIEWPORT));

	lightViewport.Width = (FLOAT)window::getInstance()->screen_width;
	lightViewport.Height = (FLOAT)window::getInstance()->screen_height;
	lightViewport.TopLeftX = 0;
	lightViewport.TopLeftY = 0;
	lightViewport.MaxDepth = 1;
	lightViewport.MinDepth = 0;
}

void dxDevice::clearDepthStencil()
{
	dxDevContext->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void dxDevice::clearFrameBuffer(float R, float G, float B, float A)
{
	dxDevContext->ClearRenderTargetView(FrameBufferShaderAccess, D3DXCOLOR(R, G, B, A));
}

void dxDevice::setRasterState(RASTER_STATE state)
{
	switch (state)
	{
	case RASTER_STATE::NORMAL:
		dxDevContext->RSSetState(rasterStateNormalRendering);
		break;
	case RASTER_STATE::DISABLE_TRIANGLE_CULL:
		dxDevContext->RSSetState(rasterStateNoCulling);
		break;
	default:
		break;
	}
}

void dxDevice::setDepthTestState(DEPTH_TEST_STATE state)
{
	switch (state)
	{
	case FULL_DISABLE:
		dxDevContext->OMSetDepthStencilState(depthStencilDisable, 1);
		break;
	case FULL_ENABLE:
		dxDevContext->OMSetDepthStencilState(depthStencilEnable, 1);
		break;
	default:
		break;
	}
}

void dxDevice::setBlendState(BLEND_STATE state)
{
	switch (state)
	{
	case BLEND_STATE::BLENDING_OFF:
		dxDevContext->OMSetBlendState(blendDisable, 0, 0xffffffff);
		break;
	case BLEND_STATE::LIGHT_BLENDING:
		dxDevContext->OMSetBlendState(lightBlendState, 0, 0xffffffff);
		break;
	case BLEND_STATE::PASS_BLENDING:
		dxDevContext->OMSetBlendState(passBlendState, 0, 0xffffffff);
		break;
	default:
		break;
	}
}


void dxDevice::setViewport(std::string viewportSelect)
{
	if(viewportSelect == "mesh")
	dxDevContext->RSSetViewports(1, &meshViewport);
	if(viewportSelect == "light")
	dxDevContext->RSSetViewports(1, &lightViewport);
}

