#include "../include/dxDepthStencil.h"



dxDepthStencil::dxDepthStencil()
{
}


dxDepthStencil::~dxDepthStencil()
{
}

void dxDepthStencil::clear(float depth)
{
	dxDevice* dxDevice = dxDeviceAccessor::dxEncapsulator;

	dxDevice->dxDevContext->ClearDepthStencilView(_depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, 0);
}

void dxDepthStencil::load(std::shared_ptr<IResourceBuilder> builder)
{
	dxDevice* dxManager = dxDeviceAccessor::dxEncapsulator;

	InitData* realBuilder = static_cast<InitData*>(builder.get());

	HRESULT result;
	D3D11_TEXTURE2D_DESC descDepth;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;

	ZeroMemory(&descDepth, sizeof(descDepth));
	ZeroMemory(&descDSV, sizeof(descDSV));
	ZeroMemory(&sr_desc, sizeof(sr_desc));

	descDepth.Width = realBuilder->_width;
	descDepth.Height = realBuilder->_height;
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

	result = dxManager->dxDev->CreateTexture2D(&descDepth, NULL, &_depthTexture);
	result = dxManager->dxDev->CreateDepthStencilView(_depthTexture, &descDSV, &_depthStencil);
	result = dxManager->dxDev->CreateShaderResourceView(_depthTexture, &sr_desc, &_depthShaderView);

	isLoaded = true;
}

void dxDepthStencil::unload()
{
	isLoaded = false;
}

void * dxDepthStencil::getParameter(std::string varName)
{
	if (varName == "TEXTURE") {
		return _depthTexture;
	}
	if (varName == "SHADERVIEW") {
		return _depthShaderView;
	}
	if (varName == "STENCILVIEW") {
		return _depthStencil;
	}

	return nullptr;
}
