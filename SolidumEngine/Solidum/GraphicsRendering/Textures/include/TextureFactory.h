#pragma once

#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxTextures/include/dxTexture.h"


class TextureFactory
{
private:
	static std::map<std::string, ITexture*>* texLibrary;
public:
	TextureFactory();
	~TextureFactory();

	static ITexture* createTexture(LPCWSTR filename, int textureType, std::string ID);

	static ITexture* requestTexture(std::string ID);

	static void destroyTexLibrary();

};

