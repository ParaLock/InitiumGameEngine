#include "../include/TextureFactory.h"



TextureFactory::TextureFactory()
{
}


TextureFactory::~TextureFactory()
{
}

Texture * TextureFactory::createTexture()
{
	Texture* newTex = nullptr;

	switch (ActiveAPITypeAccessor::_apiInUse) {
	case DIRECTX11:
		newTex = new dxTexture();
		break;
	}

	return newTex;
}
