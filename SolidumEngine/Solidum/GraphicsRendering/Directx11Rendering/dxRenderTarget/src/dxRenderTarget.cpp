#include "../include/dxRenderTarget.h"

dxRenderTarget::dxRenderTarget(int mipLevel, int aaSamples, TEX_FORMAT texFormat) 
{
	_aaSamples = aaSamples;
	_mipLevel = mipLevel;
	_texFormat = texFormat;

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
			break;
		case RGB_32BIT_FLOAT:
			textureDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
	}

	textureDesc.Width = windowAccessor::screen_width;
	textureDesc.Height = windowAccessor::screen_height;
	textureDesc.ArraySize = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	textureDesc.MipLevels = _mipLevel;
	textureDesc.SampleDesc.Count = _aaSamples;

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = _mipLevel;

	result = dxDev->CreateTexture2D(&textureDesc, NULL, &texture);
	result = dxDev->CreateRenderTargetView(texture, &renderTargetViewDesc, &renderTarget);
	dxDev->CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderView);

}

dxRenderTarget::~dxRenderTarget()
{
	renderTarget->Release();
	shaderView->Release();
	texture->Release();
}

void dxRenderTarget::updateParameter(std::string varName, void * data)
{
	if (varName == "D3D_TEXTURE") {
		texture = (ID3D11Texture2D*)data;
	}
	if (varName == "D3D_RENDERTARGET") {
		renderTarget = (ID3D11RenderTargetView*)data;
	}
	if (varName == "D3D_SHADERVIEW") {
		shaderView = (ID3D11ShaderResourceView*)data;
	}
}

void * dxRenderTarget::getParameter(std::string varName)
{
	if (varName == "D3D_TEXTURE") {
		return texture;
	}
	if (varName == "D3D_RENDERTARGET") {
		return renderTarget;
	}
	if (varName == "D3D_SHADERVIEW") {
		return shaderView;
	}

	return nullptr;
}

void dxRenderTarget::Clear(float R, float G, float B, float A)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->ClearRenderTargetView(renderTarget, D3DXCOLOR(R, G, B, A));
}
