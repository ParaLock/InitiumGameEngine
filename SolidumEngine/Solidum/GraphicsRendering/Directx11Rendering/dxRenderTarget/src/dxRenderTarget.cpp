#include "../include/dxRenderTarget.h"

dxRenderTarget::dxRenderTarget()
{
}

dxRenderTarget::dxRenderTarget(ID3D11RenderTargetView * rt, ID3D11Texture2D * rtTex)
{
	//Yup.... This constructer is a hack xD
	_texture = rtTex;
	_renderTarget = rt;

	_aaSamples = -1;
	_mipLevel = -1;
	_texFormat = -1;
}

dxRenderTarget::dxRenderTarget(ID3D11ShaderResourceView * sv, ID3D11Texture2D * svTex)
{
	//And again.... I promise to fix this in the future... (4 years later)
	_texture = svTex;
	_shaderView = sv;

	_aaSamples = -1;
	_mipLevel = -1;
	_texFormat = -1;
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

void dxRenderTarget::load(IResourceBuilder * builder)
{
	RenderTargetBuilder* realBuilder = static_cast<RenderTargetBuilder*>(builder);

	_aaSamples = realBuilder->_aaSamples;
	_mipLevel = realBuilder->_mipLevel;
	_texFormat = realBuilder->_texFormat;

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	HRESULT result;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

	switch (_texFormat) {
	case RGBA_32BIT_FLOAT:

		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		break;
	case RGB_32BIT_FLOAT:

		textureDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		break;
	case D24_UNORM_S8_UINT_COUGH_FRAMEBUFFER:

		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	}

	textureDesc.Width = window::getInstance()->screen_width;
	textureDesc.Height = window::getInstance()->screen_height;
	textureDesc.ArraySize = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	textureDesc.MipLevels = _mipLevel;
	textureDesc.SampleDesc.Count = _aaSamples;

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = _mipLevel;

	result = dxDev->CreateTexture2D(&textureDesc, NULL, &_texture);
	result = dxDev->CreateRenderTargetView(_texture, &renderTargetViewDesc, &_renderTarget);
	dxDev->CreateShaderResourceView(_texture, &shaderResourceViewDesc, &_shaderView);

	isLoaded = true;
}

void dxRenderTarget::unload()
{
	isLoaded = false;
}

void dxRenderTarget::updateParameter(std::string varName, void * data)
{
	if (varName == "D3D_TEXTURE") {
		_texture = (ID3D11Texture2D*)data;
	}
	if (varName == "D3D_RENDERTARGET") {
		_renderTarget = (ID3D11RenderTargetView*)data;
	}
	if (varName == "D3D_SHADERVIEW") {
		_shaderView = (ID3D11ShaderResourceView*)data;
	}
}

void * dxRenderTarget::getParameter(std::string varName)
{
	if (varName == "D3D_TEXTURE") {
		return _texture;
	}
	if (varName == "D3D_RENDERTARGET") {
		return _renderTarget;
	}
	if (varName == "D3D_SHADERVIEW") {
		return _shaderView;
	}

	return nullptr;
}

void dxRenderTarget::Clear(float R, float G, float B, float A)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->ClearRenderTargetView(_renderTarget, D3DXCOLOR(R, G, B, A));
}
