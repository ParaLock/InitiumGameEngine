#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../ResourceFramework/include/IResource.h"

class TextureBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;

	TextureBuilder(LPCWSTR filename) {
		_filename = filename;
	}
};

class Texture : public IResource
{
public:
	Texture();
	~Texture();

	virtual void load(IResourceBuilder* builder) = 0;
	virtual void unload() = 0;

	virtual void loadImage(LPCWSTR filename);
};

