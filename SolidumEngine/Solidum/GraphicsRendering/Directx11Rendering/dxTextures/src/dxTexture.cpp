#include "../include/dxTexture.h"

dxTexture::dxTexture()
{

}

dxTexture::~dxTexture()
{
	texture->Release();
}

void dxTexture::load()
{
	InitData* realBuilder = (InitData*)getContext()->getResourceInitParams();

	loadImage(realBuilder->_filename);
}

void dxTexture::unload()
{
}

void dxTexture::loadImage(LPCWSTR filename)
{
	HRESULT result;
	result = D3DX11CreateShaderResourceViewFromFile(
		dxDeviceAccessor::dxEncapsulator->dxDev,
		filename,
		NULL,
		NULL,
		&texture,
		NULL);

	ID3D11Texture2D *pTextureInterface = 0;
	ID3D11Resource *res;
	texture->GetResource(&res);
	res->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
	D3D11_TEXTURE2D_DESC desc;
	pTextureInterface->GetDesc(&desc);

	_width = desc.Width;
	_height = desc.Height;

	int debugRef = -1;
}

void dxTexture::updateParameter(std::string varName, void * data)
{
	if (varName == "TEXTURE") {
		texture = (ID3D11ShaderResourceView*)data;
	}
}

void * dxTexture::getParameter(std::string varName)
{
	if (varName == "TEXTURE") {
		return texture;
	}

	return nullptr;
}
