#include "../include/dxRenderTarget.h"

dxRenderTarget::dxRenderTarget() {

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	HRESULT result;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

	textureDesc.Width = windowAccessor::screen_width;
	textureDesc.Height = windowAccessor::screen_height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	result = dxDev->CreateTexture2D(&textureDesc, NULL, &texture);

	result = dxDev->CreateRenderTargetView(texture, &renderTargetViewDesc, &renderTarget);

	dxDev->CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderView);

	int breakPoint = 0;

}


dxRenderTarget::~dxRenderTarget()
{
	renderTarget->Release();
	shaderView->Release();
	texture->Release();
}

void dxRenderTarget::BindAsShaderResource()
{
	switch (parentShaderType) {
	case PARENT_SHADER_TYPE_PIXEL:
		dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShaderResources(resSlot, 1, &shaderView);
		break;
	case PARENT_SHADER_TYPE_VERTEX:
		dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShaderResources(resSlot, 1, &shaderView);
		break;
	default:
		break;
	}
}

void dxRenderTarget::Clear(float R, float G, float B, float A)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->ClearRenderTargetView(renderTarget, D3DXCOLOR(R, G, B, A));
}
