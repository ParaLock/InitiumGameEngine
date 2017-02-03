#include "../include/dxTexture.h"

dxTexture::dxTexture()
{

}

dxTexture::~dxTexture()
{
	texture->Release();
}

void dxTexture::load(IResourceBuilder * builder)
{
	TextureBuilder* realBuilder = static_cast<TextureBuilder*>(builder);

	loadImage(realBuilder->_filename);

	isLoaded = true;
}

void dxTexture::unload()
{
	isLoaded = false;
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
}

void dxTexture::updateParameter(std::string varName, void * data)
{
	if (varName == "D3D_TEXTURE") {
		texture = (ID3D11ShaderResourceView*)data;
	}
}

void * dxTexture::getParameter(std::string varName)
{
	if (varName == "D3D_TEXTURE") {
		return texture;
	}

	return nullptr;
}
