#pragma once
#include "Texture.h"

#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxTextures/include/dxTexture.h"
#include "../../RenderingCore/include/ActiveAPITypeAccessor.h"

class TextureFactory
{
public:
	TextureFactory();
	~TextureFactory();

	static Texture* createTexture();
};

