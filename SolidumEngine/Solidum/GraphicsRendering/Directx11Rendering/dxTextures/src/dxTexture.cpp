#include "../include/dxTexture.h"

dxTexture::dxTexture()
{

}

dxTexture::~dxTexture()
{
	texture->Release();
}

void dxTexture::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

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
