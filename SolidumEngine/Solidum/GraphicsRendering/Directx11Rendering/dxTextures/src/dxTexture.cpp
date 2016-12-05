#include "../include/dxTexture.h"

dxTexture::dxTexture(LPCWSTR fileName) 
{
	HRESULT result;
	result = D3DX11CreateShaderResourceViewFromFile(
		dxDeviceAccessor::dxEncapsulator->dxDev,
		fileName,
		NULL,
		NULL,
		&texture,
		NULL);

}

dxTexture::~dxTexture()
{
	texture->Release();
}

void dxTexture::Bind()
{
	switch (parentShaderType) {
	case PARENT_SHADER_TYPE_PIXEL:
		dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShaderResources(resSlot, 1, &texture);
		break;
	case PARENT_SHADER_TYPE_VERTEX:
		dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShaderResources(resSlot, 1, &texture);
		break;
	default:
		break;
	}
}
