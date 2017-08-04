#include "../include/dxRenderTarget.h"

dxRenderTarget::dxRenderTarget()
{
}

dxRenderTarget::~dxRenderTarget()
{
	if(_renderTarget != nullptr)
	_renderTarget->Release();
	if(_shaderView != nullptr)
	_shaderView->Release();
	if(_texture != nullptr)
	_texture->Release();
}

void dxRenderTarget::load()
{
	InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

	_texFormat = realBuilder->_texFormat;

	if (_texFormat == TEX_FORMAT::INVALID) { return; }

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	_viewPort = Viewport(realBuilder->_height, realBuilder->_width, 1, 0);

	HRESULT result;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

	switch (_texFormat) {
	case TEX_FORMAT::RGBA_32BIT_FLOAT:

		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		break;
	case TEX_FORMAT::RGB_32BIT_FLOAT:

		textureDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		break;
	case TEX_FORMAT::D24_UNORM_S8_UINT_COUGH_FRAMEBUFFER:

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	case TEX_FORMAT::R24G8_TYPLESS:
		textureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		break;
	}

	textureDesc.Width = realBuilder->_width;
	textureDesc.Height = realBuilder->_height;
	textureDesc.ArraySize = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc.Count = 1;

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	result = dxDev->CreateTexture2D(&textureDesc, NULL, &_texture);
	result = dxDev->CreateRenderTargetView(_texture, &renderTargetViewDesc, &_renderTarget);
	dxDev->CreateShaderResourceView(_texture, &shaderResourceViewDesc, &_shaderView);
}

void dxRenderTarget::unload()
{
}

void dxRenderTarget::updateParameter(std::string varName, void * data)
{
	if (varName == "TEXTURE") {

		_texture = (ID3D11Texture2D*)data;
	}
	if (varName == "RENDERTARGET") {

		_renderTarget = (ID3D11RenderTargetView*)data;
	}
	if (varName == "SHADERVIEW") {

		_shaderView = (ID3D11ShaderResourceView*)data;
	}
}

void * dxRenderTarget::getParameter(std::string varName)
{
	if (varName == "TEXTURE") {
		return _texture;
	}
	if (varName == "RENDERTARGET") {
		return _renderTarget;
	}
	if (varName == "SHADERVIEW") {
		return _shaderView;
	}

	return nullptr;
}

void dxRenderTarget::Clear(float R, float G, float B, float A)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->ClearRenderTargetView(_renderTarget, D3DXCOLOR(R, G, B, A));
}
