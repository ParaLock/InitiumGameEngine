#include "..\include\TextureFactory.h"

TextureFactory::TextureFactory()
{
}


TextureFactory::~TextureFactory()
{
}

std::map<std::string, ITexture*>* TextureFactory::texLibrary = new std::map<std::string, ITexture*>;

ITexture * TextureFactory::createTexture(LPCWSTR filename, int textureType, std::string ID)
{
	ITexture *newTexture;

	switch (textureType) {
	case DXTEXTURE:
		dxTexture *newDxTex = new dxTexture(filename);

		newTexture = newDxTex;
		break;
	}

	texLibrary->insert({ID, newTexture});

	return newTexture;
}

ITexture * TextureFactory::requestTexture(std::string ID)
{
	return texLibrary->at(ID);
}

void TextureFactory::destroyTexLibrary()
{
	texLibrary->clear();
	delete texLibrary;
}
